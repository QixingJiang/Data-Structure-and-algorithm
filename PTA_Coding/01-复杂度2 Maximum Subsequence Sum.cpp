/*
01-���Ӷ�2 Maximum Subsequence Sum
*/

#include<iostream>
using namespace std;
int main() {
	int n;
	int a[100000 + 5];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int left = 0;
	int tmpleft = 0;
	int right = n - 1;
	int max = 0;
	int tmpSum = 0;
	for (int i = 0; i < n; i++) {
		tmpSum += a[i];
		if (tmpSum < 0) {
			tmpSum = 0;
			tmpleft = i + 1;   // ��ͷ����������α����������е���һ�� 
		}
		else if (max < tmpSum) {
			max = tmpSum;
			left = tmpleft;   // ÿ�θ������ֵҲ��ȷ����һ�������У������ʱ�Ŀ�ͷ 
			right = i;       // ��β��������ÿ�θ������ֵʱ 
		}
	}
	if (max >= 0)
		cout << max << " " << a[left] << " " << a[right];
	else
		cout << 0 << " " << a[0] << " " << a[n - 1];
	return 0;
}