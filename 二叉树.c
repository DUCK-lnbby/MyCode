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
		create(&((*t)->lchild));	//递归创建左子树 
		create(&((*t)->rchild));	//递归创建右子树 
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
int depth(BSTree *p)		//计算树的深度 
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
int leaf(BSTree *p)		//计算叶子数 
{
	int n=0;
	if(p!=NULL)
	{
		n+=leaf(p->lchild);		//统计左子树中的叶子数 
		if(p->lchild==NULL && p->rchild==NULL)
		{
			n+=1;				//若为叶子结点计数器加1 
			n+=leaf(p->rchild);	//统计右子树中的叶子结点个数 
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

