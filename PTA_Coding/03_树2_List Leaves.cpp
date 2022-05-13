#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
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
	int check[MaxTree] = { 0 };
	char cl, cr;   //current left , current right
	int Root = -1;
	cin >> N;
	if (N)
	{
		for (i = 0; i < N; i++)
		{
			cin >> cl >> cr;  //只需要输入左右结点 
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
void LevelOrderTraverse(struct TreeNode T[], int x)   {    //层序遍历
	queue<int>q;
	int temp;
	int leaves = 0;  //标记是第几个节点
	q.push(x);//根据根节点下标去入队

	while (!q.empty())
	{
		temp = q.front();
		q.pop();
		if (T[temp].Left == -1 && T[temp].Right == -1)
		{
			if (leaves)
				cout << " ";
			cout << temp;
			++leaves;
		}
		if (T[temp].Left != -1)
		    q.push(T[temp].Left);//左孩子入队
		if (T[temp].Right != -1)
	        q.push(T[temp].Right); //右孩子入队
	}

}
int main()
{
	TreeNode T1[MaxTree];
	Tree R1;
	R1 = BuildTree(T1);
	LevelOrderTraverse(T1,R1);
	system("pause");
	return 0;

}