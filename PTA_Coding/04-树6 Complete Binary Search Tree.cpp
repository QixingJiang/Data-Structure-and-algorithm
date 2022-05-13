/*
完全二叉树 不存在左斜树，不担心浪费空间，用数组就可以 没必要链表
而且层序遍历相当于直接顺序输出，不需要链表
*/

#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#define MaxSize 2005
using namespace std;
int value[MaxSize];  
int BST[MaxSize];  
// 计算 n 个结点的树其左树结点个数 
int getLeftTreeSize(int n) {  //考察二叉树性质 第n层上有2^(n-1)个结点 整个二叉树有2^H-1个结点（H层）
	int h = 0;   // 保存该结点下满二叉树的层数 
	int tmp = n + 1;
	while (tmp != 1) {
		tmp /= 2;
		h++;
	}
	int x = n - pow(2, h) + 1;   // 最下面一排子叶结点个数 x
	x = x < pow(2, h - 1) ? x : pow(2, h - 1);   // 子叶结点个数最多是 2^(h-1) 
	int L = pow(2, h - 1) - 1 + x;   // 该结点个数情况下根结点的左子树里儿子个数 
	return L;
}

// 填充函数
void solve1(int Aleft, int Aright, int Troot) {   //排序后的输入序列A   结果树T    
	int n = Aright - Aleft + 1;  // 确定范围内数值个数    n=n
	if (!n)  return;  //n=0 return   迭代终止条件
	int L = getLeftTreeSize(n);   // 找到"偏移量"   计算出n个结点的树左子树有多少个结点 
	BST[Troot] = value[Aleft + L];    // 根结点的值应该是 左边界值 + 偏移量 
	int leftRoot = 2 * Troot + 1;   // 左儿子结点位置，由于从 0 开始  是2*root+1
	int rightRoot = leftRoot + 1;  // 右儿子结点位置 
	solve1(Aleft, Aleft + L - 1, leftRoot);  // 左子树递归 
	solve1(Aleft + L + 1, Aright, rightRoot);   // 右子树递归 
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> value[i];
	}
	// 从小到大排序 
	sort(value, value + n);
	solve1(0, n - 1, 0);   //T的根结点一定是最小的 0位置的
	for (int i = 0; i < n; i++) {
		if (i)
			cout << " ";
		cout << BST[i];
	}
	system("pause");
	return 0;
}