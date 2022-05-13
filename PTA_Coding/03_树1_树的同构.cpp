#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;


#define MaxTree 10     //静态数组定义大小
#define ElementType char
#define Tree int
#define Null -1 //注意是Null不是NULL

struct TreeNode
{
	ElementType Element;
	Tree Left;
	Tree Right;

} T1[MaxTree], T2[MaxTree];

Tree BuildTree(struct TreeNode T[])
{
	int N, i;
	int check[MaxTree] = { -1 };
	char cl, cr;   //current left , current right
	int Root = -1;   //设置成0会段错误
	cin >> N;
	if (N)
	{
		for (i = 0; i < N; i++)   check[i] = 0;
		for (i = 0; i < N; i++)
		{
			cin >> T[i].Element >> cl >> cr;
			if (cl != '-')
			{
				T[i].Left = cl - '0';
				check[T[i].Left] = 1;    //利用check[i]来找到根结点， 就是没有任何爹妈的结点 没有谁的左右子树指向它

			}
			else T[i].Left = Null;
			if (cr != '-')
			{
				T[i].Right = cr - '0';
				check[T[i].Right] = 1;    //利用check[i]来找到根结点， 就是没有任何爹妈的结点 没有谁的左右子树指向它

			}
			else T[i].Right = Null;
		}
		for (i = 0; i < N; i++)
			if (!check[i]) break;   //找到check[i]
		Root = i;
	}
	return Root;
}
int Isomorphic(Tree R1, Tree R2)
{
	if ((R1 == Null) && (R2 == Null))    //全空
		return 1;
	if (((R1 == Null) && (R2 != Null)) || ((R1 != Null) && (R2 == Null)))  //两者其一为空
		return 0;
	if (T1[R1].Element != T2[R2].Element)
		return 0;     //根节点不一样
	if ((T1[R1].Left == Null) && (T2[R2].Left == NULL))    //两树都没左子树 来搜索右子树
		return Isomorphic(T1[R1].Right, T2[R2].Right);
	if (((T1[R1].Left != Null) && (T2[R2].Left != Null)) && ((T1[T1[R1].Left].Element) == (T2[T2[R2].Left].Element))) //左右儿子不为空而且值相等 没必要交换左右  保留下来
		return (Isomorphic(T1[R1].Left, T2[R2].Left) && Isomorphic(T1[R1].Right, T2[R2].Right));
	else    // 左儿子不为空且值不等  或者 某一个左儿子为空
		return (Isomorphic(T1[R1].Right, T2[R2].Left) && Isomorphic(T1[R1].Left, T2[R2].Right));  //需要交换左右
}
int main()
{
	Tree R1, R2;
	R1 = BuildTree(T1);
	R2 = BuildTree(T2);
	if (Isomorphic(R1, R2))
		cout << "Yes";
	else
		cout << "No";

	system("pause");
	return 0;

}