//简单模式 打比赛、刷题用 可读性低 简单
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define MAXN 100
int G[MAXN][MAXN], Nv, Ne; //直接定义全局变量

void BuildGraph() {
	int i, j, v1, v2, w;

	cin >> Nv;
	// 初始化图 
	for (i = 0; i < Nv; i++)
		for (j = 0; j < Nv; j++)
			G[i][j] = 0;
	cin >> Ne;
	// 插入边 
	for (i = 0; i < Ne; i++) {
		cin >> v1;
		cin >> v2;
		cin >> w;
		G[v1][v2] = w;
		G[v2][v1] = w;
	}
}


// 遍历图
void print() {
	int i, j;
	for (i = 0; i < Nv; i++) {
		for (j = 0; j < Nv; j++)
			cout << G[i][j];
		cout << endl;
	}
}

int main() {
	BuildGraph();
	print();
	system("pause");
	return 0;
}