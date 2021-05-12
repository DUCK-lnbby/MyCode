#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
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
	if((f=fopen("班级成员信息.txt","r"))==NULL)
	{
		printf("无法打开文件");
		exit(0);
	}
	while(!feof(f))
	{
		fscanf(f,"%d %s %s %d/%d %s\n",&number,&name,&gender,&month,&day,&ID);
		p=createList(p,number,name,gender,month,day,ID);
	}
	fclose(f);
	return head;
} 
struct tm * getTime(struct tm * lt)
{
	time_t t;
	time(&t);
	lt=localtime(&t);
	//printf("%d/%d/%d\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday);
	return lt;
}
void remindBirthday()
{
	struct tm * lt;
	Imformation * head,*p;
	head=getInformation();
	p=head->next;
	lt=getTime(lt);
	while(p)
	{
		if(p->month==lt->tm_mon+1 && p->day==lt->tm_mday)
		{
			printf("%-7s 的生日到了！快给ta送上祝福吧！",p->number);
			break; 
		}
		p=p->next;
	}
}
int main()
{
	
	return 0;
}

