#include<stdio.h>
#include<stdlib.h>
typedef struct link
{
	int data;
	struct link * next;
}link;
link * createList(link * head,int data)
{
	link * newList;
	newList=(link *)malloc(sizeof(link));
	newList->next=NULL;
	newList->data=data;
	head->next=newList;
	return newList;
}
int getListLength(link * head)
{
	link * temp=head->next;
	int x=0;
	while(temp)
	{
		x++;
		temp=temp->next;
	}
	return x;
}
void search(link *head,int move)
{
	int x=0;
	link * temp=head->next;
	while(temp && x<move)
	{
		temp=temp->next;
		x++;
	}
	printf("%d",temp->data);
}
int main()
{
	link * list,*p;
	int data, x,l;
	list=(link *)malloc(sizeof(link));
	p=list;
	scanf("%d",&x);
	do{
		scanf("%d",&data);
		list=createList(list,data);
	}while(getchar()==' ');
	l=getListLength(p);
	if(l-x<0)
	{
		printf("Not Found");
	}else
	{
		search(p,l-x);
	}
	return 0;
} 
