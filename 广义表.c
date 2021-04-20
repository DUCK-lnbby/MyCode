#include<stdio.h>
#include<stdlib.h>
/*typedef struct GLNodeType
{
	int tag;		//元素类别标志域，值为0表示原子，值为1表示子表 
	union			//元素信息域，共用体类型，对于两类元素分别存放不同的信息 
	{
		char atom;
		struct {	//原子结点信息域，由头尾两个指针数据项构成，分别存放表头和表尾指针 
			struct GLNodeType * head; 
			struct GLNodeType * tail;
		}sublist;
	}info;
} GLNode;*/
typedef struct GLNodeType
{
	int tag;
	union
	{
		char atom;
		struct GLNodeType * link;
	}info;
	struct GLNodeType * next; 
} GLNode;
GLNode * create()		//广义表的创建 
{
	char ch;
	GLNode * GL=NULL;
	scanf("%c",&ch);
	if(ch!=';')
	{
		GL=(GLNode *)malloc(sizeof(GLNode));
		if(ch=='(')
		{
			GL->tag=1;
			GL->info.link=create();
		} else
		{
			if(ch==')')
			{
				GL=NULL;
			}else
			{
				GL->tag=0;
				GL->info.atom=ch;
			}
		}
	}else
	{
		GL=NULL;
	}
	if(GL!=NULL)
	{
		scanf("%c",&ch);
		if(ch==',') GL->next=create();
		else GL->next=NULL;
	}
	return GL;
}
void Print(GLNode * GL)	//广义表的输出 
{
	if(GL!=NULL)
	{
		if(GL->tag==1)
		{
			printf("(");
			if(GL->info.link==NULL) printf("");
			else Print(GL->info.link);
			printf(")");
		}
	}else
	{
		printf("%c",GL->info.link);
	}
	if(GL->next!=NULL)
	{
		printf(",");
		Print(GL->next);
	}
}

int Length(GLNode * GL)	//求广义表的长度 
{
	int n=0;
	GL=GL->info.link;//GL指向链表中的第一个结点 
	while(GL!=NULL)
	{
		n++;
		GL=GL->next; 
	}
	return n;
}
int Depth(GLNode * GL)	//求广义表的深度 
{
	int d;
	int max=0;
	if(GL->tag==0) 
		return 0;
	GL=GL->info.link;
	if(GL==NULL)
		return 1;
	while(GL!=NULL)
	{
		if(GL->tag==1)
		{
			d=Depth(GL);
			if(d>max) max=d;
		}
		GL=GL->next;
	}
	return (max+1);
}
int Search(GLNode * GL,char x)
{
	while(GL!=NULL)
	{
		if(GL->tag==1)
		{
			if(Search(GL->info.link,x)) return 1;
		}else
		{
			if(GL->info.atom==x) 
				return 1;
		}
		GL=GL->next;
	}
	return 0;
}
int main()
{
	GLNode * p;
	
	return 0;
}

