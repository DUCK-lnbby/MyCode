#include<stdio.h>
#define MAX 100			//最大顶点数 
typedef char DataType;	//设置顶点类型为字符型 
typedef struct gragh	//
{
	DataType ver[MAX+1];	//ver用于存放途中各顶点的数据值 
	int edg[MAX+1][MAX+1]; 	//edg用于存放图的邻接矩阵 
} Gragh;
void CreateMGragh(Gragh * g,int e,int n) //n为顶点，e为个数  构造无向图邻接矩阵的算法 
{
	int i,j,k;
	printf("请输入图的结点信息：\n");
	for(i=0;i<=n;i++)
	{
		scanf("%c",&g->ver[i]);//读顶点信息 
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			g->edg[i][j]=0;		//初始化邻接矩阵	 
		}
	}
	for(k=1;k<=e;k++)			//输入e的边 
	{
		printf("请输入图的边(i,j):\n");
		scanf("%d,%d",&i,&j);
		g->edg[i][j]=1;
		g->edg[j][i]=1;
	}
}
int main()
{
	return 0;
}

