#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
#define MAXSIZE 101
struct ENode {
    int target;
    int weight;
    struct ENode* next;
};
typedef struct ENode* Edge;

typedef struct {
    Edge firstEdge;
} List[MAXSIZE];

struct Graph {
    int vertexCount;
    int edgeCount;
    List header;
};
typedef struct Graph* LGraph;

LGraph graph1, graph2;  //graph1是正向邻接表，graph2是反向邻接表

/************************生成图********************************/
void createGraph() {
    int N, M;
    cin >> N >> M;
    graph1 = (LGraph)malloc(sizeof(struct Graph));
    graph2 = (LGraph)malloc(sizeof(struct Graph));   //graph1是正向邻接表，graph2是反向邻接表

    graph1->vertexCount = N; 
    graph2->vertexCount = N;
    graph1->edgeCount = M; 
    graph2->edgeCount = M;  //记录点和边的数量


    for (int i = 1; i <= N; i++) {
        graph1->header[i].firstEdge = NULL;
        graph2->header[i].firstEdge = NULL;
    }

    for (int i = 0; i < M; i++) {
        int x, y, weight;
        cin >> x >> y >> weight;
        Edge newEdge1 = (Edge)malloc(sizeof(struct ENode));
        newEdge1->target = y;
        newEdge1->weight = weight;
        newEdge1->next = graph1->header[x].firstEdge;
        graph1->header[x].firstEdge = newEdge1;

        Edge newEdge2 = (Edge)malloc(sizeof(struct ENode));
        newEdge2->target = x;
        newEdge2->weight = weight;
        newEdge2->next = graph2->header[y].firstEdge;
        graph2->header[y].firstEdge = newEdge2;
    }
}
/****************************拓扑排序******************************************/
void topSort() {
    int counter = 0;                //判断是否有回路
    int indegree[MAXSIZE] = { 0 };    //入度
    int outdegree[MAXSIZE] = { 0 };   //出度
    int eTime[MAXSIZE] = { 0 };       //最早完成时间
    int lTime[MAXSIZE] = { 0 };       //最晚完成时间
    int queue[MAXSIZE], front = 0, rear = 0;    //队列

    for (int i = 1; i <= graph1->vertexCount; i++)
        for (Edge e = graph1->header[i].firstEdge; e; e = e->next)
            indegree[e->target]++;  //初始化入度

    for (int i = 1; i <= graph1->vertexCount; i++)
        if (indegree[i] == 0)
            queue[rear++] = i;      //初始化队列

    while (front != rear) {
        int vertex = queue[front++];
        counter++;
        for (Edge e = graph1->header[vertex].firstEdge; e; e = e->next) {
            if (eTime[vertex] + e->weight > eTime[e->target])
                eTime[e->target] = eTime[vertex] + e->weight;
            if (--indegree[e->target] == 0) queue[rear++] = e->target;
        }
    }
    //如果没有环路
    if (counter == graph1->vertexCount) {
        int max = 0;
        for (int i = 1; i <= counter; i++)
            if (eTime[i] > max)
                max = eTime[i];

        front = rear = 0;               //重置队列
        for (int i = 1; i <= graph2->vertexCount; i++)
            lTime[i] = max;             //初始化最晚完成时间

        for (int i = 1; i <= graph2->vertexCount; i++)
            for (Edge e = graph2->header[i].firstEdge; e; e = e->next)
                outdegree[e->target]++; //初始化出度

        for (int i = 1; i <= graph2->vertexCount; i++)
            if (outdegree[i] == 0)
                queue[rear++] = i;      //初始化队列

        while (front != rear) {
            int vertex = queue[front++];
            for (Edge e = graph2->header[vertex].firstEdge; e; e = e->next) {
                if (lTime[e->target] > lTime[vertex] - e->weight)
                    lTime[e->target] = lTime[vertex] - e->weight;
                if (--outdegree[e->target] == 0) queue[rear++] = e->target;
            }
        }

        cout << max << endl;    //输出所需要的时间
        for (int i = 1; i <= counter; i++)
            for (Edge e = graph1->header[i].firstEdge; e; e = e->next)
                if (lTime[e->target] - e->weight == eTime[i])
                    cout << i << "->" << e->target<<endl;   //输出所有关键活动
    }
    else {
        cout << "0" << endl;
    }
}

/********************************主函数*************************************************/
int main() {
    createGraph();
    topSort();
    system("pause");
    return 0;
}

