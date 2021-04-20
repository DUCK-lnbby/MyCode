#include<stdio.h>
#include<stdlib.h>
typedef struct BSTree
{
	int data;
	struct BSTree * lchild,*rchild;
}BSTree;
void create(BSTree **t)
{
	char ch;
	scanf("%c",&ch);
	if(ch=='*')
	{
		*t=NULL;
	}else
	{
		*t=(BSTree *)malloc(sizeof(BSTree));
		(*t)->data=ch;
		create(&((*t)->lchild));	//�ݹ鴴�������� 
		create(&((*t)->rchild));	//�ݹ鴴�������� 
	}
}
void xianxu(BSTree *p)
{
	if(p!=NULL)
	{
		printf("%c",p->data);
		xianxu(p->lchild);
		xianxu(p->rchild);
	}
}
void zhongxu(BSTree *p)
{
	if(p!=NULL)
	{
		zhongxu(p->lchild);
		printf("%c",p->data);
		zhongxu(p->rchild);
	}
}
void houxu(BSTree *p)
{
	if(p!=NULL)
	{
		houxu(p->lchild);
		houxu(p->rchild);
		printf("%c",p->data);
	}
}
int depth(BSTree *p)		//����������� 
{
	int n1,n2;
	if(p==NULL)
	{
		return 0;
	} else
	{
		n1=depth(p->lchild);
		n2=depth(p->rchild);
	}
	return n1>n2?n1+1:n2+1;
}
int leaf(BSTree *p)		//����Ҷ���� 
{
	int n=0;
	if(p!=NULL)
	{
		n+=leaf(p->lchild);		//ͳ���������е�Ҷ���� 
		if(p->lchild==NULL && p->rchild==NULL)
		{
			n+=1;				//��ΪҶ�ӽ���������1 
			n+=leaf(p->rchild);	//ͳ���������е�Ҷ�ӽ����� 
		}
	}
	return n;
}
int main()
{
	BSTree * p;
	create(&p);
	xianxu(p);
	printf("\n");
	zhongxu(p);
	printf("\n");
	houxu(p);
	return 0;
}

