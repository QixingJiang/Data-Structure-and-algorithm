#include<iostream>
#define MAXN 1001    //NΪ����Ԫ�ظ��� 
#define MINH -10001
using namespace std;

int H[MAXN], sizze;
void Create() {
	sizze = 0;   //��Ϊstd����size ����size
	H[0] = MINH;
}

void Insert(int X)
{	//��X����H
	int i;
	if (sizze >= MAXN) return;
	for (i = ++sizze; H[i / 2] > X; i /= 2)  //size���Լӣ�Ȼ��i=size    Ȼ��i=i/2 size����=n
		H[i] = H[i / 2];     //���ڵ���Ҵ����Ҹ����ڵ㻻    
	H[i] = X;

}

int main()
{
	int n, m, x, i,j;
	cin >> n;
	cin >> m;
	Create();  //�ѳ�ʼ��
	for (i = 0; i < n; i++) {    //һ��������ķ�ʽ������ ע��������С����
		cin >> x;
		Insert(x);
	}
	for (int i = 0; i < m; i++) {
		cin >> j;
		cout << H[j];  //������������Ҷ���H[j]
		while (j>1)            //j>1˵�������Ǹ����
		{
			j /= 2;
			cout << " "<<H[j];
		}   //����������ĸ��ڵ�
		cout << endl;
	}
	system("pause");
	return 0;
}




