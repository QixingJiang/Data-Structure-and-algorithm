/*
07-图5 Saving James Bond - Hard Version
困难版本的区别就是不仅要输出能否获救，还要输出一条最短路径。
因为是无权图的单源最短路算法，所以直接用BFS，有些人用Dijkstrea没必要。
*/
#include <iostream>
#include "math.h"
#include "queue"
#include "stack"
#include "algorithm"
using namespace std;
#define MaxVertex 101 //N<=100
#define MINLEN 42.5   //  42.5=50-7.5  说明能直接到岛边缘然后一跳直接上岸 不用踩鳄鱼
int n, m;
struct Pointer {
	int x;
	int y;
}point[101];
bool answer = false; /* 记录007能否安全逃生~~ */
bool collected[MaxVertex]={false}; /* 判断当前点是否被访问过 */
int path[101] = { -1 }; /* 记录跳跃过程中踩过的鳄鱼 */
bool isSave(int x) { /* 判断从当前点能否跳到岸上 */
	if ((point[x].x - m <= -50) || (point[x].x + m >= 50) || (point[x].y - m <= -50) || (point[x].y + m >= 50))
		return true;
	return false;
}

bool jump(int x, int y) { /* 判断2个点距离是否在跳跃能力内 */
	int p1 = pow(point[x].x - point[y].x, 2);
	int p2 = pow(point[x].y - point[y].y, 2);
	if (sqrt(p1 + p2) <= m)
		return true;
	return false;
}

int firstJump(int x) {  /* 当007处于孤岛时 第一次可以选择跳的鳄鱼 因为第一次判断能否跳跃的计算方法与后面dfs不相同 所以要单独写 */
	int p1 = pow(point[x].x, 2);
	int p2 = pow(point[x].y, 2);
	if (sqrt(p1 + p2) <= (m+7.5)) {  //m是跳跃距离 7.5是小岛半径
		return p1 + p2;
	}
	return 0;
}
bool cmp(int a, int b) {   //自定义cmp  也就是自定义sort排序方法比较的东西
	return firstJump(a) < firstJump(b);
}
void bfs() { /* 用bfs来判断最少要踩几个小鳄鱼才能上岸 */
	int b[101];
	queue<int>q; //q:第一跳能跳到的所有鳄鱼
	/* 将第一步能踩到的鳄鱼按距离从小到大的顺序进队列~ 因为输出结果要保证在踩的鳄鱼数量相等的情况下 输出第一步距离最短的~~*/
	for (int i = 0; i < n; i++) {
		b[i] = i;
	}
	sort(b, b + n, cmp); /* 按照第一步的距离排序~~~ */
	int last;
	
	for (int i = 0; i < n; i++) {   //记录第一跳能跳到的鳄鱼
		if (firstJump(b[i])) { /* 能跳上去！   这里把fisrtJump return=0的那些点排除掉了*/
			q.push(b[i]);   //第一跳的所有鳄鱼压入队列q
			collected[b[i]] = true;
			last = b[i]; /* 不断更新 last指向当前层数最后一个数~ */
		}
	}
	int step = 2;  /* 记录最少要跳跃的次数 */
	int tail;
	while (!q.empty()) {
		int p = q.front();
		q.pop();     //一个个比较q是否能安全到达岸边
		if (isSave(p)) {  //1、如果这个点p直接能跳到岸
			int k = 1;
			stack<int> s;   //先进后出堆栈
			cout << step << endl;
			while (k < step) {
				s.push(p);   //p鳄鱼入堆
				p = path[p];  //p转到上一个鳄鱼 跳的路上前一个鳄鱼
				k++;
			}
			while (!s.empty()) {   //堆栈不为空
				p = s.top();    //最后一个进堆栈的p
				s.pop();         //出栈一个
				cout << point[p].x << " " << point[p].y << endl;
			}
			return;
		}
		for (int i = 0; i < n; i++) { //2、否则，如果还得再跳
			if (!collected[i] && jump(p, i)) { /* 没踩过并且能跳到 */
				q.push(i);   //i进队列
				path[i] = p; /* 记得当前进队节点的父节点~   p能跳到i 即p到i */
				collected[i] = true;
				tail = i; /* 指向下一层的最后一个元素 */
			}
		}
		if (last == p) { /* last=p  即将进入下一层~ */
			step += 1;
			last = tail;
		}
	}
	if (q.empty()) { /* 如果队列为空  说明没跳出去啊~ */
		cout << "0" << endl;
	}
}
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> point[i].x >> point[i].y;
	}
	if (m >= MINLEN) { /* 可以直接从孤岛上提到岸上 直接输出 */
		cout << "1" << endl;
		return 0;   //没有鳄鱼 直接输出最小跳跃次数1就行
	}

	bfs();
	return 0;
}
