#include<stdio.h>
#include<malloc.h>
#include<iostream>
using namespace std;
typedef struct AVLNode* Position;
typedef Position AVLTree;/*AVL������*/
struct AVLNode {
	int data;      /*�ڵ�����*/
	AVLTree Left;  /*ָ��������*/
	AVLTree Right; /*ָ��������*/
	int Height;    /*���ĸ߶�*/
};

int Max(int a, int b)
{
	int max = a > b ? a : b;   //a>b ѡa��Ȼѡb
	return max;
}

int GetHeight(Position T)
{
	int height;
	if (T == NULL) height = -1;
	else height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;   //�������������ȡ���Ȼ��+1�����ϸ���㣩
	return height;
}


AVLTree SingleLeftRotation(AVLTree A)
{/*ע�⣬A������һ������B*/
/*��A��B������������A��B�ĸ߶ȣ������µĸ����B*/

	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), A->Height) + 1;

	return B;
}

AVLTree SingleRightRotation(AVLTree A)
{/*ע�⣬A������һ���ҽ��B*/
/*��A��B���ҵ���������A��B�ĸ߶ȣ������µĸ����B*/

	AVLTree B = A->Right;
	A->Right = B->Left;
	B->Left = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Right), A->Height) + 1;

	return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{
	/*��B��C���ҵ���,C������*/
	A->Left = SingleRightRotation(A->Left);
	/*��A��C������,C������*/
	return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A)
{
	/*��B��C������,C������*/
	A->Right = SingleLeftRotation(A->Right);
	/*��A��C���ҵ���,C������*/
	return SingleRightRotation(A);
}

AVLTree Insert(AVLTree T, int x)
{/*��x����	AVL��T�У����ҷ��ص������AVL��*/
	AVLTree T2 = T;
	if (!T) {/*�������һ����������������һ�������*/
		T = (Position)malloc(sizeof(struct AVLNode));
		T->data = x;
		T->Height = 1;
		T->Left = NULL;
		T->Right = NULL;
	}
	else if (x < T->data) {
		/*����T��������*/
		T->Left = Insert(T->Left, x);
		/*�����Ҫ����*/
		if (GetHeight(T->Left) - GetHeight(T->Right) == 2) {
			if (x < T->Left->data)
				T = SingleLeftRotation(T);/*����*/
			else
				T = DoubleLeftRightRotation(T);/*����˫��*/
		}
	}
	else if (x > T->data) {
		/*����T��������*/
		T->Right = Insert(T->Right, x);
		/*�����Ҫ����*/
		if (GetHeight(T->Right) - GetHeight(T->Left) == 2) {
			if (x > T->Right->data)
				T = SingleRightRotation(T);/*�ҵ���*/
			else
				T = DoubleRightLeftRotation(T);/*����˫��*/
		}
	}

	/*��������*/
	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
	return T;
}

int main()
{
	AVLTree T = NULL;
	int N, i, x;
	cin >> N;
	for (i = 0; i < N; i++) {
		cin >> x;
		T = Insert(T, x);
	}
	cout << T->data;
	return 0;
}
