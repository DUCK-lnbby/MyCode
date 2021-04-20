#include<stdio.h>
#include<stdlib.h>
#define MAXLEN 10
typedef struct 
{
	int stack[MAXLEN+1];
	int top;
}stack;
stack * IniStack()
{
	stack * s;
	s=(stack*)malloc(sizeof(stack));
	if(s==NULL)
	{
		return NULL;
	}else
	{
		s->top=0;
		return s;
	}
}
int empty(stack * s)
{
	if(s->top==0) return 1;
	return 0;
}
int push(stack * s,int x)
{
	if(s->top==MAXLEN)
	{
		printf("Õ»ÒÑÂú\n");
		return 0;
	}
	s->top++;
	s->stack[s->top]=x;
	
	printf("%d ",s->stack[s->top]);
	return 1;
}
int pop(stack * s,int *x)
{
	if(s->top==0)
	{
		printf("Õ»ÒÑ¿Õ\n");
		return 0; 
	}else
	{
		//printf("%d ",s->stack[s->top]);
		*x=s->stack[s->top];
		s->top--;
		return 1;
	}
}
int getTop(stack * s,int * x)
{
	if(s->top==0)
	{
		printf("Õ»ÒÑ¿Õ\n");
		return 0; 
	}else
	{
		*x=s->stack[s->top-1];
		return 1;
	}
}
int main()
{
	stack * s;
	int whetherEmpty,x,i;
	s=IniStack();
	whetherEmpty=empty(s);
	switch(whetherEmpty)
	{
		case 1:printf("Õ»Îª¿Õ\n");break;
		case 2:printf("Õ»²»Îª¿Õ\n");break;
		
	}
	//printf("1");
	for(i=MAXLEN;i>0;i--)
	{
		push(s,i);
	}
	//getTop(s,x);
	//printf("Õ»¶¥Îª£º%d",*x);
	printf("\n");
	while(s->top)
	{
		whetherEmpty=pop(s,&x);
		printf("%d ",x);
	}
	return 0;
}

