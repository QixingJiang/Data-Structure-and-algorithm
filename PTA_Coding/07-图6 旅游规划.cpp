// 07-ͼ6 ���ι滮
#include<iostream>
using namespace std;
#define MaxVertexNum 501
#define INFINITY 65535
#define ERROR 999
typedef int Vertex; // �ö����±��ʾ����,Ϊ����
typedef int DataType;
typedef int WeightType;

/* ********************* MGraph *******************/
// Graph struct
typedef struct GNode* PtrGNode;
struct GNode
{
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];	// ��distance  (Weight)
    WeightType C[MaxVertexNum][MaxVertexNum];  // ��cost
    // DataType Data[MAX]; // �涥�������
};

typedef PtrGNode MGraph;

// Edge struct ��
typedef struct ENode* PtrENode;
struct ENode
{
    Vertex V1, V2;
    WeightType Weight;
    WeightType Cost;
};
typedef PtrENode Edge;

// ��ʼ����VertexNum�����㵫û�бߵ�ͼ
MGraph CreateGraph(int VertexNum, int EdgeNum)
{
    MGraph Graph;
    Vertex v, w;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = EdgeNum;

    for (v = 0; v < VertexNum; v++) {
        for (w = 0; w < VertexNum; w++) {
            Graph->G[v][w] = INFINITY;
            Graph->C[v][w] = INFINITY;
        }
    }
    return Graph;
}


// ���ݶ�������ݽ�ͼ(�����ߣ�
void InsertEdge(MGraph Graph, Edge E) {
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
    Graph->C[E->V1][E->V2] = E->Cost;
    Graph->C[E->V2][E->V1] = E->Cost;
}

// ��ͼ   ͼ�������ʼ��һ��ֻ�е��ͼ�ͽ���
MGraph BuildGraph(int VertexNum, int EdgeNum) {
    MGraph Graph;
    Edge E;
    int i;

    Graph = CreateGraph(VertexNum, EdgeNum);

    if (Graph->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode)); // �����߽��
        for (i = 0; i < Graph->Ne; i++)
        {
            cin >> E->V1 >> E->V2 >> E->Weight >> E->Cost;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}


/* ********************* Dijkstra *******************/
Vertex FindMinDist(MGraph Graph, int dist[], int collected[]) {
    Vertex MinV, V;
    int MinDist = INFINITY;

    for (V = 0; V < Graph->Nv; V++) {
        if (collected[V] == false && dist[V] < MinDist) {  /* ��Vδ����¼����dist[V]��С */
            MinDist = dist[V];
            MinV = V;  /* ���¶�Ӧ���� */
        }
    }
    if (MinDist < INFINITY) /* �������ҵ���dist[V]�����ҵ���Сdist */
        return MinV; /* ���ض�Ӧ�Ķ����±� */
    else
        return ERROR;  /* �������Ķ��㲻���ڣ����ش����� */
}

//�Խ����ͼGraph��Dijkstra�㷨 
bool Dijkstra(MGraph Graph, int dist[], int cost[], int path[], Vertex S)  //�����SΪԴ��
{
    int collected[MaxVertexNum];   //�������ռ���
    Vertex V, W;

    // ��ʼ��dist[], path[], cost[], collected[],�ڽӾ����в����ڱߵı��ΪINFINITY
    for (V = 0; V < Graph->Nv; V++) {
        dist[V] = Graph->G[S][V];
        cost[V] = Graph->C[S][V];   //C��cost  G:distance(E->Weight)
        if (dist[V] < INFINITY)  // S��V��ֱ��·��
            path[V] = S;
        else
            path[V] = -1;
        collected[V] = false;
    }
    // �Ƚ�������뵽������
    dist[S] = 0;
    cost[S] = 0;
    collected[S] = true;

    while (1)
    {
        V = FindMinDist(Graph, dist, collected); /* V = δ����¼������dist��С�� */
        if (V == ERROR)  /* ��������V�Ѿ������� */
            break;
        collected[V] = true;
        for (W = 0; W < Graph->Nv; W++) { // ��ͼ�е�ÿ������W
            if (collected[W] == false && Graph->G[V][W] < INFINITY)  // V��ÿ��δ�����ʹ����ڽӵ�W
            {
                if (Graph->G[V][W] < 0) /* ���и��� */
                    return false; /* ������ȷ��������ش����� bool Dijkstra =false   */

                /* ����¼Vʹ��dist[W]��С */
                if (dist[V] + Graph->G[V][W] < dist[W]) {
                    dist[W] = dist[V] + Graph->G[V][W]; // ����dist[W]
                    path[W] = V; // ����S��W��·��
                    cost[W] = cost[V] + Graph->C[V][W];  // ����cost[w]
                }
                else if (dist[V] + Graph->G[V][W] == dist[W]
                    && cost[V] + Graph->C[V][W] < cost[W])  // ����һ�����Ƿ��ø���,����·���
                {
                    cost[W] = cost[V] + Graph->C[V][W];
                    path[W] = V;
                }
            }
        } // forѭ������, ÿ��V���ڽӵ�W������
    }// while����
    return true;
}

int main()
{
    int N, M, S, D;
    int dist[MaxVertexNum], cost[MaxVertexNum], path[MaxVertexNum];
    cin >> N >> M >> S >> D;
    MGraph Graph = BuildGraph(N, M);
    if (Dijkstra(Graph, dist, cost, path, S))
        cout << dist[D] << " " << cost[D];
    else
        cout << "Error" << endl;
    system("pause");
    return 0;
}



















