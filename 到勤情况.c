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
	if((f=fopen("�Ͽε������.txt","r"))==NULL)
	{
		printf("�޷����ļ�");
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
	printf("������ȱ��ͬѧ�����ţ�");
	gets(name);
	if((f=fopen("�Ͽε������.txt","w"))==NULL)
	{
		printf("�ļ���ʧ��");
		exit(0);
	} 
	while(p)
	{
		if(strcmp(p->name,name)==0)
		{
			printf("�������ͬѧ��xx��ȱ�ڣ��Լ���ȱ�ڵ�ԭ�򣺣�����2021��5��8��΢��ԭ����٣�\n");
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

