#include<iostream>
#include<queue>
#include<algorithm>
#define MaxVertex 101
#define INF -65535
typedef int Vertex;
using namespace std;
int N; // 点
int M;  // 边
int G[MaxVertex][MaxVertex];
int Earliest[MaxVertex];  // 时间 
int Indegree[MaxVertex]; // 入度 

// 初始化图 
void build() {
	Vertex v1, v2, w;
	cin >> N >> M;
	for (Vertex i = 0; i < N; i++) {   //n*n的矩阵
		for (Vertex j = 0; j < N; j++)
			G[i][j] = INF;
	}
	for (int i = 0; i < M; i++) {
		cin >> v1 >> v2 >> w;
		G[v1][v2] = w;  // 更新G[i][j]=weight    有向图    v1->v2
		Indegree[v2]++;  // v2入度+1  
	}
}

void TopSort() {
	int cnt = 0;
	queue<Vertex> q;
	// 入度为0顶点入队   说明前面的已经入完了 轮到他们了
	for (Vertex i = 0; i < N; i++)
		if (!Indegree[i]) {
			q.push(i);  //放入容器q
			Earliest[i] = 0; //时间重置为0
		}  
	while (!q.empty()) {	   //当q不为空  开始检查容器 
		Vertex v = q.front(); //取出一个顶点 入度一定为0
		q.pop();
		cnt++;  //输出cnt个顶点
		for (Vertex w = 0; w < N; w++)
			if (G[v][w] != INF) {
				if (Earliest[w] < Earliest[v] + G[v][w])  //如果周围有时间更长，更新时间 
					Earliest[w] = max(Earliest[w], Earliest[v] + G[v][w]);
				if (--Indegree[w] == 0)  //聪明的算法 ：w的入度-1是为了抹去这个v的作用。同时随时把入度为0的顶点放在一个容器里 这样下一个不用扫描  直接 从q中取一个fornt就行 时间复杂度降低
					q.push(w);
			}
	}
	if (cnt != N)  //图里还留了顶点 说明有回路  
		cout << "Impossible";
	else {
		// 也许不止一个终点 
		int max = 0;
		for (Vertex i = 0; i < N; i++)
			if (max < Earliest[i])
				max = Earliest[i];
		cout << max;
	}

}

int main() {
	build();
	TopSort();
	return 0;
}
