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
    int x[2];
    next=(int*)malloc(sizeof(int)*len);
    getNext(b,next);
    kmp(ch,b,next,x);/*测试kmp算法*/
	char str0[10]="";
    char str1[50]="";
	
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
	char path1[100] = "/root/groupWork/cube-userdefine/instance/";
	strcat(path1, str0);
	strcat(path1, "/write1.msg");
	FILE *write1 = fopen(path1, "w+");
	fputs("{\n	\"type\":\"RECORD_DEFINE\",\n	\"subtype\":\"WRITE\",\n	\"mode\":\"INT\"\n}\n{\n	\"segment\":\"Goods_name\",\n	\"text\":\"",write1);
	fputs(str1,write1);
	fputs("\"\n}",write1);
	fclose(write1);

	return 0;
}
