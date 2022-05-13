#include<stdio.h>
#include<malloc.h>
#include<iostream>
using namespace std;
typedef struct AVLNode* Position;
typedef Position AVLTree;/*AVL树类型*/
struct AVLNode {
	int data;      /*节点数据*/
	AVLTree Left;  /*指向左子树*/
	AVLTree Right; /*指向右子树*/
	int Height;    /*树的高度*/
};

int Max(int a, int b)
{
	int max = a > b ? a : b;   //a>b 选a不然选b
	return max;
}

int GetHeight(Position T)
{
	int height;
	if (T == NULL) height = -1;
	else height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;   //左右子树的深度取最大然后+1（算上根结点）
	return height;
}


AVLTree SingleLeftRotation(AVLTree A)
{/*注意，A必须有一个左结点B*/
/*将A与B做左单旋，更新A与B的高度，返回新的根结点B*/

	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), A->Height) + 1;

	return B;
}

AVLTree SingleRightRotation(AVLTree A)
{/*注意，A必须有一个右结点B*/
/*将A与B做右单旋，更新A与B的高度，返回新的根结点B*/

	AVLTree B = A->Right;
	A->Right = B->Left;
	B->Left = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Right), A->Height) + 1;

	return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{
	/*将B与C做右单旋,C被返回*/
	A->Left = SingleRightRotation(A->Left);
	/*将A与C做左单旋,C被返回*/
	return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A)
{
	/*将B与C做左单旋,C被返回*/
	A->Right = SingleLeftRotation(A->Right);
	/*将A与C做右单旋,C被返回*/
	return SingleRightRotation(A);
}

AVLTree Insert(AVLTree T, int x)
{/*将x插入	AVL树T中，并且返回调整后的AVL树*/
	AVLTree T2 = T;
	if (!T) {/*如果插入一个空树，则建立包含一个结点树*/
		T = (Position)malloc(sizeof(struct AVLNode));
		T->data = x;
		T->Height = 1;
		T->Left = NULL;
		T->Right = NULL;
	}
	else if (x < T->data) {
		/*插入T的左子树*/
		T->Left = Insert(T->Left, x);
		/*如果需要左旋*/
		if (GetHeight(T->Left) - GetHeight(T->Right) == 2) {
			if (x < T->Left->data)
				T = SingleLeftRotation(T);/*左单旋*/
			else
				T = DoubleLeftRightRotation(T);/*左右双旋*/
		}
	}
	else if (x > T->data) {
		/*插入T的右子树*/
		T->Right = Insert(T->Right, x);
		/*如果需要右旋*/
		if (GetHeight(T->Right) - GetHeight(T->Left) == 2) {
			if (x > T->Right->data)
				T = SingleRightRotation(T);/*右单旋*/
			else
				T = DoubleRightLeftRotation(T);/*右左双旋*/
		}
	}

	/*更新树高*/
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
