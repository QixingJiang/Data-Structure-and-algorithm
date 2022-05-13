//复杂模式下
#include<iostream>
using namespace std;
#define MaxVertexNum 100
typedef int Vertex;
typedef int WeightType;
typedef int DataType;
//边的定义
typedef struct ENode* PtrToENode;  //定义指向边界点的指针
struct ENode {  //定义边结点
	Vertex V1, V2;  //一条边首先有俩结点  有向V1->V2
	WeightType Weight;//有权图的权重
};
typedef PtrToENode Edge;// 把边定义为指向边界点的指针
//结点的定义
typedef struct GNode* PtrToGNode;   //Ptr:指针
struct GNode {
	int Nv;  //顶点数
	int Ne;   //边数
	WeightType G[MaxVertexNum][MaxVertexNum];
	DataType Data[MaxVertexNum]; //存顶点的数据

};
typedef PtrToGNode MGraph;//以邻接矩阵存储的图类型  M：Matrix
//初始化一个有VertexNum个顶点但是无边的图
MGraph CreateGraph(int VertexNum)   //Vertex:顶点
{
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	//这里默认顶点编号从0开始 到Nv-1 因为数组下标原因
	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;
	return Graph;
}
//插入边
void InsertEdge(MGraph Graph, Edge E)
{
	Graph->G[E->V1][E->V2] = E->Weight;  //插入边<V1,V2>
	Graph->G[E->V2][E->V1] = E->Weight;  //无向图(V1,V2)也要插入<V2,V1>
}
MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	int i, Nv;
	cin >> Nv;  //读入顶点个数
	Graph = CreateGraph(Nv);    //输入顶点数的时候就先建立一个有顶点无边的图
	cin >> Graph->Ne;  //直接用Gaph->Ne里的Ne 不用再重新建立Ne变量
	if (Graph->Ne != 0)
	{	
		E = (Edge)malloc(sizeof(struct ENode));
		for (i = 0; i < Graph->Ne; i++)
		{
			cin >> E->V1;  //输入的动物编号正常 到下面存入图的时候要-1
			cin >> E->V2;
			cin >> E->Weight;
			E->V1--;
			E->V2--;   //因为起始编号是从0开始的
			InsertEdge(Graph, E);//读入边E的信息然后插入Graph
		}
	}
	return Graph;

} 
//遍历输出图



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