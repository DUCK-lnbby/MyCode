#include <stdio.h>
#include <stdlib.h>
typedef struct link
{
	int data;
	struct link *next;
}link;
typedef struct
{
	link *front;
	link *rear;
}LinkQueue;
LinkQueue * init()
{
	LinkQueue * q;
	q=(LinkQueue *)malloc(sizeof(LinkQueue));
	if(q==NULL)
	{
		printf("创建失败");
		exit(0);
	}
	else
	{
		q->front=(link *)malloc(sizeof(link));
		q->front->next=NULL;
		if(q->front==NULL)
		{
			printf("创建失败");
			exit(0);
		}else
		{
			q->rear=q->front;
			return q;	
		}
	}
}
int empty(LinkQueue * p)
{
	if(p->front->next==NULL) return 0;
	return 1;
}
void push(LinkQueue * p,int data)
{
	link * newList=(link *)malloc(sizeof(link));
	newList->next=NULL;
	if(newList==NULL)
	{
		printf("创建失败");
		exit(0); 
	}
	newList->data=data;
	p->rear->next=newList;
	p->rear=newList;
}
void pop(LinkQueue * p,int *x)
{
	link * t;
	if(p->front->next==NULL)
	{
		printf("队列为空");
		exit(0);
	}else
	{
		t=p->front->next;
		*x=t->data; 
		p->front->next=t->next;
		free(t);
		if(p->front->next==NULL)
		{
			p->rear=p->front;
		}
	}
}
int main()
{
	int x,i;
	LinkQueue *q;
	q=init();
//	do
//	{
//		scanf("%d",&x);
//		push(q,x);
//	}while(getchar()==' ');
	for(i=0;i<10;i++)
	{
		push(q,i);
	}
	while(empty(q))
	{
		pop(q,&x);
		printf("%d",x);
	}
	return 0;
 }
