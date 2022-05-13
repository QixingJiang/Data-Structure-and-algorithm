#include<cstdio>
#include<stack>
#include<iostream>
#include<string>
using namespace std;

#define MAX 30
int preOrder[MAX];
int inOrder[MAX];
int postOrder[MAX];

//push过程就是前序遍历，pop过程就是中序遍历inorder，就是要写一个根据前序preorder和中序遍历inorder确定后序遍历postorder的算法。
//根据前序和中序划分，来确定后序遍历。前序的第一个数字为根结点，
//找到根结点root在中序数组位置，中序数组中root左边为根结点左子树，右边为右子树
void Solve(int preL, int inL, int postL, int n) {   //preL是某个元素在前序遍历的位置，inL是中序遍历的位置 同理…… n是n个数  
	if (n == 0)return;   //输入0个数  （空） 或者说直到传入=0 循环结束 这个时候相当于左或者右结点已经没了 缺少这行会报错
	if (n == 1) {      //输入一个数  前序=后序
		postOrder[postL] = preOrder[preL];   
	}
	int root = preOrder[preL];   //前序的第一个是根结点
	postOrder[postL + n - 1] = root;   //根结点在后序中是最后一个   核心步骤 构造postOrder这个数组的内容
	int i, R, L;
	for (i = 0; i<n; i++) {
		if (root == inOrder[inL + i])break;  //计算出根结点在中序系列中的位置inL+i  主要是i
	}
	L = i, R = n - i - 1;        //L为左子树结点数目=i，R为右子树结点数目=n-i-1（1是根结点）
	//对左右子树相同的方法进行递归直到L=R=0
	Solve(preL + 1, inL, postL, L);    //确定后序数组中根结点root左边的排列顺序  左边元素个数=L ，inL和postL都不变
	Solve(preL + L + 1, inL + L + 1, postL + L, R);    //确定后序数组中根结点root右边的排列顺序      preL+L+1是root右边的第一个元素位置 inL也是
}

int main() {
	int n;
	for (int i = 0; i<MAX; i++) {
		preOrder[i] = 0;
		inOrder[i] = 0;
		postOrder[i] = 0;
	}
	stack<int> s;
	cin >> n;
	string str;
	int data;
	int index = 0, pos = 0;
	for (int i = 0; i<2 * n; i++) {
		cin >> str;
		if (str == "Push") {      //push代表前序遍历
			cin >> data;
			s.push(data);
			preOrder[index++] = data;
		}
		else if (str == "Pop") { //pop为中序遍历
			inOrder[pos++] = s.top();
			s.pop();
		}
	}  //对前序和中序排列进行填充 
	Solve(0, 0, 0, n);  //传递的参数三个0只是三个排序的第一位 具体操作是具体的preOrder 等数组
	for (int i = 0; i<n; i++) {   //计算出postOrder 也就是说不用建树 只要计算结果
		if (i>0)printf(" ");
		printf("%d", postOrder[i]);
	}
	system("pause");
	return 0;
}