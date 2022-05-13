#include<iostream>
#include<queue>
#include<algorithm>
#define MaxVertex 101
#define INF -65535
typedef int Vertex;
using namespace std;
int N; // ��
int M;  // ��
int G[MaxVertex][MaxVertex];
int Earliest[MaxVertex];  // ʱ�� 
int Indegree[MaxVertex]; // ��� 

// ��ʼ��ͼ 
void build() {
	Vertex v1, v2, w;
	cin >> N >> M;
	for (Vertex i = 0; i < N; i++) {   //n*n�ľ���
		for (Vertex j = 0; j < N; j++)
			G[i][j] = INF;
	}
	for (int i = 0; i < M; i++) {
		cin >> v1 >> v2 >> w;
		G[v1][v2] = w;  // ����G[i][j]=weight    ����ͼ    v1->v2
		Indegree[v2]++;  // v2���+1  
	}
}

void TopSort() {
	int cnt = 0;
	queue<Vertex> q;
	// ���Ϊ0�������   ˵��ǰ����Ѿ������� �ֵ�������
	for (Vertex i = 0; i < N; i++)
		if (!Indegree[i]) {
			q.push(i);  //��������q
			Earliest[i] = 0; //ʱ������Ϊ0
		}  
	while (!q.empty()) {	   //��q��Ϊ��  ��ʼ������� 
		Vertex v = q.front(); //ȡ��һ������ ���һ��Ϊ0
		q.pop();
		cnt++;  //���cnt������
		for (Vertex w = 0; w < N; w++)
			if (G[v][w] != INF) {
				if (Earliest[w] < Earliest[v] + G[v][w])  //�����Χ��ʱ�����������ʱ�� 
					Earliest[w] = max(Earliest[w], Earliest[v] + G[v][w]);
				if (--Indegree[w] == 0)  //�������㷨 ��w�����-1��Ϊ��Ĩȥ���v�����á�ͬʱ��ʱ�����Ϊ0�Ķ������һ�������� ������һ������ɨ��  ֱ�� ��q��ȡһ��fornt���� ʱ�临�ӶȽ���
					q.push(w);
			}
	}
	if (cnt != N)  //ͼ�ﻹ���˶��� ˵���л�·  
		cout << "Impossible";
	else {
		// Ҳ��ֹһ���յ� 
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
