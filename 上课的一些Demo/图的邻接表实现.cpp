#include<iostream>
using namespace std;
typedef int Vertex;
typedef int WeightType;
typedef int DataType;
#define MaxVertexNum 100





 //定义邻接点
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {    //邻接表内元素
	Vertex AdjV;//邻接点下标
	WeightType Weight;//有权图的变量权重
	PtrToAdjVNode Next;//指向下一个结点的指针
};
//定义邻接表头
typedef struct Vnode {    //邻接表头
	PtrToAdjVNode FirstEdge;   //总是指向链表里第一个边 
	DataType Data;//防止顶点还需要存一些数据

} AdjList[MaxVertexNum]; //结构体类型命名为AdjList  这里是邻接表类型  是一个数组 每个元素都是一个结点Vnode 结点里包含指针FirstEdge




//定义边
typedef struct ENode* ptrToENode;
struct ENode {  // 边 
	Vertex V1, V2;    // 有向边<V1,V2> 
	WeightType Weight;  // 权重 
};
typedef ptrToENode Edge;

//定义结构体结点
typedef struct GNode* PtrToGNode;
struct GNode {   //定义结构体结点
	int Nv;
	int Ne;
	AdjList G;  //邻接表
};
typedef PtrToGNode LGraph;//以邻接表方式存储的图类型    LGraph:邻接表

LGraph CreateGraph(int VertexNum)   //初始化一个有顶点没边的图
{
	Vertex V, W;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	for(V=0;V<Graph->Nv;V++)
		Graph->G[V].FirstEdge = NULL;//满足没有边
	return Graph;
}
void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode;

	//插入边<V1,V2>
	//为V2建立新的邻接点  NewNode相当于V2
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;  
	NewNode->Weight = E->Weight;
	//将V2插入V1的表头

	NewNode->Next = Graph->G[E->V1].FirstEdge;   //这一步把V2指向原本V1指向的那个（比如V2）
	Graph->G[E->V1].FirstEdge = NewNode;   //这一步让V1从指向V3变成指向V2，完成V2的插入

	//如果是无向图，还需要插入<V2,V1>
	//为V1建立新的邻接点  NewNode相当于V1
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;
	//将V1插入V2的表头
	NewNode->Next = Graph->G[E->V2].FirstEdge;   //这一步把V2指向原本V1指向的那个（比如V2）
	Graph->G[E->V2].FirstEdge = NewNode;   //这一步让V1从指向V3变成指向V2，完成V2的插入

}
  //建立图
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
//输出表
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