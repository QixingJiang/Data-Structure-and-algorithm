#include<iostream>
using namespace std;


#define INF 65535 //����INFINITY  Ϊ˫�ֽ��޷������������ֵ
#define MaxVertexNum 100
typedef int Vertex;
typedef int WeightType;
typedef struct ENode* PtrToENode;  //����ָ��߽���ָ��
//�ߵĶ���
typedef struct ENode* PtrToENode;  //����ָ��߽���ָ��
struct ENode {  //����߽��
	Vertex V1, V2;  //һ���������������  ����V1->V2
	WeightType Weight;//��Ȩͼ��Ȩ��
};
typedef PtrToENode Edge;// �ѱ߶���Ϊָ��߽���ָ��
//���Ķ���
typedef struct GNode* PtrToGNode;   //Ptr:ָ��
struct GNode {
	int Nv;  //������
	int Ne;   //����
	WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;//���ڽӾ���洢��ͼ����  M��Matrix

//�������ͼ
//����ÿ��Դ�㵽����������ֵ
WeightType FindMaxDist(WeightType D[][MaxVertexNum], Vertex i, int N)
{
	WeightType MaxDist;
	Vertex j;
	MaxDist = 0;
	for (j = 0; j < N; j++)    //�ҵ�i����������j�������
	{
		if (j != i && D[i][j] > MaxDist)  //���ж϶Խ���Ԫ�� ��Ϊ���������
			MaxDist = D[i][j];
	}
	return MaxDist;
}
MGraph CreateGraph(int VertexNum)   //Vertex:����
{
	Vertex V, W;
	MGraph Graph;
	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	//����Ĭ�϶����Ŵ�0��ʼ ��Nv-1 ��Ϊ�����±�ԭ��
	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
			Graph->G[V][W] = INF;
	return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
	Graph->G[E->V1][E->V2] = E->Weight;  //�����<V1,V2>
	Graph->G[E->V2][E->V1] = E->Weight;  //����ͼ(V1,V2)ҲҪ����<V2,V1>
}

MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	int i, Nv;
	cin >> Nv;  //���붥�����
	Graph = CreateGraph(Nv);    //���붥������ʱ����Ƚ���һ���ж����ޱߵ�ͼ
	cin >> Graph->Ne;  //ֱ����Gaph->Ne���Ne ���������½���Ne����
	if (Graph->Ne != 0)
	{
		E = (Edge)malloc(sizeof(struct ENode));
		for (i = 0; i < Graph->Ne; i++)
		{
			cin >> E->V1;  //����Ķ��������� ���������ͼ��ʱ��Ҫ-1
			cin >> E->V2;
			cin >> E->Weight;
			E->V1--;
			E->V2--;   //��Ϊ��ʼ����Ǵ�0��ʼ��
			InsertEdge(Graph, E);//�����E����ϢȻ�����Graph
		}
	}
	return Graph;

}

//	Floyd�㷨ʵ��
void Floyd(MGraph Graph, WeightType D[][MaxVertexNum])
{
	Vertex i, j, k;

	for (i = 0; i < Graph->Nv; i++)
		for (j = 0; j < Graph->Nv; j++)
			D[i][j] = Graph->G[i][j];


	for (k = 0; k < Graph->Nv; k++)
		for (i = 0; i < Graph->Nv; i++)
			for (j = 0; j < Graph->Nv; j++)
				if (D[i][k] + D[k][j] < D[i][j])
				{
					D[i][j] = D[i][k] + D[k][j];
					//if (i == j && D[i][j] < 0)   //�����ָ�ֵȦ  ����˵��i��������һȦ�ص�i������Dist<0
					//	return false;
					//path[i][j] = k;
				}
	//return true;
}

//���Ҷ��(ÿ��Դ�㵽����������ֵ)�е���Сֵ
void FindAnimal(MGraph Graph)
{ 
	WeightType MinDist,MaxDist;
	Vertex i, Animal;
	WeightType D[MaxVertexNum][MaxVertexNum];
	Floyd(Graph,D);   //����Floyd�㷨1
	MinDist = INF;
	for (i = 0; i < Graph->Nv; i++)
	{
		MaxDist = FindMaxDist(D, i, Graph->Nv);   //�ҵ���ǰ�����������
		if (MaxDist == INF) {
			cout << "0" << endl;
			return;
		}
		if (MinDist > MaxDist)  //��ǰ������������MaxDist��С��ʱ�򣬸���MaxDist
		{
			MinDist = MaxDist;
			Animal = i + 1;  //��¼������ i+1����Ϊ���붯���Ǵ�1��ʼ��ţ�����i��0��ʼ���� 
		}
	}
	cout << Animal <<" "<< MinDist;
}

int main()  
{   //����ģ�飺1������ͼ 2��FindAnimal
	MGraph G = BuildGraph();      //�����Ӿ����ʾͼ���ʺϵ�
	FindAnimal(G);
	system("pause");
	return 0;


}