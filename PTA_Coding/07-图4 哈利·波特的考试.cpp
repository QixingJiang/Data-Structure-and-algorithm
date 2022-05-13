#include<iostream>
using namespace std;


#define INF 65535 //定义INFINITY  为双字节无符号整数的最大值
#define MaxVertexNum 100
typedef int Vertex;
typedef int WeightType;
typedef struct ENode* PtrToENode;  //定义指向边界点的指针
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
};
typedef PtrToGNode MGraph;//以邻接矩阵存储的图类型  M：Matrix

//遍历输出图
//查找每个源点到其他点的最大值
WeightType FindMaxDist(WeightType D[][MaxVertexNum], Vertex i, int N)
{
	WeightType MaxDist;
	Vertex j;
	MaxDist = 0;
	for (j = 0; j < N; j++)    //找到i与其他动物j的最长距离
	{
		if (j != i && D[i][j] > MaxDist)  //不判断对角线元素 因为都是无穷大
			MaxDist = D[i][j];
	}
	return MaxDist;
}
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
			Graph->G[V][W] = INF;
	return Graph;
}

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

//	Floyd算法实现
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
					//if (i == j && D[i][j] < 0)   //若发现复值圈  就是说从i出发走了一圈回到i本身但是Dist<0
					//	return false;
					//path[i][j] = k;
				}
	//return true;
}

//查找动物：(每个源点到其他点的最大值)中的最小值
void FindAnimal(MGraph Graph)
{ 
	WeightType MinDist,MaxDist;
	Vertex i, Animal;
	WeightType D[MaxVertexNum][MaxVertexNum];
	Floyd(Graph,D);   //调用Floyd算法1
	MinDist = INF;
	for (i = 0; i < Graph->Nv; i++)
	{
		MaxDist = FindMaxDist(D, i, Graph->Nv);   //找到当前动物的最大距离
		if (MaxDist == INF) {
			cout << "0" << endl;
			return;
		}
		if (MinDist > MaxDist)  //当前动物的最大距离比MaxDist还小的时候，更新MaxDist
		{
			MinDist = MaxDist;
			Animal = i + 1;  //记录动物编号 i+1是因为输入动物是从1开始编号，但是i从0开始计数 
		}
	}
	cout << Animal <<" "<< MinDist;
}

int main()  
{   //两大模块：1、建立图 2、FindAnimal
	MGraph G = BuildGraph();      //用连接矩阵表示图更适合点
	FindAnimal(G);
	system("pause");
	return 0;


}