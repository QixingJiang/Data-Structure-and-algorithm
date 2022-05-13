/*
跟上一题思想差不多 只是堆排序更复杂一点
*/
#include<stdio.h>
#include<algorithm>
#include<iostream>
using namespace std;
#define MAXNUM 65535
//*************
//InsertSort
//*************
void InsertSort(int Insert[], int step, int N) {
	int i;
	int tmp = Insert[step];
	for (i = step; i > 0 && tmp < Insert[i - 1]; i--) Insert[i] = Insert[i - 1];
	Insert[i] = tmp;
}

//*************
//HeapSort
//*************
void Swap(int A[], int p, int q) {
	int tmp = A[p];
	A[p] = A[q];
	A[q] = tmp;
}
void AdjustHeap(int Heap[], int p, int Last) {
	int Parent, Child;
	int tmp = Heap[p];
	for (Parent = p; Parent * 2 + 1 < Last; Parent = Child) {
		Child = Parent * 2 + 1;
		if (Child + 1 < Last && Heap[Child + 1] > Heap[Child]) Child++;
		if (Heap[Child] > tmp) Heap[Parent] = Heap[Child];
		else break;
	}
	Heap[Parent] = tmp;
}
void BuildMaxHeap(int Heap[], int N) {
	int i;
	for (i = (N - 1) / 2; i >= 0; i--) { //从下到上调整每一课子树 
		AdjustHeap(Heap, i, N);
	}
	//	for(i=0;i<N;i++) printf("%d ",Heap[i]);
}
void HeapSort(int Heap[], int step, int N) {
	int Last = N - step;
	if (Last <= 0) return;
	Swap(Heap, 0, Last);
	AdjustHeap(Heap, 0, Last);
}


//*************
//Match
//*************
int Match(int A[], int Sorted[], int N) {
	int i;
	for (i = 0; i < N; i++) {
		if (A[i] != Sorted[i]) return 0;
	}
	return 1;
}

/******************主函数************************/
int main() {
	int i;
	int N;
	cin >> N;
	int Sorted[MAXNUM], Insert[MAXNUM], Heap[MAXNUM];
	for (i = 0; i < N; i++) {
		cin >> Insert[i];
		Heap[i] = Insert[i];
	}
	for (i = 0; i < N; i++)
		cin>> Sorted[i];

	BuildMaxHeap(Heap, N); //需要先在比较前建起最大堆才能同步step 
	int step = 1;
	int flag = 0;//1:Insert,2:Heap
	while (step < N) {
		InsertSort(Insert, step, N);
		if (Match(Insert, Sorted, N)) {
			flag = 1;
			break;
		}
		else HeapSort(Heap, step, N);
		if (Match(Heap, Sorted, N)) {
			flag = 2;
			break;
		}
		step++;
	}

	if (flag == 1) {
		cout << "Insertion Sort" << endl;
		InsertSort(Sorted, step + 1, N);
	}
	else if (flag == 2) {
		cout << "Heap Sort" << endl;
		HeapSort(Sorted, step + 1, N);
	}

	for (i = 0; i < N; i++) {
		cout << Sorted[i];
		if (i < N - 1) cout << " ";
		else cout << endl;
	}
	return 0;
}