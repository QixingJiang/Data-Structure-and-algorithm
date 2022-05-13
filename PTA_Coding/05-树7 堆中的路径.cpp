#include<iostream>
#define MAXN 1001    //N为插入元素个数 
#define MINH -10001
using namespace std;

int H[MAXN], sizze;
void Create() {
	sizze = 0;   //因为std里有size 别用size
	H[0] = MINH;
}

void Insert(int X)
{	//将X插入H
	int i;
	if (sizze >= MAXN) return;
	for (i = ++sizze; H[i / 2] > X; i /= 2)  //size先自加，然后i=size    然后i=i/2 size最终=n
		H[i] = H[i / 2];     //父节点比我大，那我跟父节点换    
	H[i] = X;

}

int main()
{
	int n, m, x, i,j;
	cin >> n;
	cin >> m;
	Create();  //堆初始化
	for (i = 0; i < n; i++) {    //一个个插入的方式建立堆 注意这里是小顶堆
		cin >> x;
		Insert(x);
	}
	for (int i = 0; i < m; i++) {
		cin >> j;
		cout << H[j];  //先输出最下面的叶结点H[j]
		while (j>1)            //j>1说明还不是根结点
		{
			j /= 2;
			cout << " "<<H[j];
		}   //依次输出他的父节点
		cout << endl;
	}
	system("pause");
	return 0;
}




