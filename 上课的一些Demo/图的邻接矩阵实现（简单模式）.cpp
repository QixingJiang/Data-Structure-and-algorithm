//��ģʽ �������ˢ���� �ɶ��Ե� ��
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define MAXN 100
int G[MAXN][MAXN], Nv, Ne; //ֱ�Ӷ���ȫ�ֱ���

void BuildGraph() {
	int i, j, v1, v2, w;

	cin >> Nv;
	// ��ʼ��ͼ 
	for (i = 0; i < Nv; i++)
		for (j = 0; j < Nv; j++)
			G[i][j] = 0;
	cin >> Ne;
	// ����� 
	for (i = 0; i < Ne; i++) {
		cin >> v1;
		cin >> v2;
		cin >> w;
		G[v1][v2] = w;
		G[v2][v1] = w;
	}
}


// ����ͼ
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