#include<iostream>
using namespace std;
#define MaxSize 100005
void bucket_sort(int A[], int N) {   //桶排序处理
	int count[55]={0};   //初始化数组count
	for (int i = 0; i < N; i++)
		count[A[i]]++;   //每个A[i]数出现一次 对应的count链表就+1
	for (int i = 0; i < 55; i++)
		if (count[i])
			cout << i << ":" << count[i] << endl;
}

int main() {
	int N;
	cin >> N;
	int A[MaxSize];
	for (int i = 0; i < N; i++)
		cin >> A[i];
	bucket_sort(A, N);
	system("pause");
	return 0;
}