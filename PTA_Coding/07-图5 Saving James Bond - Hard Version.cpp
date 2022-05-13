/*
07-ͼ5 Saving James Bond - Hard Version
���Ѱ汾��������ǲ���Ҫ����ܷ��ȣ���Ҫ���һ�����·����
��Ϊ����Ȩͼ�ĵ�Դ���·�㷨������ֱ����BFS����Щ����Dijkstreaû��Ҫ��
*/
#include <iostream>
#include "math.h"
#include "queue"
#include "stack"
#include "algorithm"
using namespace std;
#define MaxVertex 101 //N<=100
#define MINLEN 42.5   //  42.5=50-7.5  ˵����ֱ�ӵ�����ԵȻ��һ��ֱ���ϰ� ���ò�����
int n, m;
struct Pointer {
	int x;
	int y;
}point[101];
bool answer = false; /* ��¼007�ܷ�ȫ����~~ */
bool collected[MaxVertex]={false}; /* �жϵ�ǰ���Ƿ񱻷��ʹ� */
int path[101] = { -1 }; /* ��¼��Ծ�����вȹ������� */
bool isSave(int x) { /* �жϴӵ�ǰ���ܷ��������� */
	if ((point[x].x - m <= -50) || (point[x].x + m >= 50) || (point[x].y - m <= -50) || (point[x].y + m >= 50))
		return true;
	return false;
}

bool jump(int x, int y) { /* �ж�2��������Ƿ�����Ծ������ */
	int p1 = pow(point[x].x - point[y].x, 2);
	int p2 = pow(point[x].y - point[y].y, 2);
	if (sqrt(p1 + p2) <= m)
		return true;
	return false;
}

int firstJump(int x) {  /* ��007���ڹµ�ʱ ��һ�ο���ѡ���������� ��Ϊ��һ���ж��ܷ���Ծ�ļ��㷽�������dfs����ͬ ����Ҫ����д */
	int p1 = pow(point[x].x, 2);
	int p2 = pow(point[x].y, 2);
	if (sqrt(p1 + p2) <= (m+7.5)) {  //m����Ծ���� 7.5��С���뾶
		return p1 + p2;
	}
	return 0;
}
bool cmp(int a, int b) {   //�Զ���cmp  Ҳ�����Զ���sort���򷽷��ȽϵĶ���
	return firstJump(a) < firstJump(b);
}
void bfs() { /* ��bfs���ж�����Ҫ�ȼ���С��������ϰ� */
	int b[101];
	queue<int>q; //q:��һ������������������
	/* ����һ���ܲȵ������㰴�����С�����˳�������~ ��Ϊ������Ҫ��֤�ڲȵ�����������ȵ������ �����һ��������̵�~~*/
	for (int i = 0; i < n; i++) {
		b[i] = i;
	}
	sort(b, b + n, cmp); /* ���յ�һ���ľ�������~~~ */
	int last;
	
	for (int i = 0; i < n; i++) {   //��¼��һ��������������
		if (firstJump(b[i])) { /* ������ȥ��   �����fisrtJump return=0����Щ���ų�����*/
			q.push(b[i]);   //��һ������������ѹ�����q
			collected[b[i]] = true;
			last = b[i]; /* ���ϸ��� lastָ��ǰ�������һ����~ */
		}
	}
	int step = 2;  /* ��¼����Ҫ��Ծ�Ĵ��� */
	int tail;
	while (!q.empty()) {
		int p = q.front();
		q.pop();     //һ�����Ƚ�q�Ƿ��ܰ�ȫ���ﰶ��
		if (isSave(p)) {  //1����������pֱ����������
			int k = 1;
			stack<int> s;   //�Ƚ������ջ
			cout << step << endl;
			while (k < step) {
				s.push(p);   //p�������
				p = path[p];  //pת����һ������ ����·��ǰһ������
				k++;
			}
			while (!s.empty()) {   //��ջ��Ϊ��
				p = s.top();    //���һ������ջ��p
				s.pop();         //��ջһ��
				cout << point[p].x << " " << point[p].y << endl;
			}
			return;
		}
		for (int i = 0; i < n; i++) { //2�����������������
			if (!collected[i] && jump(p, i)) { /* û�ȹ����������� */
				q.push(i);   //i������
				path[i] = p; /* �ǵõ�ǰ���ӽڵ�ĸ��ڵ�~   p������i ��p��i */
				collected[i] = true;
				tail = i; /* ָ����һ������һ��Ԫ�� */
			}
		}
		if (last == p) { /* last=p  ����������һ��~ */
			step += 1;
			last = tail;
		}
	}
	if (q.empty()) { /* �������Ϊ��  ˵��û����ȥ��~ */
		cout << "0" << endl;
	}
}
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> point[i].x >> point[i].y;
	}
	if (m >= MINLEN) { /* ����ֱ�Ӵӹµ����ᵽ���� ֱ����� */
		cout << "1" << endl;
		return 0;   //û������ ֱ�������С��Ծ����1����
	}

	bfs();
	return 0;
}
