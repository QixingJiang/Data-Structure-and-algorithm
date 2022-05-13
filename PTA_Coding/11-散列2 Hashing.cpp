/*
11-散列2 Hashing
“TSize最好是素数。如果用户给定的最大大小不是素数，则必须将表大小重新定义为大于用户给定大小的最小素数。”
二次探测（仅具有正增量）

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
		return pos;   //添加
	}
	else {
		while (H[pos] != -1) {    //对应位置已经有数了 冲突
			if (H[(pos + k * k) % m] == -1) {
				H[(pos + k * k) % m] = 1;
				return (pos + k * k) % m;
			}
			k++;
			if (k >= m) return -1;
		}
	}

}

int NextPrime(int N)  //判断m是不是素数，要选择大于m的第一个素数
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
	for (i = 0; i < m; i++) H[i] = -1;  //初始化 
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
