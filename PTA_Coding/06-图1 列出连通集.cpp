#include<iostream>
#include<stdlib.h>
#include<queue>
#define MaxVertex 100
typedef int Vertex;
int G[MaxVertex][MaxVertex];
bool visit[MaxVertex];
int Ne, Nv;
using namespace std;

// 建图
void Build() {
	cin >> Nv;
	for (int i = 0; i < Nv; i++) {
		visit[i] = false;   // 设置为未访问
		for (int j = 0; j < Nv; j++)
			G[i][j] = 0;
	}
	cin >> Ne;
	for (int i = 0; i < Ne; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		G[v1][v2] = 1;
		G[v2][v1] = 1;
	}
}

void DFS(Vertex v) {
	// 标记为已访问
	visit[v] = true;
	cout << " " << v;
	for (int i = 0; i < Nv; i++)
		if (!visit[i] && G[v][i]) //visit[i]=0而且G[v][j]=1
			DFS(i);
}


void BFS(Vertex v) {
	queue<Vertex> q;
	// 改变状态
	visit[v] = true;
	cout << " " << v;
	// 入队
	q.push(v);
	while (!q.empty()) {
		// 队首元素出队
		Vertex tmp = q.front();
		q.pop();
		for (Vertex i = 0; i < Nv; i++) {
			// 如果没有被访问过，而且跟刚出队的元素相邻
			if (!visit[i] && G[i][tmp]) {
				visit[i] = true;
				cout << " " << i;
				q.push(i);
			}
		}
	}
}

// 遍历连通集 
void ListComp() {
	for (Vertex i = 0; i < Nv; i++)   //DFS搜索并输出
		if (!visit[i]) {
			cout << "{";
			DFS(i);
			cout << " }" << endl;
		}
	// 初始化访问状态
	for (Vertex i = 0; i < Nv; i++)
		visit[i] = false;

	for (Vertex i = 0; i < Nv; i++)
		if (!visit[i]) {   //BFS搜索并输出
			cout << "{";
			BFS(i);
			cout << " }" << endl;
		}
}

int main() {
	Build();
	ListComp();
	system("pause");
	return 0;
}