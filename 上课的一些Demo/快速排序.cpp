#include<iostream>
using namespace std;
void Quicksort(ElementType A[], int Left, int Right)   //������������ ��������ͨ�Ľӿڣ�һ��ֻ�����������ƺ���������
{
	if (Cutoff <= Right - Left) {   //��ģ������ֵ���ÿ�������
		Pivot = Median3(A, Left, Right);   //����Ԫ ��ԪPivot������Right-1��λ����
		i = Left;
		j = Right - 1;//��ʼ�Ӽ�����  
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
		Swap(&A[i], &A[Right - 1]); //����Ԫ��Right-1������A[i]��λ�� ����Ӽ����� 
		Quciksort(A, Left, i - 1);

		Quciksort(A, i + 1, Right);  //�ݹ��������Ӽ�
	}
	else
		Insertion_Sort(A + Left, Right-Left + 1); //�����������ֵ��ֱ���ò������� ����   Right-Left+1�ǵ�ǰ���������е��ܸ���
}

void Quick_Sort(ElementType A[], int N)  //�׿�
{
	Quicksort(A, 0, N - 1);  
}