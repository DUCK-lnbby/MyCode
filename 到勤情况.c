#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Imformation
{
	int number;
	char name[10];
	char gender[10];
	int month;
	int day;
	char ID[15]; 
	struct Imformation * next;
}Imformation;
Imformation *createList(Imformation * head,int number,char name[],char gender[],int month,int day,char ID[])
{
	Imformation * p;
	p=(Imformation *)malloc(sizeof(Imformation));
	p->next=NULL;
	head->next=p;
	p->number=number;
	strcpy(p->name,name);
	strcpy(p->gender,gender);
	p->month=month;
	p->day=day;
	strcpy(p->ID,ID);
	return p;
}
Imformation* getInformation()
{
	int number;
	char name[10];
	char gender[10];
	int year;
	int month;
	int day;
	char ID[15];
	
	Imformation * p,*head;
	FILE * f;
	head=p=(Imformation *)malloc(sizeof(Imformation));
	p->next=NULL;
	if((f=fopen("上课到勤情况.txt","r"))==NULL)
	{
		printf("无法打开文件");
		exit(0);
	}
	while(!feof(f))
	{
		fscanf(f,"%s %s %s\n",&name,&gender,&ID);
		p=createList(p,number,name,gender,month,day,ID);
	}
	fclose(f);
	return head;
} 
void saveName(Imformation * head)
{
	char name[10];
	
	char reason[100]; 
	FILE * f;
	Imformation *p=head->next;
	printf("请输入缺勤同学的座号：");
	gets(name);
	if((f=fopen("上课到勤情况.txt","w"))==NULL)
	{
		printf("文件打开失败");
		exit(0);
	} 
	while(p)
	{
		if(strcmp(p->name,name)==0)
		{
			printf("请输入该同学于xx课缺勤，以及其缺勤的原因：（例：2021年5月8日微机原理请假）\n");
			gets(reason);
			fprintf(f,"%d %s %s %s\n",p->number,p->name,p->gender,p->ID);
		}
		
		p=p->next;
	}
	fclose(f);
}
int main()
{
	return 0;
}

