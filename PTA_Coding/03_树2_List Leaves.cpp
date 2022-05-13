#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
using namespace std;


#define MaxTree 10     //��̬���鶨���С
#define ElementType char
#define Tree int
#define Null -1 //ע����Null����NULL

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
			cin >> cl >> cr;  //ֻ��Ҫ�������ҽ�� 
			if (cl != '-')
			{
				T[i].Left = cl - '0';
				check[T[i].Left] = 1;    //����check[i]���ҵ�����㣬 ����û���κε���Ľ�� û��˭����������ָ����

			}
			else T[i].Left = Null;
			if (cr != '-')
			{
				T[i].Right = cr - '0';
				check[T[i].Right] = 1;    //����check[i]���ҵ�����㣬 ����û���κε���Ľ�� û��˭����������ָ����

			}
			else T[i].Right = Null;
		}
		for (i = 0; i < N; i++)
			if (!check[i]) break;   //�ҵ�check[i]
		Root = i;
	}
	return Root;
}
void LevelOrderTraverse(struct TreeNode T[], int x)   {    //�������
	queue<int>q;
	int temp;
	int leaves = 0;  //����ǵڼ����ڵ�
	q.push(x);//���ݸ��ڵ��±�ȥ���

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
		    q.push(T[temp].Left);//�������
		if (T[temp].Right != -1)
	        q.push(T[temp].Right); //�Һ������
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