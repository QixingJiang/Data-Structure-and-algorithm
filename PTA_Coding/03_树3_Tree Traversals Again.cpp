#include<cstdio>
#include<stack>
#include<iostream>
#include<string>
using namespace std;

#define MAX 30
int preOrder[MAX];
int inOrder[MAX];
int postOrder[MAX];

//push���̾���ǰ�������pop���̾����������inorder������Ҫдһ������ǰ��preorder���������inorderȷ���������postorder���㷨��
//����ǰ������򻮷֣���ȷ�����������ǰ��ĵ�һ������Ϊ����㣬
//�ҵ������root����������λ�ã�����������root���Ϊ��������������ұ�Ϊ������
void Solve(int preL, int inL, int postL, int n) {   //preL��ĳ��Ԫ����ǰ�������λ�ã�inL�����������λ�� ͬ���� n��n����  
	if (n == 0)return;   //����0����  ���գ� ����˵ֱ������=0 ѭ������ ���ʱ���൱��������ҽ���Ѿ�û�� ȱ�����лᱨ��
	if (n == 1) {      //����һ����  ǰ��=����
		postOrder[postL] = preOrder[preL];   
	}
	int root = preOrder[preL];   //ǰ��ĵ�һ���Ǹ����
	postOrder[postL + n - 1] = root;   //������ں����������һ��   ���Ĳ��� ����postOrder������������
	int i, R, L;
	for (i = 0; i<n; i++) {
		if (root == inOrder[inL + i])break;  //����������������ϵ���е�λ��inL+i  ��Ҫ��i
	}
	L = i, R = n - i - 1;        //LΪ�����������Ŀ=i��RΪ�����������Ŀ=n-i-1��1�Ǹ���㣩
	//������������ͬ�ķ������еݹ�ֱ��L=R=0
	Solve(preL + 1, inL, postL, L);    //ȷ�����������и����root��ߵ�����˳��  ���Ԫ�ظ���=L ��inL��postL������
	Solve(preL + L + 1, inL + L + 1, postL + L, R);    //ȷ�����������и����root�ұߵ�����˳��      preL+L+1��root�ұߵĵ�һ��Ԫ��λ�� inLҲ��
}

int main() {
	int n;
	for (int i = 0; i<MAX; i++) {
		preOrder[i] = 0;
		inOrder[i] = 0;
		postOrder[i] = 0;
	}
	stack<int> s;
	cin >> n;
	string str;
	int data;
	int index = 0, pos = 0;
	for (int i = 0; i<2 * n; i++) {
		cin >> str;
		if (str == "Push") {      //push����ǰ�����
			cin >> data;
			s.push(data);
			preOrder[index++] = data;
		}
		else if (str == "Pop") { //popΪ�������
			inOrder[pos++] = s.top();
			s.pop();
		}
	}  //��ǰ����������н������ 
	Solve(0, 0, 0, n);  //���ݵĲ�������0ֻ����������ĵ�һλ ��������Ǿ����preOrder ������
	for (int i = 0; i<n; i++) {   //�����postOrder Ҳ����˵���ý��� ֻҪ������
		if (i>0)printf(" ");
		printf("%d", postOrder[i]);
	}
	system("pause");
	return 0;
}