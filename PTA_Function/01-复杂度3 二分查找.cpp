/*
������01-���Ӷ�3 ���ֲ���
*/
/*���в��Գ���������*/

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
	Position Last; /* �������Ա������һ��Ԫ�ص�λ�� */
};

List ReadInput(); /* ����ʵ�֣�ϸ�ڲ���Ԫ�ش��±�1��ʼ�洢 */
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



/*******************************�������塪����������******************************************/
Position BinarySearch(List L, ElementType X)
{
	ElementType left = 1;
	ElementType right = L->Last;
	while (left < right)
	{
		if (L->Data[right] == X)    //������� �����β��
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