/*
11-ɢ��2 Hashing
��TSize���������������û�����������С��������������뽫���С���¶���Ϊ�����û�������С����С��������
����̽�⣨��������������

*/
//hs-1-2.c
#include<iostream>
using namespace std;
#include<stdio.h>
#include<math.h>
#include<string.h>
#define MAX 100005
int H[MAX];

int Hash(int x, int m) {
	int k = 1;
	int pos;
	pos = x % m;
	if (H[pos] == -1) {
		H[pos] = 1;
		return pos;   //���
	}
	else {
		while (H[pos] != -1) {    //��Ӧλ���Ѿ������� ��ͻ
			if (H[(pos + k * k) % m] == -1) {
				H[(pos + k * k) % m] = 1;
				return (pos + k * k) % m;
			}
			k++;
			if (k >= m) return -1;
		}
	}

}

int NextPrime(int N)  //�ж�m�ǲ���������Ҫѡ�����m�ĵ�һ������
{
	int i, p = (N % 2) ? N + 2 : N + 1;
	if (N == 1) return 2;
	while (p <= MAX) {
		for (i = (int)sqrt(p); i > 2; i--)
			if (!(p % i)) break;
		if (i == 2) break;
		else p += 2;
	}
	return p;
}
int main()
{
	int m, n, x;
	int i;
	int flag = 1, t;
	cin >> m >> n;
	m = NextPrime(m);
	for (i = 0; i < m; i++) H[i] = -1;  //��ʼ�� 
	for (i = 0; i < n; i++) {
		cin >> x;
		if (flag) flag = 0;
		else cout << " ";
		t = Hash(x, m);
		if (t != -1) cout << t;
		else cout<<"-";
	}
	return 0;
}
