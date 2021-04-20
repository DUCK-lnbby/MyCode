#include<stdio.h>
#include<stdlib.h>
typedef struct stackList
{
	int data;
	struct stackList * next;
}stackList;
stackList * IniStack()
{
	stackList * top;
	top=(stackList *)malloc(sizeof(stackList));
	if(top==NULL)
	{
		printf("ÉêÇë¿Õ¼äÊ§°Ü\n");
		exit(0);
	}else
	{
		top->next=NULL;
		return top;
	}
}
int empty(stackList * top)
{
	if(top->next==NULL)
	{
		printf("Õ»Îª¿Õ");
		return 1;
	}return 0; 
}
int push(stackList * top,int x)
{
	stackList * newList;
	newList=(stackList *)malloc(sizeof(stackList));
	if(top==NULL)
	{
		printf("ÉêÇë¿Õ¼äÊ§°Ü\n");
		exit(0);
	}
	newList->data=x;
	newList->next=top->next;
	top->next=newList; 
	return 1;
}
int pop(stackList * top,int * x)
{
	stackList * p;
	if(top->next==NULL)
	{
		printf("Õ»Îª¿Õ\n");
		return 0;
	}
	else
	{
		p=top->next;
		*x=p->data;
		top->next=p->next;
		free(p);
		return 1;
	}
}
int main()
{
	int i;
	stackList * s,*temp;;
	s=IniStack();
	for(i=0;i<10;i++)
	{
		push(s,i);
	}
	temp=s->next;
	while(temp)
	{
		printf("%d ",temp->data);
		temp=temp->next;
	}
	return 0;
}

