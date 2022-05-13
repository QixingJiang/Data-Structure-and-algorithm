/*
02-���Խṹ3 Reversing Linked List
*/
#include<stdio.h>
#include<iostream>
#define MaxSize 100000
using namespace std;
int main() {
	int Data[MaxSize];
	int Next[MaxSize];
	int list[MaxSize];
	int FirstAdd, N, K;
	cin >> FirstAdd >> N >> K;
	for (int i = 0; i < N; i++) {
		int tmpAdd, tmpData, tmpNext;
		cin >> tmpAdd >> tmpData >> tmpNext;
		Data[tmpAdd] = tmpData;
		Next[tmpAdd] = tmpNext;
	}
	int sum = 0;   // �ۼ���Ч����� 
	while (FirstAdd != -1) {   // ��β���Ϊ -1 ʱ���� 
		list[sum++] = FirstAdd;   // ��¼����Address
		FirstAdd = Next[FirstAdd];  // ����һ����� 
	}
	for (int i = 0; i < sum - sum % K; i += K) {  // ÿ K �����һ������ 
		for (int j = 0; j < K / 2; j++) {  // ��ת����
			int t = list[i + j];
			list[i + j] = list[i + K - j - 1];
			list[i + K - j - 1] = t;
		}
	}
	for (int i = 0; i < sum - 1; i++)
		printf("%05d %d %05d\n", list[i], Data[list[i]], list[i + 1]);
	printf("%05d %d -1\n", list[sum - 1], Data[list[sum - 1]]);
	return 0;
}