#include<stdio.h>
#define MAX 100			//��󶥵��� 
typedef char DataType;	//���ö�������Ϊ�ַ��� 
typedef struct gragh	//
{
	DataType ver[MAX+1];	//ver���ڴ��;�и����������ֵ 
	int edg[MAX+1][MAX+1]; 	//edg���ڴ��ͼ���ڽӾ��� 
} Gragh;
void CreateMGragh(Gragh * g,int e,int n) //nΪ���㣬eΪ����  ��������ͼ�ڽӾ�����㷨 
{
	int i,j,k;
	printf("������ͼ�Ľ����Ϣ��\n");
	for(i=0;i<=n;i++)
	{
		scanf("%c",&g->ver[i]);//��������Ϣ 
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			g->edg[i][j]=0;		//��ʼ���ڽӾ���	 
		}
	}
	for(k=1;k<=e;k++)			//����e�ı� 
	{
		printf("������ͼ�ı�(i,j):\n");
		scanf("%d,%d",&i,&j);
		g->edg[i][j]=1;
		g->edg[j][i]=1;
	}
}
int main()
{
	return 0;
}

