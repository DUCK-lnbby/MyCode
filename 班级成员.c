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
		printf("���ţ�%-2d ������%-7s %-s ���գ�%-2d/%-2d ѧ�ţ�%-s\n",p->number,p->name,p->gender,p->month,p->day,p->ID);
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
	if((f=fopen("�༶��Ա��Ϣ.txt","r"))==NULL)
	{
		printf("�޷����ļ�");
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
	printf("������ȫ���������");
	scanf("%d",&x);
	getchar();
	printf("���������š��������Ա𡢳�����/�ա�ѧ��");
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
	if((f=fopen("�༶��Ա��Ϣ.txt","w"))==NULL)
	{
		printf("�ļ���ʧ��");
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
	printf("������ת��ͬѧ�����š��������Ա𡢳�����/�ա�ѧ��");
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
	printf("������ת�����༶ѧ������λ�ţ�");
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
	printf("��������Ҫ�޸���Ϣͬѧ�����ţ�");
	scanf("%d",&x);
	while(p)
	{
		if(p->number==x)
		{
			printf("%d %s %s %d/%d %s\n",p->number,p->name,p->gender,p->month,p->day,p->ID);
			printf("��ѡ����Ҫ�޸ĵ����ԣ�1�����ţ�2��������3���Ա�4���������£�5��ѧ��"); 
			scanf("%d",x);
			switch(x)
			{
				case 1:
					{
						printf("�������޸ĺ�����ţ�");
						scanf("%d",&number);
						p->number=number;
						break;
					}
				case 2:
					{
						printf("�������޸ĺ��������");
						scanf("%s",&name);
						strcpy(p->name,name);
						break;
					}
				case 3:
					{
						printf("�������޸ĺ���Ա�");
						scanf("%s",&gender);
						strcpy(p->gender,gender);
						break;
					}
				case 4:
					{
						printf("�������޸ĺ�ĳ������£����м��ÿո������");
						scanf("%d%d",&month,&day);
						p->month=month;
						p->day=day;
						break;
					}
				case 5:
					{
						printf("�������޸ĺ��ѧ�ţ�");
						scanf("%s",&ID);
						strcpy(p->ID,ID); 
						break;
					}
				default :printf("����Ĺ���ѡ������");
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
	printf("�������ѯ��ѧ��������");
	scanf("%s",&name);
	while(p)
	{
		if(strcmp(p->name,name)==0)
		{
			printf("���ţ�%-2d ������%-7s %-s ���գ�%-2d/%-2d ѧ�ţ�%-s\n",p->number,p->name,p->gender,p->month,p->day,p->ID);
			break;
		}
		p=p->next;
	}
	if(p==NULL) printf("δ�ҵ���ѧ��"); 
} 

int main()
{
	//struct tm * lt;
	Imformation * head;
	//head=writeInformation();		//����д��ѧ����Ϣ 
	//saveImformation(head);		//����ʹ��������ѧ����Ϣ 
	head=getInformation(head);	//���ǻ�ȡ���ļ��е�ѧ����Ϣ 
	//PrintInformation(head);		//���Ǵ�ӡѧ����Ϣ 
	//searchInformation();			//��ѯѧ����Ϣ  
	return 0;
}

