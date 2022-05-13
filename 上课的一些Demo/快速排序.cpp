#include<iostream>
using namespace std;
void Quicksort(ElementType A[], int Left, int Right)   //传入三个参数 不符合普通的接口（一般只传入数组名称和数个数）
{
	if (Cutoff <= Right - Left) {   //规模大于阈值才用快速排序
		Pivot = Median3(A, Left, Right);   //求主元 主元Pivot被藏在Right-1的位置上
		i = Left;
		j = Right - 1;//开始子集划分  
		for (;;)
		{
			while (A[++i] < Pivot)
			{

			}
			while (A[--j] > Pivot)
			{

			}
			if (i < j)
			{
				Swap(&A[i], &A[j]);
			}
			else break;
		}
		Swap(&A[i], &A[Right - 1]); //把主元（Right-1）换到A[i]的位置 完成子集划分 
		Quciksort(A, Left, i - 1);

		Quciksort(A, i + 1, Right);  //递归解决左右子集
	}
	else
		Insertion_Sort(A + Left, Right-Left + 1); //不满足大于阈值就直接用插入排序 更快   Right-Left+1是当前待排序数列的总个数
}

void Quick_Sort(ElementType A[], int N)  //套壳
{
	Quicksort(A, 0, N - 1);  
}