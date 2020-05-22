#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*naive string-matching algorithm,T为原始字符串，P为需要匹配的字符串*/
void naiveMatch(char *T,char *P)
{
    int lenT,lenP,i,j;
    lenT=strlen(T);
    lenP=strlen(P);
    if(lenT<lenP)/*需要匹配的字符串比原始字符串还要长出错*/
    {
        perror("input error");
        return ;
    }
    for(i=0;i<(lenT-lenP+1);i++)
    {
        for(j=0;j<lenP;j++)
        {
            if(T[i+j]!=P[j])
                break;
        }
        if(j==lenP)
            printf("string match at place %d\n",i);
    }
}

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
	message=fopen("/root/centoscloud/cube-1.3/example/webmsgecho/message.log","r");    
	char ch[800]="0";
	fread((void *)(ch),1,800,message);
	
	
	char b[]="message";
	int len=strlen(b);
    int *next;
    int x[4];
    next=(int*)malloc(sizeof(int)*len);
    getNext(b,next);
    kmp(ch,b,next,x);/*测试kmp算法*/

    char str1[50]="";
    char str2[3]="";
    char str3[20]="";
    char str4[10]="";
    int i,j=0;
    for(i=x[0]+10;ch[i]!=0x22;i++)
    {
    	str1[j]=ch[i];
    	j++;
	}
	
	int k,l=0;
	for(k=x[1]+10;ch[k]!=0x22;k++)
    {
    	str2[l]=ch[k];
    	l++;
	}
	
	int i1,j1=0;
    for(i1=x[2]+10;ch[i1]!=0x22;i1++)
    {
    	str3[j1]=ch[i1];
    	j1++;
	}
	
	int k1,l1=0;
	for(k1=x[3]+10;ch[k1]!=0x22;k1++)
    {
    	str4[l1]=ch[k1];
    	l1++;
	}
	
	FILE *write=NULL;
	write=fopen("/root/centoscloud/cube-userdefine/instance/guke001/write.msg","w");
	fputs("{\n	\"type\":\"RECORD_DEFINE\",\n	\"subtype\":\"WRITE\",\n	\"mode\":\"INT\"\n}\n{\n	\"Goods_name\":\"",write);
	fputs(str1,write);
	fputs("\",\n 	\"Goods_num\":\"",write);
	fputs(str2,write);
	fputs("\",\n 	\"Rec_addr\":\"",write);
	fputs(str3,write);
	fputs("\",\n 	\"isReceived\":\"",write);
	fputs(str4,write);
	fputs("\",\n}",write);
	fclose(message);
	fclose(write);

	FILE *message2=NULL;
      message2=fopen("/root/centoscloud/cube-1.3/example/webmsgecho/message.log","w");
	fclose(message2);
	return 0;
}
