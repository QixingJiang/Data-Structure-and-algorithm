#include<iostream>
using namespace std;
#define MaxSize 10001                  /* 集合最大元素个数 */
typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MaxSize];
SetName Find(SetType S, ElementType X)
{
	if (S[X] < 0)  //找到集合的根
		return X;
	else                  //递归法 先找到根 再把根变成X的父节点 再返回根 这样一轮后根结点变成下面所有子树的父节点
		return S[X] = Find(S, S[X]);

}
//合并 按秩归并
void Union(SetType S, SetName Root1, SetName Root2) //小的树贴到大的树上面去
{           //S[Root]=-x；x=树高
	if (S[Root2] < S[Root1]) {       //树2比树1更高
		S[Root1] = Root2;
	}
	else {
		if (S[Root2] = S[Root1]) S[Root1]--;  //一样高的时候就把1挂在2上  1更高一层 Root1-=1
		S[Root2] = Root1;
	}
}
void Initialization(SetType S, int n) {
	for (int i = 0; i < n; i++)
		S[i] = -1;
}
// 并
void Input_connection(SetType S) {
	ElementType u, v;
	cin >> u;
	cin >> v;
	SetName R1, R2;
	R1 = Find(S, u - 1);
	R2 = Find(S, v - 1);
	if (R1 != R2)
		Union(S, R1, R2);
}
// 查
void Check_connection(SetType S) {
	ElementType u, v;
	cin >> u;
	cin >> v;
	SetName R1, R2;
	R1 = Find(S, u - 1);
	R2 = Find(S, v - 1);
	if (R1 == R2)
		printf("yes\n");
	else
		printf("no\n");
}

//检查是否完成
void Check_network(SetType S, int n) {
	int i, count = 0;
	for (i = 0; i < n; i++) {
		if (S[i] < 0)
			count++;
	}
	if (count == 1)
		printf("The network is connected.\n");
	else
		printf("There are %d components.\n", count);
}

int main() {
	SetType S;
	int n;
	char in;
	cin >> n;
	Initialization(S, n);
	do {
		cin >> in;
		switch (in) {
		case'I':Input_connection(S); break;
		case'C':Check_connection(S); break;
		case'S':Check_network(S, n); break;
					}
	} while (in != 'S');
	system("pause");
	return 0;
}