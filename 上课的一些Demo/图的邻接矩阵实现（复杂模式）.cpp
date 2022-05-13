//����ģʽ��
#include<iostream>
using namespace std;
#define MaxVertexNum 100
typedef int Vertex;
typedef int WeightType;
typedef int DataType;
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
	DataType Data[MaxVertexNum]; //�涥�������

};
typedef PtrToGNode MGraph;//���ڽӾ���洢��ͼ����  M��Matrix
//��ʼ��һ����VertexNum�����㵫���ޱߵ�ͼ
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
			Graph->G[V][W] = INFINITY;
	return Graph;
}
//�����
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
//�������ͼ



void print(MGraph Graph) {
	int i, j;
	for (i = 0; i < Graph->Nv; i++) {
		for (j = 0; j < Graph->Nv; j++)
			cout << Graph->G[i][j]<< " ";
			cout << endl;
	}
}
int main() {
	MGraph Graph1=BuildGraph();
	print(Graph1);
	system("pause");
	return 0;

}