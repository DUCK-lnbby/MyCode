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
void PrintInformation(Imformation * head)
{
	Imformation * p=head->next;
	while(p)
	{
		printf("座号：%-2d 姓名：%-7s %-s 生日：%-2d/%-2d 学号：%-s\n",p->number,p->name,p->gender,p->month,p->day,p->ID);
		p=p->next;
	}
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
Imformation * writeInformation()
{
	int number;
	char name[10];
	char gender[10];
	int year;
	int month;
	int day;
	char ID[15];
	
	int i=0,x;
	Imformation * head,*I;
	head=I=(Imformation *)malloc(sizeof(Imformation));
	I->next=NULL;
	printf("请输入全班的人数：");
	scanf("%d",&x);
	getchar();
	printf("请输入座号、姓名、性别、出生月/日、学号");
	for(i=0;i<x;i++)
	{
		scanf("%d %s %s %d/%d %s",&number,&name,&gender,&month,&day,&ID);
		I=createList(I,number,name,gender,month,day,ID);
	}
	return head;
}
void saveImformation(Imformation * head)
{
	FILE * f;
	Imformation *p=head->next;
	if((f=fopen("班级成员信息.txt","w"))==NULL)
	{
		printf("文件打开失败");
		exit(0);
	} 
	while(p)
	{
		fprintf(f,"%d %s %s %d/%d %s\n",p->number,p->name,p->gender,p->month,p->day,p->ID);
		p=p->next;
	}
	fclose(f);
}
void createNewInformation() 
{
	Imformation * insert;
	int number;
	char name[10];
	char gender[10];
	int year;
	int month;
	int day;
	char ID[15];
	
	Imformation * head;
	Imformation * p=head->next;
	printf("请输入转班同学的座号、姓名、性别、出生月/日、学号");
	scanf("%d %s %s %d/%d %s",&number,&name,&gender,&month,&day,&ID);
	insert=createList(insert,number,name,gender,month,day,ID);
	head=getInformation(head);
	
	while(p)
	{
		if(p->number==insert->number-1)
		{
			insert->next=p->next;
			p->next=insert;
			break;
		}
		p=p->next;
	}
}
void deletInformation()
{
	int x;
	Imformation * head;
	head=getInformation(head);
	Imformation* p=head->next,*t;
	printf("请输入转出本班级学生的座位号：");
	scanf("%d",&x);
	while(p)
	{
		if(p->number==x)
		{
			t=head->next;
			head->next=head->next->next;
			free(t); 
		}
		p=p->next;
		head=head->next;
	} 
} 
void modifyInformation()
{
	int number;
	char name[10];
	char gender[10];
	int year;
	int month;
	int day;
	char ID[15];
	
	int x;
	Imformation * head,*p;
	head=getInformation(head);
	p=head->next;
	printf("请输入需要修改信息同学的座号：");
	scanf("%d",&x);
	while(p)
	{
		if(p->number==x)
		{
			printf("%d %s %s %d/%d %s\n",p->number,p->name,p->gender,p->month,p->day,p->ID);
			printf("请选择需要修改的属性：1、座号；2、姓名；3、性别；4、出生年月；5、学号"); 
			scanf("%d",x);
			switch(x)
			{
				case 1:
					{
						printf("请输入修改后的座号：");
						scanf("%d",&number);
						p->number=number;
						break;
					}
				case 2:
					{
						printf("请输入修改后的姓名：");
						scanf("%s",&name);
						strcpy(p->name,name);
						break;
					}
				case 3:
					{
						printf("请输入修改后的性别：");
						scanf("%s",&gender);
						strcpy(p->gender,gender);
						break;
					}
				case 4:
					{
						printf("请输入修改后的出生年月：（中间用空格隔开）");
						scanf("%d%d",&month,&day);
						p->month=month;
						p->day=day;
						break;
					}
				case 5:
					{
						printf("请输入修改后的学号：");
						scanf("%s",&ID);
						strcpy(p->ID,ID); 
						break;
					}
				default :printf("输入的功能选项有误");
			}
		}
		p=p->next;
	}
}
void searchInformation()
{
	char name[15];
	
	Imformation * head,*p;
	head=getInformation(head);
	p=head->next;
	printf("请输入查询的学生姓名：");
	scanf("%s",&name);
	while(p)
	{
		if(strcmp(p->name,name)==0)
		{
			printf("座号：%-2d 姓名：%-7s %-s 生日：%-2d/%-2d 学号：%-s\n",p->number,p->name,p->gender,p->month,p->day,p->ID);
			break;
		}
		p=p->next;
	}
	if(p==NULL) printf("未找到该学生"); 
} 

int main()
{
	//struct tm * lt;
	Imformation * head;
	//head=writeInformation();		//这是写入学生信息 
	//saveImformation(head);		//这是使用链表保存学生信息 
	head=getInformation(head);	//这是获取到文件中的学生信息 
	//PrintInformation(head);		//这是打印学生信息 
	//searchInformation();			//查询学生信息  
	return 0;
}

