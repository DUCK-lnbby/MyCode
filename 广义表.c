#include<stdio.h>
#include<stdlib.h>
/*typedef struct GLNodeType
{
	int tag;		//Ԫ������־��ֵΪ0��ʾԭ�ӣ�ֵΪ1��ʾ�ӱ� 
	union			//Ԫ����Ϣ�򣬹��������ͣ���������Ԫ�طֱ��Ų�ͬ����Ϣ 
	{
		char atom;
		struct {	//ԭ�ӽ����Ϣ����ͷβ����ָ��������ɣ��ֱ��ű�ͷ�ͱ�βָ�� 
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
GLNode * create()		//�����Ĵ��� 
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
void Print(GLNode * GL)	//��������� 
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

int Length(GLNode * GL)	//������ĳ��� 
{
	int n=0;
	GL=GL->info.link;//GLָ�������еĵ�һ����� 
	while(GL!=NULL)
	{
		n++;
		GL=GL->next; 
	}
	return n;
}
int Depth(GLNode * GL)	//���������� 
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

