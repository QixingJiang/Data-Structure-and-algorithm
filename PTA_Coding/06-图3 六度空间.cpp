#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#define MaxVertex 10005
typedef int vertex;
typedef struct Node* AdjList;
struct Node {
	vertex Adjv;  // 当前下标 
	AdjList Next;  // 下一个 
};
AdjList G[MaxVertex];
bool visit[MaxVertex];  // 是否访问 
int N;  // 结点数
int M;  // 边数 
using namespace std;

// 初始化访问状态 
void InitVisit() {
	for (int i = 1; i <= N; i++)
		visit[i] = false;
}

// 初始化 
void Init() {
	vertex v1, v2;
	AdjList NewNode;
	cin >> N >> M;
	// 初始化点，从 1到N   创建N个点
	for (int i = 1; i <= N; i++) {
		G[i] = (AdjList)malloc(sizeof(struct Node));
		G[i]->Adjv = i;
		G[i]->Next = NULL;
	}
	// 初始化边 
	for (int i = 0; i < M; i++) {   //总体就是为了实现把v2赋予v1->Next
		cin >> v1 >> v2;   //v1是当前结点  v2是v1指向的下一个结点
		NewNode = (AdjList)malloc(sizeof(struct Node));
		NewNode->Adjv = v2;          
		NewNode->Next = G[v1]->Next; //指向下一个 这个时候NewNode的Next=NULL
		G[v1]->Next = NewNode;       //把NewNode的Next和Adjv全都赋予G[v1]->Next 而NewNode又是v2 相当于把v2赋给v1->Next

		NewNode = (AdjList)malloc(sizeof(struct Node));
		NewNode->Adjv = v1;
		NewNode->Next = G[v2]->Next;
		G[v2]->Next = NewNode;  //v1赋给v2的->next 因为是无向图 双向连接。
	}
}

int BFS(vertex v) {   //v=i
	queue<vertex> q;
	vertex tmp;
	int level = 0;
	int last = v;  // 该层最后一次访问的结点 
	int tail = v;  // 每次在变的结点 
	AdjList node;
	visit[v] = true;
	int count = 1;  // 统计关系数 
	q.push(v); //push是插入q队列 queue是先进先出
	while (!q.empty()) {  //当q不空
		tmp = q.front(); //queue的第一个元素   tmp=i
		q.pop(); //出队列
		// G[i]第一个结点存自己的下标    G[tmp]=G[i]
		node = G[tmp]->Next;
		while (node) {
			if (!visit[node->Adjv]) {  //node->Adjv没访问过
				visit[node->Adjv] = true;
				q.push(node->Adjv);
				count++;
				tail = node->Adjv; // 每次更新该结点 
			}
			node = node->Next;
		}
		// 如果该当前结点是这层最后一个结点 
		if (tmp == last) {
			level++;    // 层数 +1  
			last = tail;   // 更改 last 
		}
		// 层数够了结束 
		if (level == 6)
			break;
	}
	return count;
}


void output(double result, int i) {
	printf("%d: %.2f%%\n", i, result);
}

void SDS() {  //SDS:六度分割缩写
	int count;
	for (int i = 1; i <= N; i++) {
		// 每次初始化访问数组 
		InitVisit();
		count = BFS(i);
		output((100.0 * count) / N, i);
	}
}


int main() {
	Init();
	SDS();
	system("pause");
	return 0;
}