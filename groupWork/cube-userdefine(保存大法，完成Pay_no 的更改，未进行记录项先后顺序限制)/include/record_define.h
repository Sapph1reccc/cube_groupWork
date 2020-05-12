enum dtype_record_define {
	TYPE(RECORD_DEFINE)=0x3210
};
enum subtype_record_define {
	SUBTYPE(RECORD_DEFINE,RECORD)=0x1,
	SUBTYPE(RECORD_DEFINE,READ),
	SUBTYPE(RECORD_DEFINE,WRITE)
};

typedef struct record_define_record{
	char * Pay_no;	//把record_no直接改为Pay_no了
	char * Goods_name;
	char * Goods_num;
	char * Rec_addr;
	char * Deli_addr;
	char * isSent;
	char * isReceived;
	char * Goods_addr;
	char * isFinished;
}__attribute__((packed)) RECORD(RECORD_DEFINE,RECORD);

typedef struct record_define_read{
	char * Pay_no;
}__attribute__((packed)) RECORD(RECORD_DEFINE,READ);

typedef struct record_define_write{
	char * Pay_no;
	char * segment;
	char * text;
}__attribute__((packed)) RECORD(RECORD_DEFINE,WRITE);
