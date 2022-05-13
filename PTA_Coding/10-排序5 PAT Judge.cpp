/*
10-排序5 PAT Judge
第一行输入三个数字 依次是用户总数  问题总数 提交总次数
然后第二行输入 每个问题的满分（最高分数）
然后下面开始依次输入每次提交的信息：用户ID  对应问题序号  得到的分数  （-1代表编译失败）
输出的结果是从高到低输出每个用户的信息（按照总分排序）  输出内容：用户ID 总分 每个问题的得分 
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
//按照问题特点定义一个结构 里面放了每个用户的总分
struct UserNode {
	int total;
	int perfect;  //如果总分一样 要用完美提交问题的次数来排序
	int* score; //score指针用来指向一个存放各个问题成绩的数组
};
UserNode* ranklist[10001];  //用户总数<10^4

//定义排序的规则  
//true表示位置正确，无需进行交换
//false表示位置错误，进行位置的交换
bool cmp(int a, int b) { 
	if (ranklist[a]->total > ranklist[b]->total)
		return true;
	else if (ranklist[a]->total == ranklist[b]->total) {
		if (ranklist[a]->perfect > ranklist[b]->perfect)
			return true;
		else if (ranklist[a]->perfect == ranklist[b]->perfect)
			if (a < b)return true;
	}
	return false;
}
/*******************************main函数*************************************/
int main() {
	int i, j, t, n, k, m, id, problem, score, flag, r, temp, s[5];  // n:用户总数 k:问题总数 m：提交次数   r：排名
	vector<int> rlist;  //rlist:里面按照排名记录了每个用户 。是向量类型的容器。

	cin >> n >> k >> m;   
	for (i = 0; i < k; i++)
		cin >> s[i];   //输入每个问题的总分(满分)
	for (i = 1; i <= n; i++)
		ranklist[i] = NULL; //先初始化每个人的排名


	/*********************输入每次提交的信息*******************************/
	while (m--) {    //当m不等于0 执行后减  实现每次提交后的更新
		cin >> id >> problem >> score;
		if (!ranklist[id]) {  //如果这个用户第一次输入 那就是空  就先初始化 
			ranklist[id] = new UserNode;
			ranklist[id]->score = new int[k];   //new int[] 是创建一个int型数组，数组大小是在[]中指定 。实现创建存放每个问题成绩的数组scroe[k]
			for (j = 0; j < k; j++)
				ranklist[id]->score[j] = -2;
			ranklist[id]->total = 0;
			ranklist[id]->perfect = 0;
		}
		//如果这个用户不是第一次输入（已经提交过东西了）
		// score：当前输入提交次数对应的成绩    ranklist[id]->score[problem - 1] 一开始初始化为-2  依次更新为提交的最大值	 
		if (ranklist[id]->score[problem - 1] < score)   //problem的序号是从1开始  1-N 所以对应score数组元素是problem-1
			ranklist[id]->score[problem - 1] = score;
	}
	for (i = 1; i <= n; i++) {
		if (ranklist[i]) {   //ranklist[i]不为空 代表有这个用户存在
			flag = 0; //flag来判断这个用户的这个问题有没有编译成功过
			for (j = 0; j < k; j++) {
				if (ranklist[i]->score[j] >= 0) {
					flag = 1;
					ranklist[i]->total += ranklist[i]->score[j];  //如果一个问题提交成功（成绩不是-1）  就加到总分上
				}
				if (ranklist[i]->score[j] == s[j])
					ranklist[i]->perfect++;  //顺便统计下该用户完美提交次数
			}
			if (flag) rlist.push_back(i);   //push_back:在vector类中作用为在vector尾部加入一个数据  这里加入用户id
		} 
	}

	sort(rlist.begin(), rlist.end(), cmp); //rlist里的元素进行从小到大排序 每个元素都是一个ranklist结构
	temp = 1;
	for (i = 0; i < k; i++)
		temp += s[i]; //初始化temp:temp=总分满分+1 
	for (i = 0; i < rlist.size(); i++) { //对rlist进行排序
		t = rlist[i];   //第i名的用户ID,这里的ID只有最后的非零数字，没有前面的0000（实际上i从0开始 应该是第i+1名）
		if (ranklist[t]->total < temp) {
			r = i + 1; //r=i+1 代表名次
			temp = ranklist[t]->total;  //更新temp为按排名当前第i名用户的总分
		}
		printf("%d %05d %d", r, t, ranklist[t]->total);
		for (j = 0; j < k; j++) {
			if (ranklist[t]->score[j] == -2)
				printf(" -");   //从没提交过
			else if (ranklist[t]->score[j] == -1)
				printf(" 0");   //提交过但是没过 0分
			else
				printf(" %d", ranklist[t]->score[j]);
		}
		printf("\n");

	}
	system("pause");
	return 0;
}