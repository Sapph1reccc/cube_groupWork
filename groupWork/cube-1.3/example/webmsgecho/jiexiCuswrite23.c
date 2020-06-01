#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*kmp预处理需要的匹配串*/
void getNext(char *p,int next[])
{
    int len,i,j;
    len=strlen(p);
    next[0]=0;
    for(i=1;i<len;i++)
    {
        j=next[i-1];
        while((p[i-1]!=p[j-1])&&(j!=0))
        {
            j=next[j-1];
//            printf("j= %d\n",j);
        }
        next[i]=j+1;
    }
}

/*kmp字符串匹配算法*/
void kmp(char *t,char *p,int next[],int x[])
{
    int lent,lenp,i,j;
    int count=0;
    lent=strlen(t);
    lenp=strlen(p);
    i=0;
    j=0;
    while(i<(lent))
    {
        if((j==-1)||(t[i]==p[j]))
        {
            i++;
            j++;

//            printf("i=%d,j=%d\n",i,j);
        }
        else
        {
           
//            printf("in else i=%d,j=%d\n",i,j);
            j=next[j]-1;
        }
        if(j==(lenp))
        {
        	x[count]=i-lenp;
        	count++;
        }
    }
}

int main()
{
//dfh
/*	int t=(len1-1)*29;
	int s1;
	char recordno[27];
	int w1=0;
	for(s1=t;s1<t+27;s1++)
	{
		recordno[w1]=cc[s1];
		w1++;
	}
	printf("%s\n",recordno);
*/

	FILE *message=NULL;
	message=fopen("/root/groupWork/cube-1.3/example/webmsgecho/message.log","r");    
	char ch[1000];
	fread((void *)(ch),1,1000,message);
	char b[]="message";
	int len=strlen(b);
    int *next;
    int x[4];
    next=(int*)malloc(sizeof(int)*len);
    getNext(b,next);
    kmp(ch,b,next,x);/*测试kmp算法*/

    char str0[10];
    char str2[10];
    char str3[50];

	int i0,j0=0;
    for(i0=x[0]+10;ch[i0]!=0x22;i0++)
    {
    	str0[j0]=ch[i0];
    	j0++;
	}
	str0[j0] = '\0';
	int k,l=0;
	for(k=x[2]+10;ch[k]!=0x22;k++)
    {
    	str2[l]=ch[k];
    	l++;
	}
	str2[l] = '\0';
	int i1,j1=0;
    for(i1=x[3]+10;ch[i1]!=0x22;i1++)
    {
    	str3[j1]=ch[i1];
    	j1++;
	}
	str3[j1] = '\0';
	printf("%s %s\t%d %d\n", str2, str3, strlen(str2), strlen(str3));

	FILE *infono=NULL;
	char orderno_path[100] = "/root/groupWork/cube-userdefine/instance/";
	strcat(orderno_path, str0);
	strcat(orderno_path, "/ORDER_NO.txt");
	infono=fopen(orderno_path, "r");    
	char cc[1000];
	fscanf(infono, "%s\n", cc);
	printf("读出的订单号: %s\n",cc);
	printf("订单号长度: %d\n",strlen(cc));
	char recordno[27];
	int i;
	for(i = 0; cc[i] != '\0'; i++){
		recordno[i] = cc[i];
	}

	
	char path2[100] = "/root/groupWork/cube-userdefine/instance/";
	strcat(path2, str0);
	strcat(path2, "/write2.msg");
	FILE *write2 = fopen(path2, "w+");
	fputs("{\n	\"type\":\"RECORD_DEFINE\",\n	\"subtype\":\"WRITE\",\n	\"mode\":\"INT\"\n}\n{\n	\"Pay_no\":\"",write2);
	fputs(recordno, write2);
	fputs("\",\n	\"segment\":\"Goods_num\",\n	\"text\":\"",write2);
	fputs(str2,write2);
	fputs("\"\n}",write2);
	fclose(write2);
	
	char path3[100] = "/root/groupWork/cube-userdefine/instance/";
	strcat(path3, str0);
	strcat(path3, "/write3.msg");
	FILE *write3 = fopen(path3, "w+");
	fputs("{\n	\"type\":\"RECORD_DEFINE\",\n	\"subtype\":\"WRITE\",\n	\"mode\":\"INT\"\n}\n{\n	\"Pay_no\":\"",write3);
	fputs(recordno,write3);
	fputs("\",\n	\"segment\":\"Rec_addr\",\n	\"text\":\"",write3);
	fputs(str3,write3);
	fputs("\"\n}",write3);
	fclose(write3);

	FILE *message2=NULL;
      message2=fopen("/root/groupWork/cube-1.3/example/webmsgecho/message.log","w");
	fclose(message2);
	return 0;
}
