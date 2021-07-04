#include<stdio.h>
#include<stdlib.h>
#define MAX 100			//��󶥵��� 
#define MaxInt 32767	//���Ȩֵ 
int D1[MAX],P1[MAX],D[MAX][MAX];
typedef char VerTexType;//�������� 
typedef int ArcType;	//Ȩֵ���� 
VerTexType P[MAX][MAX];
typedef struct {
	VerTexType vexs[MAX];	//������Ϣ 
	ArcType arc[MAX][MAX];	//�ڽӾ��� 
	int visited[MAX]; 
	int vexnum,arcnum;		//������������� 
}Gragh;
typedef enum {FALSE,TRUE} boolean;			//enum��һ���µĹؼ��֣�ר����������ö�����ͣ���Ҳ������C�����е�Ψһ��;
typedef struct StackList{
	VerTexType data;
	struct StackList * next;
}StackList;
int Locatevex(Gragh * G,VerTexType x);		//��ȡ��ͼ�Ķ���λ�� 
void CreateUDN(Gragh * G);					//����ͼ 
void DestroyGragh(Gragh * G);				//����ͼ 
VerTexType GetVex(Gragh * G,VerTexType x);	//����ͼ�ж������Ϣ 
void PutVex(Gragh * G,VerTexType v,VerTexType value);	//�Զ������½��и�ֵ 
VerTexType FirstAdjVex(Gragh * G,VerTexType x);			//���ص�һ���ڽӶ��� 
VerTexType NextAdjVex(Gragh * G,VerTexType x,VerTexType y);	//���������������¸��ڽӵ�
void InsertVex(Gragh * G,VerTexType x);			//����һ������ 
void DeleteArc(Gragh * G,VerTexType x);			//ɾ��G�ж���x������صĻ�
void InsertArc(Gragh * G,VerTexType x,VerTexType y);	//��Ӷ���֮��ı�(�޸�) 
void DeletVex(Gragh * G,VerTexType x,VerTexType y);		//ɾ����
void DFSTraverse(Gragh * G,VerTexType start);					//��ȱ���
int CountVex(Gragh * G,VerTexType x);			//���㶥��Ķ� 
void BFSTraverse(Gragh * G,VerTexType start);					//��ȱ��� 
void ClearVisted(Gragh * G);							//������ʹ��ı�� 
StackList * GetImfor(Gragh * G,VerTexType start);		//���������ȱ������
void Dijkstra(Gragh * G,VerTexType start);	//�Ͻ�˹�����㷨�����·�� 
void Floyd(Gragh * G,VerTexType start,VerTexType end);		//����������������֮������·�� 
void ReadGragh(Gragh * G){
	FILE * f;
	VerTexType v1,v2;
	int weight,i,k,j;
	if((f=fopen("test.txt","r"))==NULL){
		printf("���ļ�ʧ��\n");
	}else{
		for(i=0;i<MAX;i++){
			G->visited[i]=0;
			for(j=0;j<MAX;j++){
				G->arc[i][j]=MaxInt;					//��ʼ���ڽӾ��� 
			}
		} 
		fscanf(f,"%d %d\n",&G->vexnum,&G->arcnum);	//���붥������ͱ���
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
				printf("�����˲����ڵĶ���!\n");
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
	if(k==-1) printf("���� %c �� %c ��·����\n",start,end);
	else{
		printf("�Ӷ��� %c �� %c �����·���ǣ�%c",start,end,start);
		while(k!=Locatevex(G,end)){                     
			printf("->%c",G->vexs[k]);
			k=P[k][Locatevex(G,end)];                          
		}        
		printf("->%c\n",G->vexs[Locatevex(G,end)]);
		printf("·�����ȣ�%d\n",D[Locatevex(G,start)][Locatevex(G,end)]);
	}
}                                          
void Dijkstra(Gragh * G,VerTexType start){ 
	//Dijkstra�㷨������ͼG��v1���㵽��������v�����·��P[v]����ȨD[v]
	//��G������ͼ���ڽӾ�����<i,j>�����ڣ���M[i][j]=ManInt
	//S[v]Ϊ�浱�ҽ���v��S,���Ѿ����v1��v�����·��      
	int D2[MAX],P2[MAX];
	int v,i,w,min;
	int v1;
	v1=Locatevex(G,start);
	boolean S[MAX];
	for(v=0;v<G->vexnum;v++)			//��ʼ��S��D 
	{
		S[v]=FALSE;				//�ÿ����·���յ㼯 
		D2[v]=G->arc[v1][v];	//��ʼ�����·��ֵ 
		if(D2[v]<MaxInt){
			P2[v]=v1;			//v1��v��ǰ����˫�ף� 
		}else{
			P2[v]=0;			//vû��ǰ�� 
		}
	}
	D2[v1]=0;S[v1]=TRUE;		//S����ʼ��ʱֻ��Դ�㣬Դ�㵽Դ��ľ���Ϊ0
	//��ʼѭ����ÿ�����v1��ĳ����������·��������v�ӵ�S���� 
	for(i=1;i<G->vexnum;i++)			//����n-1������ 
	{
		min=MaxInt;
		for(w=0;w<G->vexnum;w++)
			if(!S[w] && D2[w]<min){	//w������v1������� 
				v=w;
				min=D2[w];
			}
			S[v]=TRUE;
			for(w=0;w<G->vexnum;w++)		//���µ�ǰ���·���Լ����� 
				if(!S[w] && (D2[v]+G->arc[v][w]<D2[w])){
					D2[w]=D2[v]+G->arc[v][w];	//�޸�D2[w]��P2[w] 
					P2[w]=v;
				}
	}                    
	printf("·������    ·��\n");
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
	x=Locatevex(G,start);							//��ǰ�����λ�� 
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
		printf("�����˲����ڵĶ���!\n");
	}
}
void InsertArc(Gragh * G,VerTexType x,VerTexType y){
	int i,j,weight;
	printf("��������֮���·�����ȣ�\n");
	scanf("%d",&weight);
	getchar();
	i=Locatevex(G,x);
	j=Locatevex(G,y);
	if(i!=-1 && j!=-1){
		G->arc[i][j]=weight;
		G->arc[j][i]=weight;
	}else{
		printf("�����˲����ڵĶ���!\n");
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
	for(j=k;j<G->vexnum;j++){				//��ɾ���Ķ�����Ϣ�ɺ���ǰ���и��ǣ�����ֶԽ������д����ų����������� 
		for(i=0;i<G->vexnum;i++){
			G->arc[i][j]=G->arc[i][j+1];
			G->arc[j][i]=G->arc[j+1][i];
		}
	}
	for(i=0;i<G->vexnum;i++){
		G->arc[i][G->vexnum-1]=MaxInt;
		G->arc[G->vexnum-1][i]=MaxInt;
	}
	G->vexnum--;							//��ȥ������ 
	G->arcnum-=m;							//��ȥ���� 
	for(i=0;i<G->vexnum;i++){					//��ʼ���Խ��� 
		G->arc[i][i]=MaxInt;
	}
} 
void InsertVex(Gragh * G,VerTexType x) {
	int i,j,k;
	int vexnum,arcnum,weight;
	VerTexType v1,v2;					//��������
	G->vexs[(G->vexnum++)]=x;
	printf("���������ı�����\n");
	scanf("%d",&arcnum);
	getchar();
	G->arcnum+=arcnum;
	for(k=0;k<arcnum;k++){
		printf("���붥��1������2�Լ�����֮���·�����ȣ�(����%d��)\n",arcnum-k);
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
			printf("�����˲����ڵĶ���!\n");
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
		printf("��ͼ��û�и�·��\n");
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
	VerTexType v1,v2;					//�������� 
	ArcType weight;						//·������ 
	for(i=0;i<MAX;i++){
		G->visited[i]=0;
		for(j=0;j<MAX;j++){
			G->arc[i][j]=MaxInt;					//��ʼ���ڽӾ��� 
		}
	} 
	if((f=fopen("ARC.txt","w"))==NULL)		
	{
		printf("�ļ����ܴ�!\n");
		exit(0);
	}else{
		printf("���붥������ͱ���:\n");
		scanf("%d%d",&G->vexnum,&G->arcnum);	//���붥������ͱ���
		fprintf(f,"%d %d\n",G->vexnum,G->arcnum);
		printf("����������㣺\n");
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
			printf("���붥��1������2�Լ�����֮���·�����ȣ�\n");
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
//				printf("�����˲����ڵĶ���!\n");
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

