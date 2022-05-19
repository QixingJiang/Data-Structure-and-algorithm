#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;


//可以用暴力算法 但是KMP的复杂度为O(m+n)

/***********************************建立前缀后缀数组**********************************************/
void BuildMatch(string pattern, int match[]) {
	int m = pattern.size();
	int i, j;
	match[0] = -1;
	for (j = 1; j < m; j++) {
		i = match[j - 1];//记录上⼀个⼦串的前缀长度为i
		while (i >= 0 && pattern[i + 1] != pattern[j]) {//⼀直回退match，递归找合适的匹配值  类似动态规划
			i = match[i];   //当最后一位新的匹配不上的时候，需要回溯到前面
		}
		if (pattern[i + 1] == pattern[j]) {  //j因为加了1 相当于这个比上个子串多了一位尾数，比较一下这个尾数跟之前pattern[i+1]相等不，相等的话这个字符串比上一个子串的前缀长度多1
			match[j] = i + 1;
		}
		else {
			match[j] = -1;
		}
	}
}
//KMP核⼼算法  原理就是在已匹配的字符串中，找到最大真子缀，省略已匹配部分，相当于简略的快速匹配。
int KMP(string str, string pattern) {
	int n = str.size();
	int m = pattern.size();
	if (m > n) { //特殊情况 pattern比str长
		return -1;
	}
	int match[100000];
	BuildMatch(pattern, match); //建立一个match数组，是前缀后缀数组
	int p, s;
	p = s = 0;
	while (p < m && s < n) {
		if (pattern[p] == str[s]) {
			p++; s++;               //检索没匹配上的那个位置
		}
		else if (p > 0) {
			p = match[p - 1] + 1;//回退到上⼀个匹配串的下⼀个不匹配位置
		}
		else {
			s++;
		}
	}
	return (p == m) ? (s - m) : -1;    
}

int main()
{
	string str, pattern;
	cin >> str;
	int N, Pos;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> pattern;
		Pos = KMP(str, pattern);
		if (Pos == -1) {
			cout << "Not Found" << endl;
		}
		else {
			for (int j = Pos; j < str.size(); j++) {
				cout << str[j];
			}
			printf("\n");
		}
	}


	return 0;
}