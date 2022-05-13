#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
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
	int check[MaxTree] = { -1 };
	char cl, cr;   //current left , current right
	int Root = -1;   //���ó�0��δ���
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
int Isomorphic(Tree R1, Tree R2)
{
	if ((R1 == Null) && (R2 == Null))    //ȫ��
		return 1;
	if (((R1 == Null) && (R2 != Null)) || ((R1 != Null) && (R2 == Null)))  //������һΪ��
		return 0;
	if (T1[R1].Element != T2[R2].Element)
		return 0;     //���ڵ㲻һ��
	if ((T1[R1].Left == Null) && (T2[R2].Left == NULL))    //������û������ ������������
		return Isomorphic(T1[R1].Right, T2[R2].Right);
	if (((T1[R1].Left != Null) && (T2[R2].Left != Null)) && ((T1[T1[R1].Left].Element) == (T2[T2[R2].Left].Element))) //���Ҷ��Ӳ�Ϊ�ն���ֵ��� û��Ҫ��������  ��������
		return (Isomorphic(T1[R1].Left, T2[R2].Left) && Isomorphic(T1[R1].Right, T2[R2].Right));
	else    // ����Ӳ�Ϊ����ֵ����  ���� ĳһ�������Ϊ��
		return (Isomorphic(T1[R1].Right, T2[R2].Left) && Isomorphic(T1[R1].Left, T2[R2].Right));  //��Ҫ��������
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