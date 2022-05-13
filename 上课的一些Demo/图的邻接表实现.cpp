#include<iostream>
using namespace std;
typedef int Vertex;
typedef int WeightType;
typedef int DataType;
#define MaxVertexNum 100





 //�����ڽӵ�
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {    //�ڽӱ���Ԫ��
	Vertex AdjV;//�ڽӵ��±�
	WeightType Weight;//��Ȩͼ�ı���Ȩ��
	PtrToAdjVNode Next;//ָ����һ������ָ��
};
//�����ڽӱ�ͷ
typedef struct Vnode {    //�ڽӱ�ͷ
	PtrToAdjVNode FirstEdge;   //����ָ���������һ���� 
	DataType Data;//��ֹ���㻹��Ҫ��һЩ����

} AdjList[MaxVertexNum]; //�ṹ����������ΪAdjList  �������ڽӱ�����  ��һ������ ÿ��Ԫ�ض���һ�����Vnode ��������ָ��FirstEdge




//�����
typedef struct ENode* ptrToENode;
struct ENode {  // �� 
	Vertex V1, V2;    // �����<V1,V2> 
	WeightType Weight;  // Ȩ�� 
};
typedef ptrToENode Edge;

//����ṹ����
typedef struct GNode* PtrToGNode;
struct GNode {   //����ṹ����
	int Nv;
	int Ne;
	AdjList G;  //�ڽӱ�
};
typedef PtrToGNode LGraph;//���ڽӱ�ʽ�洢��ͼ����    LGraph:�ڽӱ�

LGraph CreateGraph(int VertexNum)   //��ʼ��һ���ж���û�ߵ�ͼ
{
	Vertex V, W;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	for(V=0;V<Graph->Nv;V++)
		Graph->G[V].FirstEdge = NULL;//����û�б�
	return Graph;
}
void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode;

	//�����<V1,V2>
	//ΪV2�����µ��ڽӵ�  NewNode�൱��V2
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;  
	NewNode->Weight = E->Weight;
	//��V2����V1�ı�ͷ

	NewNode->Next = Graph->G[E->V1].FirstEdge;   //��һ����V2ָ��ԭ��V1ָ����Ǹ�������V2��
	Graph->G[E->V1].FirstEdge = NewNode;   //��һ����V1��ָ��V3���ָ��V2�����V2�Ĳ���

	//���������ͼ������Ҫ����<V2,V1>
	//ΪV1�����µ��ڽӵ�  NewNode�൱��V1
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;
	//��V1����V2�ı�ͷ
	NewNode->Next = Graph->G[E->V2].FirstEdge;   //��һ����V2ָ��ԭ��V1ָ����Ǹ�������V2��
	Graph->G[E->V2].FirstEdge = NewNode;   //��һ����V1��ָ��V3���ָ��V2�����V2�Ĳ���

}
  //����ͼ
LGraph BuildGraph() {
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
	scanf("%d", &Nv);
	Graph = CreateGraph(Nv);
	scanf("%d", &(Graph->Ne));
	if (Graph->Ne != 0) {
		for (i = 0; i < Graph->Ne; i++) {
			E = (Edge)malloc(sizeof(struct ENode));
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			InsertEdge(Graph, E);
		}
	}
	return Graph;
}
//�����
void PrintGraph(LGraph Graph) {
	Vertex v;
	PtrToAdjVNode tmp;
	for (v = 0; v < Graph->Nv; v++) {
		tmp = Graph->G[v].FirstEdge;
		printf("%d ", v);
		while (tmp) {
			printf("%d ", tmp->AdjV);
			tmp = tmp->Next;
		}
		printf("\n");
	}
}


int main() {
	LGraph Graph;
	Graph = BuildGraph();
	PrintGraph(Graph);
	return 0;
}