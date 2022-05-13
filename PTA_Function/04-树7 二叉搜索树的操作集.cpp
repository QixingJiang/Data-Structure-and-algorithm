/*
������04-��7 �����������Ĳ�����
*/



/*************************************���в��Գ�������************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

void PreorderTraversal(BinTree BT); /* ����������ɲ���ʵ�֣�ϸ�ڲ��� */
void InorderTraversal(BinTree BT);  /* ����������ɲ���ʵ�֣�ϸ�ڲ��� */

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

int main()
{
	BinTree BST, MinP, MaxP, Tmp;
	ElementType X;
	int N, i;

	BST = NULL;
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &X);
		BST = Insert(BST, X);
	}
	printf("Preorder:"); PreorderTraversal(BST); printf("\n");
	MinP = FindMin(BST);
	MaxP = FindMax(BST);
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &X);
		Tmp = Find(BST, X);
		if (Tmp == NULL) printf("%d is not found\n", X);
		else {
			printf("%d is found\n", Tmp->Data);
			if (Tmp == MinP) printf("%d is the smallest key\n", Tmp->Data);
			if (Tmp == MaxP) printf("%d is the largest key\n", Tmp->Data);
		}
	}
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &X);
		BST = Delete(BST, X);
	}
	printf("Inorder:"); InorderTraversal(BST); printf("\n");

	return 0;
}






/******************************************����ʵ�ִ����������ύ******************************************************/
// ���� 
BinTree Insert(BinTree BST, ElementType X) {
	if (!BST) {  // ���Ϊ�գ������½�� 
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = NULL;
		BST->Right = NULL;
	}
	else {
		if (X < BST->Data)
			BST->Left = Insert(BST->Left, X);
		else if (BST->Data < X)
			BST->Right = Insert(BST->Right, X);
	}
	return BST;
}

// ɾ��
BinTree Delete(BinTree BST, ElementType X) {
	BinTree tmp;
	if (!BST) {
		printf("Not Found\n");
		return BST;
	}
	else {
		if (X < BST->Data)
			BST->Left = Delete(BST->Left, X);
		else if (BST->Data < X)
			BST->Right = Delete(BST->Right, X);
		else {  // �ҵ�Ҫɾ����� 
			if (BST->Left && BST->Right) {  // ����ý�������Ҷ��� 
				tmp = FindMin(BST->Right);
				BST->Data = tmp->Data;
				BST->Right = Delete(BST->Right, tmp->Data);
			}
			else {
				tmp = BST;
				if (BST->Left && !BST->Right)
					BST = BST->Left;
				else if (!BST->Left && BST->Right)
					BST = BST->Right;
				else
					BST = NULL;
				free(tmp);
			}
		}
	}
	return BST;
}

// Ѱ��ֵ��С��� 
Position FindMin(BinTree BST) {
	if (BST)
		while (BST->Left)
			BST = BST->Left;
	return BST;
}

// Ѱ��ֵ�����
Position FindMax(BinTree BST) {
	if (BST)
		while (BST->Right)
			BST = BST->Right;
	return BST;
}

// ����
Position Find(BinTree BST, ElementType X) {
	if (!BST) {
		return NULL;
	}
	else if (X < BST->Data)
		return Find(BST->Left, X);
	else if (BST->Data < X)
		return Find(BST->Right, X);
	else
		return BST;
}
