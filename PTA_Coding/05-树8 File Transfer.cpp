#include<iostream>
using namespace std;
#define MaxSize 10001                  /* �������Ԫ�ظ��� */
typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MaxSize];
SetName Find(SetType S, ElementType X)
{
	if (S[X] < 0)  //�ҵ����ϵĸ�
		return X;
	else                  //�ݹ鷨 ���ҵ��� �ٰѸ����X�ĸ��ڵ� �ٷ��ظ� ����һ�ֺ��������������������ĸ��ڵ�
		return S[X] = Find(S, S[X]);

}
//�ϲ� ���ȹ鲢
void Union(SetType S, SetName Root1, SetName Root2) //С�����������������ȥ
{           //S[Root]=-x��x=����
	if (S[Root2] < S[Root1]) {       //��2����1����
		S[Root1] = Root2;
	}
	else {
		if (S[Root2] = S[Root1]) S[Root1]--;  //һ���ߵ�ʱ��Ͱ�1����2��  1����һ�� Root1-=1
		S[Root2] = Root1;
	}
}
void Initialization(SetType S, int n) {
	for (int i = 0; i < n; i++)
		S[i] = -1;
}
// ��
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
// ��
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

//����Ƿ����
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