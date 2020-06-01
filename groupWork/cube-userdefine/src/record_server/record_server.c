#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "data_type.h"
#include "alloc.h"
#include "memfunc.h"
#include "basefunc.h"
#include "struct_deal.h"
#include "crypto_func.h"
#include "memdb.h"
#include "message.h"
#include "ex_module.h"
#include "sys_func.h"
#include "user_define.h"
//#include "user_server.h"	//后加的，为了订单号加上用户名
#include "record_define.h"
#include "record_server.h"
// add para lib_include
int record_server_init(void * sub_proc, void * para)
{
	int ret;
	// add yorself's module init func here
	return 0;
}
int record_server_start(void * sub_proc, void * para)
{
	int ret;
	void * recv_msg;
	int type;
	int subtype;
	// add yorself's module exec func here
	while(1)
	{
		usleep(time_val.tv_usec);
		ret=ex_module_recvmsg(sub_proc,&recv_msg);
		if(ret<0)
			continue;
		if(recv_msg==NULL)
			continue;
		type=message_get_type(recv_msg);
		subtype=message_get_subtype(recv_msg);
		if(!memdb_find_recordtype(type,subtype))
		{
			printf("message format (%d %d) is not registered!\n",
			message_get_type(recv_msg),message_get_subtype(recv_msg));
			continue;
		}
		if((type==TYPE(RECORD_DEFINE))&&(subtype==SUBTYPE(RECORD_DEFINE,WRITE)))
		{
			ret=proc_record_write(sub_proc,recv_msg);
		}
		if((type==TYPE(RECORD_DEFINE))&&(subtype==SUBTYPE(RECORD_DEFINE,READ)))
		{
			ret=proc_record_read(sub_proc,recv_msg);
		}
	}
	return 0;
}

int proc_record_write(void * sub_proc,void * recv_msg)
{
	int ret;
	RECORD(RECORD_DEFINE,RECORD) * record_data;
	RECORD(RECORD_DEFINE,WRITE) * write_data;
	RECORD(USER_DEFINE,RETURN) * return_info;
	RECORD(USER_DEFINE,SERVER_STATE) * user_state;

	void * new_msg;
	
	ret=message_get_record(recv_msg,&write_data,0);
	if(ret<0)
		return ret;

	return_info=Talloc0(sizeof(*return_info));
	if(return_info==NULL)
		return -ENOMEM;

	//后加的
	DB_RECORD * db_record;

// find the user state, 
/*	db_record=memdb_find_first(TYPE_PAIR(USER_DEFINE,SERVER_STATE),"user_name",write_data->user);
	if(db_record==NULL)
	{
		return_info->return_code=NOUSER;
		return_info->return_info=dup_str("no such user!\n",0);
		goto write_out;
	}
 	user_state=db_record->record;
*/
//	find the record

	time_t now;
	struct tm *p;
	time(&now);
	p = localtime(&now);
	char timeStamp[14], month[10], date[8], hour[6], minute[4], second[2];
	//类型转换后拼接成字符串
	//时间
	sprintf(timeStamp, "%d", 1900+p->tm_year);
	sprintf(month, "%02d", p->tm_mon+1);
	sprintf(date, "%02d", p->tm_mday);
	sprintf(hour, "%02d", p->tm_hour);
	sprintf(minute, "%02d", p->tm_min);
	sprintf(second, "%02d", p->tm_sec);
	//名字
	char user_name[5], order_no[32];
	FILE *name = fopen("./output.txt", "r");
	fscanf(name, "%s", user_name);
	truncate("./output.txt", 0);	//清空文件
//	memset(user_name,'\0',sizeof(user_name));
	fclose(name);
	strcpy(order_no, user_name);	//将读出来的名字复制到order_no
	strcat(order_no, "__");
	strcat(order_no, strcat(timeStamp, strcat(month, strcat(date, strcat(hour, strcat(minute, strcat(second, "__YT")))))));
	//顾客，由系统分配订单号
	if(Strncmp(user_name, "guke", 4) == 0){
		//顾客且非越权写
		//顾客第一次写，随机分配订单号写
		if((Strncmp(order_no, user_name, 7) == 0) && (Strcmp(write_data->Pay_no, "") == 0)){
			printf("\033[40;33;1m<>\033[0m当前写操作用户为顾客：%s，写订单号将随机分配为：\033[44;31;1m%s\033[0m。\n", user_name, order_no);
			db_record=memdb_find_first(TYPE_PAIR(RECORD_DEFINE,RECORD),"Pay_no",order_no);
			char order_no_path[30] = "./../";
			strcat(order_no_path, user_name);
			strcat(order_no_path, "/ORDER_NO.txt");
			FILE *Customer_order_no = fopen(order_no_path, "a");
			fprintf(Customer_order_no, "%s\r", order_no);
			fclose(Customer_order_no);
		}
		//顾客带订单号来写，读取所要求的合法订单号
		else if((Strncmp(write_data->Pay_no, user_name, 7) == 0) && (Strcmp(write_data->Pay_no, "") > 0)){
			if(Strncmp(write_data->Pay_no, "guke", 4) == 0){	//订单号有效
				printf("顾客自带订单号写: %s\n", write_data->Pay_no);
				db_record=memdb_find_first(TYPE_PAIR(RECORD_DEFINE,RECORD),"Pay_no",write_data->Pay_no);
			}
			else{	//订单号无效
				return_info->return_code=INVALID;
				return_info->return_info=dup_str("Customer writes data fail! INVALID PAY_NO!!!", 0);
				goto write_out;
			}	
		}
		//顾客越权写限制定义
		else{
			return_info->return_code=AUTHFAIL;
			return_info->return_info=dup_str("You have NO AUTH to WRITE other customers' order(s)!!!",0);
			goto write_out;
		}
	}
	//非顾客，需自带订单号来写
	else{
		printf("\033[40;33;1m<>\033[0m当前写操作用户为\033[40;31;1m非顾客\033[0m：%s，写订单号将根据需求获取\033[44;31;1m（不提供则不写）\033[0m。\n", user_name);
		if(Strncmp(write_data->Pay_no, "guke", 4) == 0){	//订单号有效
			char order_no_path[30] = "./../";
			strcat(order_no_path, user_name);
			strcat(order_no_path, "/ORDER_NO.txt");
			FILE *Customer_order_no = fopen(order_no_path, "a");
			fprintf(Customer_order_no, "%s\n", write_data->Pay_no);
			fclose(Customer_order_no);
			db_record=memdb_find_first(TYPE_PAIR(RECORD_DEFINE,RECORD),"Pay_no",write_data->Pay_no);
		}
		else{	//订单号无效
			return_info->return_code=INVALID;
			return_info->return_info=dup_str("write data fail! INVALID PAY_NO!!!", 0);
			goto write_out;
		}
	}
	if(db_record==NULL)
	{
		record_data=Talloc0(sizeof(*record_data));
		if((Strncmp(user_name, "guke", 4) == 0) && (Strcmp(write_data->Pay_no, "") <= 0))
			record_data->Pay_no = dup_str(order_no,0);
		else
			record_data->Pay_no = dup_str(write_data->Pay_no,0);
	}
	else
	{
		record_data=db_record->record;
	}

	//  add write access control code begin

	//  add write access control code end

	void * record_template = memdb_get_template(TYPE_PAIR(RECORD_DEFINE,RECORD));
	if(record_template==NULL)
		return -EINVAL;
	
	ret = struct_write_elem_text(write_data->segment,record_data,write_data->text,record_template);
	if(ret<0)
		return -EINVAL;

	if(Strcmp(write_data->segment,"Goods_name")==0){
		record_data->Goods_name= dup_str(write_data->text,256);
	}
	else if(Strcmp(write_data->segment,"Goods_num")==0){
		record_data->Goods_num= dup_str(write_data->text,256);
	}
	else if(Strcmp(write_data->segment,"Rec_addr")==0){
		record_data->Rec_addr= dup_str(write_data->text,256);
	}
	else if(Strcmp(write_data->segment,"Deli_addr")==0){
		if((Strcmp(record_data->Goods_name, "") > 0) && (Strcmp(record_data->Goods_num, "") > 0) && (Strcmp(record_data->Rec_addr, "") > 0))
			record_data->Deli_addr= dup_str(write_data->text,256);
		else{
			record_data->Deli_addr= dup_str("",256);
			return_info->return_code=INVALID;
			return_info->return_info=dup_str("写Deli_addr失败! 需要先完成订单所有基本信息填写!",0);
			goto write_out;
		}
	}
	else if(Strcmp(write_data->segment,"isSent")==0){
		if((Strcmp(record_data->Rec_addr, "") > 0) && (Strcmp(record_data->Deli_addr, "") > 0))
			record_data->isSent= dup_str(write_data->text,256);
		else{
			record_data->isSent= dup_str("",256);
			return_info->return_code=INVALID;
			return_info->return_info=dup_str("写isSent失败! 需要先写收发货地址!",0);
			goto write_out;
		}
	}
	else if(Strcmp(write_data->segment,"isReceived")==0){
		if(Strcmp(record_data->isSent, "true") == 0)
			record_data->isReceived= dup_str(write_data->text,256);
		else{
			record_data->isReceived= dup_str("",256);
			return_info->return_code=INVALID;
			return_info->return_info=dup_str("写isReceived失败! 订单需已发出才是否收货!",0);
			goto write_out;
		}
	}
	else if(Strcmp(write_data->segment,"Goods_addr")==0){
		if(Strcmp(record_data->isSent, "true") == 0)
			record_data->Goods_addr= dup_str(write_data->text,256);
		else{
			record_data->Goods_addr= dup_str("",256);
			return_info->return_code=INVALID;
			return_info->return_info=dup_str("写Goods_addr失败! 货物需已发出才可写途中具体位置!",0);
			goto write_out;
		}
			
	}
	else if(Strcmp(write_data->segment,"isFinished")==0){
		if(Strcmp(record_data->isReceived, "true") == 0)
			record_data->isFinished= dup_str(write_data->text,256);	
		else{
			record_data->isFinished= dup_str("",256);
			return_info->return_code=INVALID;
			return_info->return_info=dup_str("写isFinished失败! 需要顾客确认送达后才可结束订单!",0);
			goto write_out;
		}
	}
	memdb_store(record_data,TYPE_PAIR(RECORD_DEFINE,RECORD),NULL);
	return_info->return_code=SUCCEED;
	return_info->return_info=dup_str("write data succeed!",0);

	// send a message store notice
    	void * type_msg;
    	RECORD(MESSAGE,TYPES) types_pair;

    	types_pair.type=TYPE(RECORD_DEFINE);
    	types_pair.subtype=SUBTYPE(RECORD_DEFINE,RECORD);
		
    	type_msg=message_create(TYPE_PAIR(MESSAGE,TYPES),NULL);

    	message_add_record(type_msg,&types_pair);
    	ex_module_sendmsg(sub_proc,type_msg);
write_out:
	new_msg=message_create(TYPE_PAIR(USER_DEFINE,RETURN),recv_msg);	
	if(new_msg==NULL)
		return -EINVAL;
	ret=message_add_record(new_msg,return_info);
	if(ret<0)
		return ret;
	
	ret=ex_module_sendmsg(sub_proc,new_msg);
	return ret;
}

int proc_record_read(void * sub_proc,void * recv_msg)
{
	int ret;
	RECORD(RECORD_DEFINE,RECORD) * record_data;
	RECORD(RECORD_DEFINE,READ) * read_data;
	RECORD(USER_DEFINE,SERVER_STATE) * user_state;
	RECORD(USER_DEFINE,RETURN) * return_info;
	void * new_msg;
	
	ret=message_get_record(recv_msg,&read_data,0);
	if(ret<0)
		return ret;
// find the user state, 
	DB_RECORD * db_record;

	// find the record
	//读的时候根据read.msg的需求来读，不限制订单号
	db_record=memdb_find_first(TYPE_PAIR(RECORD_DEFINE,RECORD),"Pay_no",read_data->Pay_no);
	if(db_record==NULL)
	{
	//	record_data=Talloc0(sizeof(*record_data));
		printf("\033[43;37;5m!!!\033[0m无订单号为\"%s\"的订单，请查正后再读!\n", read_data->Pay_no);
		goto end;
	}
	else{
		record_data=db_record->record;
	}

	//  add read access control code begin
	

	//  add read access control code end

	new_msg=message_create(TYPE_PAIR(RECORD_DEFINE,RECORD),recv_msg);	
	if(new_msg==NULL)
		return -EINVAL;
	ret=message_add_record(new_msg,record_data);
	if(ret<0)
		return ret;
	
	ret=ex_module_sendmsg(sub_proc,new_msg);
	return ret;
	end:;
}
