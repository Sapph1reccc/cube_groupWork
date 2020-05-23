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
	FILE *message=NULL;
	message=fopen("/root/groupWork/cube-1.3/example/webmsgecho/message.log","r");    
	char ch[1000]="0";
	fread((void *)(ch),1,1000,message);
	
	
	char b[]="message";
	int len=strlen(b);
    int *next;
    int x[4];
    next=(int*)malloc(sizeof(int)*len);
    getNext(b,next);
    kmp(ch,b,next,x);/*测试kmp算法*/
	char str0[10]="";
    char str1[50]="";
    char str2[3]="";
    char str3[20]="";
	
	int i0,j0=0;
    for(i0=x[0]+10;ch[i0]!=0x22;i0++)
    {
    	str0[j0]=ch[i0];
    	j0++;
	}

    int i,j=0;
    for(i=x[1]+10;ch[i]!=0x22;i++)
    {
    	str1[j]=ch[i];
    	j++;
	}
	
	int k,l=0;
	for(k=x[2]+10;ch[k]!=0x22;k++)
    {
    	str2[l]=ch[k];
    	l++;
	}
	
	int i1,j1=0;
    for(i1=x[3]+10;ch[i1]!=0x22;i1++)
    {
    	str3[j1]=ch[i1];
    	j1++;
	}

	char path1[100] = "/root/groupWork/cube-userdefine/instance/";
	strcat(path1, str0);
	strcat(path1, "/write1.msg");
	FILE *write1 = fopen(path1, "w+");
	fputs("{\n	\"type\":\"RECORD_DEFINE\",\n	\"subtype\":\"WRITE\",\n	\"mode\":\"INT\"\n}\n{\n	\"segment\":\"Goods_name\",\n	\"text\":\"",write1);
	fputs(str1,write1);
	fputs("\"\n}",write1);
	fclose(write1);
	
	char path2[100] = "/root/groupWork/cube-userdefine/instance/";
	strcat(path2, str0);
	strcat(path2, "/write2.msg");
	FILE *write2 = fopen(path2, "w+");
	fputs("{\n	\"type\":\"RECORD_DEFINE\",\n	\"subtype\":\"WRITE\",\n	\"mode\":\"INT\"\n}\n{\n	\"segment\":\"Goods_num\",\n	\"text\":\"",write2);
	fputs(str2,write2);
	fputs("\"\n}",write2);
	fclose(write2);
	
	char path3[100] = "/root/groupWork/cube-userdefine/instance/";
	strcat(path3, str0);
	strcat(path3, "/write3.msg");
	FILE *write3 = fopen(path3, "w+");
	fputs("{\n	\"type\":\"RECORD_DEFINE\",\n	\"subtype\":\"WRITE\",\n	\"mode\":\"INT\"\n}\n{\n	\"segment\":\"Rec_addr\",\n	\"text\":\"",write3);
	fputs(str3,write3);
	fputs("\"\n}",write3);
	fclose(write3);

	FILE *message2=NULL;
      message2=fopen("/root/groupWork/cube-1.3/example/webmsgecho/message.log","w");
	fclose(message2);
	return 0;
}
