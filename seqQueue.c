#include<stdio.h>
#include<stdlib.h>
#define MAXLEN 100
typedef struct seqQueue
{
	int queue[MAXLEN+1];
	int front,rear;
}seqQueue;
seqQueue * IniQueue()
{
	seqQueue * sq;
	sq=(seqQueue *)malloc(sizeof(seqQueue));
	if(sq==NULL)
	{
		printf("申请失败");
		return NULL;
	}
	sq->front=1;
	sq->rear=1;
	return sq;
}
int AddQueue(seqQueue * sq,int x)
{
	if(sq->rear% MAXLEN + 1==sq->front)
	{
		printf("\n队列已满");
		return 0;
	}
	sq->rear=sq->rear%MAXLEN + 1;
	sq->queue[sq->rear]=x;
	return 1;
}
int delQueue(seqQueue * sq,int * px )
{
	if(sq->front==sq->rear)
	{
		printf("\n队列已空");
		return 0;
	}
	sq->front=sq->front%MAXLEN + 1;
	*px=sq->queue[sq->front];
	return 1;
}
int main()
{
	int i,x;
	seqQueue * s;
	s=IniQueue();
	for(i=0;i<10;i++)
	{
		AddQueue(s,i);
	}
	for(i=0;i<10;i++)
	{
		delQueue(s,&x);
		printf("%d ",x);
	}
	return 0;
}

