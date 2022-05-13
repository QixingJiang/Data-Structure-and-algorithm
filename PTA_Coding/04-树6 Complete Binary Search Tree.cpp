/*
��ȫ������ ��������б�����������˷ѿռ䣬������Ϳ��� û��Ҫ����
���Ҳ�������൱��ֱ��˳�����������Ҫ����
*/

#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#define MaxSize 2005
using namespace std;
int value[MaxSize];  
int BST[MaxSize];  
// ���� n �������������������� 
int getLeftTreeSize(int n) {  //������������� ��n������2^(n-1)����� ������������2^H-1����㣨H�㣩
	int h = 0;   // ����ý�������������Ĳ��� 
	int tmp = n + 1;
	while (tmp != 1) {
		tmp /= 2;
		h++;
	}
	int x = n - pow(2, h) + 1;   // ������һ����Ҷ������ x
	x = x < pow(2, h - 1) ? x : pow(2, h - 1);   // ��Ҷ����������� 2^(h-1) 
	int L = pow(2, h - 1) - 1 + x;   // �ý���������¸���������������Ӹ��� 
	return L;
}

// ��亯��
void solve1(int Aleft, int Aright, int Troot) {   //��������������A   �����T    
	int n = Aright - Aleft + 1;  // ȷ����Χ����ֵ����    n=n
	if (!n)  return;  //n=0 return   ������ֹ����
	int L = getLeftTreeSize(n);   // �ҵ�"ƫ����"   �����n���������������ж��ٸ���� 
	BST[Troot] = value[Aleft + L];    // ������ֵӦ���� ��߽�ֵ + ƫ���� 
	int leftRoot = 2 * Troot + 1;   // ����ӽ��λ�ã����ڴ� 0 ��ʼ  ��2*root+1
	int rightRoot = leftRoot + 1;  // �Ҷ��ӽ��λ�� 
	solve1(Aleft, Aleft + L - 1, leftRoot);  // �������ݹ� 
	solve1(Aleft + L + 1, Aright, rightRoot);   // �������ݹ� 
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> value[i];
	}
	// ��С�������� 
	sort(value, value + n);
	solve1(0, n - 1, 0);   //T�ĸ����һ������С�� 0λ�õ�
	for (int i = 0; i < n; i++) {
		if (i)
			cout << " ";
		cout << BST[i];
	}
	system("pause");
	return 0;
}