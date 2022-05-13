/*
函数题01-复杂度3 二分查找
*/
/*裁判测试程序样例：*/

#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode* List;
struct LNode {
	ElementType Data[MAXSIZE];
	Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch(List L, ElementType X);

int main()
{
	List L;
	ElementType X;
	Position P;

	L = ReadInput();
	cin >> X;
	P = BinarySearch(L, X);
	printf("%d\n", P);

	return 0;
}



/*******************************函数定义——即答案输入******************************************/
Position BinarySearch(List L, ElementType X)
{
	ElementType left = 1;
	ElementType right = L->Last;
	while (left < right)
	{
		if (L->Data[right] == X)    //特殊情况 如果在尾部
			return right;
		ElementType center = (left + right) / 2;
		if (L->Data[center] < X)
			left = center + 1;
		else if (X < L->Data[center])
			right = center - 1;
		else
			return center;
	}
	return NotFound;
}