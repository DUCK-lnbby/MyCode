#include<stdio.h>
#define MAXVALUE 1000
typedef struct HuffmanTree
{			
	int weight;					//��Ž���Ȩֵ 
	int parent,lchild,rchild;	//���˫�ס����ӡ��Һ��ӽ����±� 
}HuffmanTree;
void HFCreat(HuffmanTree ht[],int n)
{
	int i,j,min1,min2,k1,k2;//min1��min2�ֱ�����С�ʹ�СȨ��k1��k2��Ŷ�ӦС�� 
	for(i=0;i<2*n-1;i++)
	{
		ht[i].parent=ht[i].lchild=ht[i].rchild=-1;
		ht[i].weight=0;
	}
	printf("input the weight of all leaves:\n");
	for(i=0;i<n-1;i++)
	{
		scanf("%d",&ht[i].weight);
	}
	for(i=0;i<n-1;i++)
	{
		min1=min2=MAXVALUE;
		k1=k2=0;
		for(j=0;j<n+i;j++)
		{
			if(ht[i].parent==-1 && ht[i].weight<min1)
			{
				min2=min1;
				k2=k1;
				k1=j;
				min1=ht[i].weight;
			}else
			{
				if(ht[i].parent==-1 && ht[j].weight<min2)
				{
					k2=j;
					min2=ht[i].weight;
				}
			}
		} 
		ht[k1].parent=ht[k2].parent=n+i;
		ht[n+i].lchild=k1;
		ht[n+i].rchild=k2;
		ht[n+i].parent=-1;
		ht[n+i].weight=ht[k1].weight+ht[k2].weight;
		printf("%d",ht[i].weight);
	}
}
int main()
{
	int n,i;
	HuffmanTree ht[100];
	HFCreat(ht,5);
	return 0;
}

