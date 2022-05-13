/*
问题关键是第三行的输入不一定是最终排序结果，可能只是一个过程结果。
因此输出中提到“输出再一次迭代进行排序后的结果”
*/
#include<iostream>
using namespace std;
#define MAXNUM 65535
int Match(int A[], int B[], int N) { //0
	int i;
	for (i = 0; i < N; i++) {
		if (A[i] != B[i]) return 0;
	}
	return 1;
}

void InsertSort(int Insert[], int m, int N) {
	int i;
	int tmp = Insert[m];
	for (i = m; i > 0 && tmp < Insert[i - 1]; i--) {
		Insert[i] = Insert[i - 1];
	}
	Insert[i] = tmp;
}

void MergeSort(int Merge[], int step, int N) {
	if (step > N) return;//不能判step==N，特殊情况初始条件N==2！ 
	int i, j, k, tmp;
	int n = N / step;//number of mergers 
	if (N % step > 0) n++;
	for (i = 0; i < n; i++) {
		int l = i * step;
		int r = (i + 1) * step - 1;
		if (r >= N) r = N - 1;
		for (j = l + 1; j <= r; j++) {
			tmp = Merge[j];
			for (k = j; k > l && Merge[k - 1] > tmp; k--) {
				Merge[k] = Merge[k - 1];
			}
			Merge[k] = tmp;
		}
	}
}

int main() {
	int i;
	int Sorted[MAXNUM];//partial sorted sequence 
	int A[MAXNUM];//Insertion sort sequence
	int B[MAXNUM];//Merge sort sequence
	int N;
	cin >> N;
	for (i = 0; i < N; i++) {
		cin >> A[i];   
		B[i] = A[i];
	}
	for (i = 0; i < N; i++) {
		cin >> Sorted[i];
	}

	int step1 = 1, step2 = 2;
	int flag = 0;//                0:Insertion,                 1:Merge
	while (step1 < N) {
		flag = 0;
		InsertSort(A, step1, N);
		step1++;
		if (Match(A, Sorted, N)) break;

		flag = 1;
		MergeSort(B, step2, N);
		step2 *= 2;
		if (Match(B, Sorted, N)) break;
	}
	if (flag == 0) {
		cout << "Insertion Sort" << endl;
		InsertSort(Sorted, step1, N);
	}
	else {
		cout << "Merge Sort" << endl;
		MergeSort(Sorted, step2, N);
	}
	for (i = 0; i < N; i++) {
		cout << Sorted[i];
		if (i < N - 1) cout << " ";
		else cout << endl;
	}
	system("pause");
	return 0;
}