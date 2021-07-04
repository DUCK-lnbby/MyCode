#include<stdio.h>
#include<stdlib.h>
#define MAX 100			//最大顶点数 
#define MaxInt 32767	//最大权值 
int D1[MAX],P1[MAX],D[MAX][MAX];
typedef char VerTexType;//顶点类型 
typedef int ArcType;	//权值类型 
VerTexType P[MAX][MAX];
typedef struct {
	VerTexType vexs[MAX];	//顶点信息 
	ArcType arc[MAX][MAX];	//邻接矩阵 
	int visited[MAX]; 
	int vexnum,arcnum;		//顶点个数，边数 
}Gragh;
typedef enum {FALSE,TRUE} boolean;			//enum是一个新的关键字，专门用来定义枚举类型，这也是它在C语言中的唯一用途
typedef struct StackList{
	VerTexType data;
	struct StackList * next;
}StackList;
int Locatevex(Gragh * G,VerTexType x);		//获取到图的顶点位置 
void CreateUDN(Gragh * G);					//创建图 
void DestroyGragh(Gragh * G);				//销毁图 
VerTexType GetVex(Gragh * G,VerTexType x);	//返回图中顶点的信息 
void PutVex(Gragh * G,VerTexType v,VerTexType value);	//对顶点重新进行赋值 
VerTexType FirstAdjVex(Gragh * G,VerTexType x);			//返回第一个邻接顶点 
VerTexType NextAdjVex(Gragh * G,VerTexType x,VerTexType y);	//返回这个顶点的下下个邻接点
void InsertVex(Gragh * G,VerTexType x);			//插入一个顶点 
void DeleteArc(Gragh * G,VerTexType x);			//删除G中顶点x及其相关的弧
void InsertArc(Gragh * G,VerTexType x,VerTexType y);	//添加顶点之间的边(修改) 
void DeletVex(Gragh * G,VerTexType x,VerTexType y);		//删除边
void DFSTraverse(Gragh * G,VerTexType start);					//深度遍历
int CountVex(Gragh * G,VerTexType x);			//计算顶点的度 
void BFSTraverse(Gragh * G,VerTexType start);					//广度遍历 
void ClearVisted(Gragh * G);							//清除访问过的标记 
StackList * GetImfor(Gragh * G,VerTexType start);		//队列链存广度遍历结果
void Dijkstra(Gragh * G,VerTexType start);	//迪杰斯特拉算法求最短路径 
void Floyd(Gragh * G,VerTexType start,VerTexType end);		//弗洛伊德求两顶点之间的最短路径 
void ReadGragh(Gragh * G){
	FILE * f;
	VerTexType v1,v2;
	int weight,i,k,j;
	if((f=fopen("test.txt","r"))==NULL){
		printf("打开文件失败\n");
	}else{
		for(i=0;i<MAX;i++){
			G->visited[i]=0;
			for(j=0;j<MAX;j++){
				G->arc[i][j]=MaxInt;					//初始化邻接矩阵 
			}
		} 
		fscanf(f,"%d %d\n",&G->vexnum,&G->arcnum);	//输入顶点个数和边数
		for(i=0;i<G->vexnum;i++){
			fscanf(f,"%c ",&G->vexs[i]);
		}
		for(k=0;k<G->arcnum;k++){
			fscanf(f,"%c %c %d\n",&v1,&v2,&weight);
			i=Locatevex(G,v1);
			j=Locatevex(G,v2);
			if(i!=-1 && j!=-1){
				G->arc[i][j]=weight;
				G->arc[j][i]=weight;
			}else{
				k--; 
				printf("输入了不存在的顶点!\n");
			}
		}
	}
}

void Floyd(Gragh * G,VerTexType start,VerTexType end){
	int i,j,k;
	for(i=0;i<G->vexnum;i++)
	{
		for(j=0;j<G->vexnum;j++)
		{
			if(G->arc[i][j] != MaxInt){
				P[i][j]=j;
			}else{
				P[i][j]=-1;
			}
			D[i][j]=G->arc[i][j];
		}
	}
	for(k=0;k<G->vexnum;k++)
	{
		for(i=0;i<G->vexnum;i++)
		{
			for(j=0;j<G->vexnum;j++)
			{
				if(D[i][k]+D[k][j]<D[i][j]){
					D[i][j]=D[i][k]+D[k][j];
					P[i][j]=P[i][k];
				}
			}
		}
	}
	k=P[Locatevex(G,start)][Locatevex(G,end)];
	if(k==-1) printf("顶点 %c 到 %c 无路径！\n",start,end);
	else{
		printf("从顶点 %c 到 %c 的最短路径是：%c",start,end,start);
		while(k!=Locatevex(G,end)){                     
			printf("->%c",G->vexs[k]);
			k=P[k][Locatevex(G,end)];                          
		}        
		printf("->%c\n",G->vexs[Locatevex(G,end)]);
		printf("路径长度：%d\n",D[Locatevex(G,start)][Locatevex(G,end)]);
	}
}                                          
void Dijkstra(Gragh * G,VerTexType start){ 
	//Dijkstra算法求有向图G的v1顶点到其他顶点v的最短路径P[v]及其权D[v]
	//设G是有向图的邻接矩阵，若<i,j>不存在，则M[i][j]=ManInt
	//S[v]为真当且仅当v∈S,即已经求得v1到v的最短路径      
	int D2[MAX],P2[MAX];
	int v,i,w,min;
	int v1;
	v1=Locatevex(G,start);
	boolean S[MAX];
	for(v=0;v<G->vexnum;v++)			//初始化S和D 
	{
		S[v]=FALSE;				//置空最短路径终点集 
		D2[v]=G->arc[v1][v];	//初始化最短路径值 
		if(D2[v]<MaxInt){
			P2[v]=v1;			//v1是v的前驱（双亲） 
		}else{
			P2[v]=0;			//v没有前驱 
		}
	}
	D2[v1]=0;S[v1]=TRUE;		//S集初始化时只有源点，源点到源点的距离为0
	//开始循环，每次求得v1到某个顶点的最短路径，并将v加到S集中 
	for(i=1;i<G->vexnum;i++)			//其余n-1个顶点 
	{
		min=MaxInt;
		for(w=0;w<G->vexnum;w++)
			if(!S[w] && D2[w]<min){	//w顶点离v1顶点更近 
				v=w;
				min=D2[w];
			}
			S[v]=TRUE;
			for(w=0;w<G->vexnum;w++)		//更新当前最短路径以及距离 
				if(!S[w] && (D2[v]+G->arc[v][w]<D2[w])){
					D2[w]=D2[v]+G->arc[v][w];	//修改D2[w]和P2[w] 
					P2[w]=v;
				}
	}                    
	printf("路径长度    路径\n");
	for(i=0;i<G->vexnum;i++){
		printf("%5d",D2[i]);
		printf("%5c",G->vexs[i]);
		//printf("%5c",i);
		v=P2[i];
		while(v!=0){
			printf("<-%c",G->vexs[v]);
			//printf("<-%d",v);
			v=P2[v];    
		}
		//printf("<-%c",start);
		printf("\n");  
	}
} 
void ClearVisted(Gragh * G){
	int i;
	for(i=0;i<G->vexnum;i++){
		G->visited[i]=0;
	}
}
void BFSTraverse(Gragh * G,VerTexType start){
	int x,i;
	StackList * head, * temp,* d;
	x=Locatevex(G,start);
	head=(StackList *)malloc(sizeof(StackList));
	head->next=NULL;
	head->data=GetVex(G,start);
	while(head){
		if(G->visited[Locatevex(G,head->data)]==0){
			printf("%c ",head->data);
			G->visited[Locatevex(G,head->data)]=1;
		}
		temp=head;
		while(temp->next){
			temp=temp->next;
		}
		temp->next=GetImfor(G,head->data);
		d=head;
		head=head->next;
		free(d);
	}
}
StackList * GetImfor(Gragh * G,VerTexType start){
	int i,x;
	StackList * head,* rear,* temp;
	x=Locatevex(G,start);
	temp=head=(StackList *)malloc(sizeof(StackList));
	temp->next=head->next=NULL;
	for(i=0;i<G->vexnum;i++){
		if(G->arc[x][i]!=MaxInt && G->visited[i]==0){
			rear=(StackList *)malloc(sizeof(StackList));
			rear->next=NULL;
			rear->data=G->vexs[i];
			temp->next=rear;
			temp=temp->next;
			//G->visited[i]=1;
		}
	}
	if(head->next) return head->next;
	else return NULL;
}
int CountVex(Gragh * G,VerTexType x){
	int i,k;
	int count=0;
	k=Locatevex(G,x);
	for(i=0;i<G->vexnum;i++){
		if(G->arc[k][i]!=MaxInt) count++;
	} 
	return count;
}
void DFSTraverse(Gragh * G,VerTexType start){
	int i,x;
	x=Locatevex(G,start);							//当前顶点的位置 
	if(GetVex(G,start)!=' ' && G->visited[x]==0){
		printf("%c ",GetVex(G,start));
		G->visited[x]=1;
	}
	for(i=0;i<G->vexnum;i++){
		if(G->visited[i]==0 && G->arc[x][i]!=MaxInt){
			DFSTraverse(G,G->vexs[i]);
		}
	}
}
void DeletVex(Gragh * G,VerTexType x,VerTexType y){
	int i,j;
	i=Locatevex(G,x);
	j=Locatevex(G,y);
	if(i!=-1 && j!=-1){
		G->arc[i][j]=MaxInt;
		G->arc[j][i]=MaxInt;
	}else{
		printf("传入了不存在的顶点!\n");
	}
}
void InsertArc(Gragh * G,VerTexType x,VerTexType y){
	int i,j,weight;
	printf("输入两者之间的路径长度：\n");
	scanf("%d",&weight);
	getchar();
	i=Locatevex(G,x);
	j=Locatevex(G,y);
	if(i!=-1 && j!=-1){
		G->arc[i][j]=weight;
		G->arc[j][i]=weight;
	}else{
		printf("输入了不存在的顶点!\n");
	}
}
void DeleteArc(Gragh * G,VerTexType x){
	int k,i,j,m;
	k=Locatevex(G,x);
	printf("k=%d\n",k); 
	for(i=0;i<G->vexnum;i++){
		if(G->arc[k][i]!=MaxInt){
			m++;
		}
	}
	for(i=k;i<G->vexnum;i++){
		G->vexs[i]=G->vexs[i+1];
	}
	for(j=k;j<G->vexnum;j++){				//将删除的顶点信息由后往前进行覆盖，会出现对角线上有错误，排除错误在下面 
		for(i=0;i<G->vexnum;i++){
			G->arc[i][j]=G->arc[i][j+1];
			G->arc[j][i]=G->arc[j+1][i];
		}
	}
	for(i=0;i<G->vexnum;i++){
		G->arc[i][G->vexnum-1]=MaxInt;
		G->arc[G->vexnum-1][i]=MaxInt;
	}
	G->vexnum--;							//减去顶点数 
	G->arcnum-=m;							//减去边数 
	for(i=0;i<G->vexnum;i++){					//初始化对角线 
		G->arc[i][i]=MaxInt;
	}
} 
void InsertVex(Gragh * G,VerTexType x) {
	int i,j,k;
	int vexnum,arcnum,weight;
	VerTexType v1,v2;					//两个顶点
	G->vexs[(G->vexnum++)]=x;
	printf("输入新增的边数：\n");
	scanf("%d",&arcnum);
	getchar();
	G->arcnum+=arcnum;
	for(k=0;k<arcnum;k++){
		printf("输入顶点1、顶点2以及两者之间的路径长度：(还需%d条)\n",arcnum-k);
		scanf("%c",&v1);
		getchar();
		scanf("%c",&v2);
		getchar();
		scanf("%d",&weight);
		getchar();
		i=Locatevex(G,v1);
		j=Locatevex(G,v2);
		if(i!=-1 && j!=-1){
			G->arc[i][j]=weight;
			G->arc[j][i]=weight;
		}else{
			k--; 
			printf("输入了不存在的顶点!\n");
		}
	}
}
VerTexType NextAdjVex(Gragh * G,VerTexType x,VerTexType y){
	int i,j;
	int k,l;
	k=Locatevex(G,x);
	l=Locatevex(G,y);
	if(k!=-1 && l!=-1){
		if(G->arc[k][l]!=MaxInt){
			 for(i=l+1;i<G->vexnum;i++){
			 	if(G->arc[k][i]!=MaxInt) return G->vexs[i];
			 }
			 return ' ';
		}
	}else{
		printf("在图中没有该路线\n");
	}
}
VerTexType FirstAdjVex(Gragh * G,VerTexType x){
	int i,j;
	for(i=0;i<G->vexnum;i++){
		if(x==G->vexs[i]){
			break; 
		}
	}
	for(j=0;j<G->vexnum;j++){
		if(G->arc[i][j]!=MaxInt){
			return G->vexs[j];
		}
	}
	return ' ';
}
void PutVex(Gragh * G,VerTexType v,VerTexType value){
	int i;
	for(i=0;i<G->vexnum;i++){
		if(v==G->vexs[i]){
			G->vexs[i]=value;
		}
	}
}
VerTexType GetVex(Gragh * G,VerTexType x){
	int i;
	for(i=0;i<G->vexnum;i++){
		if(x==G->vexs[i]){
			return x;
		}
	}
	return ' ';
}
void DestroyGragh(Gragh * G){
	int i,j;
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arc[i][j]=MaxInt;
		}
	} 
}
int Locatevex(Gragh * G,VerTexType x){
	int i;
	for(i=0;i<G->vexnum;i++){
		if(x==G->vexs[i]){
			return i;
		}
	}
	return -1;
}
void CreateUDN(Gragh * G){
	FILE * f;
	char Imfor[20];
	int i,j,k;
	VerTexType v1,v2;					//两个顶点 
	ArcType weight;						//路经长度 
	for(i=0;i<MAX;i++){
		G->visited[i]=0;
		for(j=0;j<MAX;j++){
			G->arc[i][j]=MaxInt;					//初始化邻接矩阵 
		}
	} 
	if((f=fopen("ARC.txt","w"))==NULL)		
	{
		printf("文件不能打开!\n");
		exit(0);
	}else{
		printf("输入顶点个数和边数:\n");
		scanf("%d%d",&G->vexnum,&G->arcnum);	//输入顶点个数和边数
		fprintf(f,"%d %d\n",G->vexnum,G->arcnum);
		printf("输入各个顶点：\n");
		getchar();
		for(i=0;i<G->vexnum;i++){
			scanf("%c",&G->vexs[i]);
			fprintf(f,"%c ",G->vexs[i]);
			getchar();
		}
		fprintf(f,"\n");
//		for(i=0;i<G->vexnum;i++){
//			printf("%c ",G->vexs[i]);
//		}
//		printf("\n");
		
		for(k=0;k<G->arcnum;k++){
			printf("输入顶点1、顶点2以及两者之间的路径长度：\n");
//			scanf("%c",&v1);
//			getchar();
//			scanf("%c",&v2);
//			getchar();
//			scanf("%d",&weight);
//			getchar();
			gets(Imfor);
			fprintf(f,"%s\n",Imfor);
			//printf("\nv1:%c  v2:%c  weight:%d\n",v1,v2,weight);
//			i=Locatevex(G,v1);
//			j=Locatevex(G,v2);
//			if(i!=-1 && j!=-1){
//				G->arc[i][j]=weight;
//				G->arc[j][i]=weight;
//			}else{
//				k--; 
//				printf("输入了不存在的顶点!\n");
//			}
		}
	}
}
void print(Gragh * G){
	int i,j;
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			printf("%d ",G->arc[i][j]);
		}
		printf("\n");
	} 
}
int main()
{
	int i,j;
	Gragh G;
	//CreateUDN(&G);
	ReadGragh(&G); 
	print(&G);
	BFSTraverse(&G,'A');
	ClearVisted(&G);
	printf("\n");
	DFSTraverse(&G,'A');
	ClearVisted(&G);
	printf("\n");
	Floyd(&G,'C','F');
	return 0;   
}

