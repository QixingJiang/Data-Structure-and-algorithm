/*
10-����5 PAT Judge
��һ�������������� �������û�����  �������� �ύ�ܴ���
Ȼ��ڶ������� ÿ����������֣���߷�����
Ȼ�����濪ʼ��������ÿ���ύ����Ϣ���û�ID  ��Ӧ�������  �õ��ķ���  ��-1�������ʧ�ܣ�
����Ľ���ǴӸߵ������ÿ���û�����Ϣ�������ܷ�����  ������ݣ��û�ID �ܷ� ÿ������ĵ÷� 
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
//���������ص㶨��һ���ṹ �������ÿ���û����ܷ�
struct UserNode {
	int total;
	int perfect;  //����ܷ�һ�� Ҫ�������ύ����Ĵ���������
	int* score; //scoreָ������ָ��һ����Ÿ�������ɼ�������
};
UserNode* ranklist[10001];  //�û�����<10^4

//��������Ĺ���  
//true��ʾλ����ȷ��������н���
//false��ʾλ�ô��󣬽���λ�õĽ���
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
/*******************************main����*************************************/
int main() {
	int i, j, t, n, k, m, id, problem, score, flag, r, temp, s[5];  // n:�û����� k:�������� m���ύ����   r������
	vector<int> rlist;  //rlist:���水��������¼��ÿ���û� �����������͵�������

	cin >> n >> k >> m;   
	for (i = 0; i < k; i++)
		cin >> s[i];   //����ÿ��������ܷ�(����)
	for (i = 1; i <= n; i++)
		ranklist[i] = NULL; //�ȳ�ʼ��ÿ���˵�����


	/*********************����ÿ���ύ����Ϣ*******************************/
	while (m--) {    //��m������0 ִ�к��  ʵ��ÿ���ύ��ĸ���
		cin >> id >> problem >> score;
		if (!ranklist[id]) {  //�������û���һ������ �Ǿ��ǿ�  ���ȳ�ʼ�� 
			ranklist[id] = new UserNode;
			ranklist[id]->score = new int[k];   //new int[] �Ǵ���һ��int�����飬�����С����[]��ָ�� ��ʵ�ִ������ÿ������ɼ�������scroe[k]
			for (j = 0; j < k; j++)
				ranklist[id]->score[j] = -2;
			ranklist[id]->total = 0;
			ranklist[id]->perfect = 0;
		}
		//�������û����ǵ�һ�����루�Ѿ��ύ�������ˣ�
		// score����ǰ�����ύ������Ӧ�ĳɼ�    ranklist[id]->score[problem - 1] һ��ʼ��ʼ��Ϊ-2  ���θ���Ϊ�ύ�����ֵ	 
		if (ranklist[id]->score[problem - 1] < score)   //problem������Ǵ�1��ʼ  1-N ���Զ�Ӧscore����Ԫ����problem-1
			ranklist[id]->score[problem - 1] = score;
	}
	for (i = 1; i <= n; i++) {
		if (ranklist[i]) {   //ranklist[i]��Ϊ�� ����������û�����
			flag = 0; //flag���ж�����û������������û�б���ɹ���
			for (j = 0; j < k; j++) {
				if (ranklist[i]->score[j] >= 0) {
					flag = 1;
					ranklist[i]->total += ranklist[i]->score[j];  //���һ�������ύ�ɹ����ɼ�����-1��  �ͼӵ��ܷ���
				}
				if (ranklist[i]->score[j] == s[j])
					ranklist[i]->perfect++;  //˳��ͳ���¸��û������ύ����
			}
			if (flag) rlist.push_back(i);   //push_back:��vector��������Ϊ��vectorβ������һ������  ��������û�id
		} 
	}

	sort(rlist.begin(), rlist.end(), cmp); //rlist���Ԫ�ؽ��д�С�������� ÿ��Ԫ�ض���һ��ranklist�ṹ
	temp = 1;
	for (i = 0; i < k; i++)
		temp += s[i]; //��ʼ��temp:temp=�ܷ�����+1 
	for (i = 0; i < rlist.size(); i++) { //��rlist��������
		t = rlist[i];   //��i�����û�ID,�����IDֻ�����ķ������֣�û��ǰ���0000��ʵ����i��0��ʼ Ӧ���ǵ�i+1����
		if (ranklist[t]->total < temp) {
			r = i + 1; //r=i+1 ��������
			temp = ranklist[t]->total;  //����tempΪ��������ǰ��i���û����ܷ�
		}
		printf("%d %05d %d", r, t, ranklist[t]->total);
		for (j = 0; j < k; j++) {
			if (ranklist[t]->score[j] == -2)
				printf(" -");   //��û�ύ��
			else if (ranklist[t]->score[j] == -1)
				printf(" 0");   //�ύ������û�� 0��
			else
				printf(" %d", ranklist[t]->score[j]);
		}
		printf("\n");

	}
	system("pause");
	return 0;
}