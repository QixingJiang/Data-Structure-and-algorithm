#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#define MaxVertex 10005
typedef int vertex;
typedef struct Node* AdjList;
struct Node {
	vertex Adjv;  // ��ǰ�±� 
	AdjList Next;  // ��һ�� 
};
AdjList G[MaxVertex];
bool visit[MaxVertex];  // �Ƿ���� 
int N;  // �����
int M;  // ���� 
using namespace std;

// ��ʼ������״̬ 
void InitVisit() {
	for (int i = 1; i <= N; i++)
		visit[i] = false;
}

// ��ʼ�� 
void Init() {
	vertex v1, v2;
	AdjList NewNode;
	cin >> N >> M;
	// ��ʼ���㣬�� 1��N   ����N����
	for (int i = 1; i <= N; i++) {
		G[i] = (AdjList)malloc(sizeof(struct Node));
		G[i]->Adjv = i;
		G[i]->Next = NULL;
	}
	// ��ʼ���� 
	for (int i = 0; i < M; i++) {   //�������Ϊ��ʵ�ְ�v2����v1->Next
		cin >> v1 >> v2;   //v1�ǵ�ǰ���  v2��v1ָ�����һ�����
		NewNode = (AdjList)malloc(sizeof(struct Node));
		NewNode->Adjv = v2;          
		NewNode->Next = G[v1]->Next; //ָ����һ�� ���ʱ��NewNode��Next=NULL
		G[v1]->Next = NewNode;       //��NewNode��Next��Adjvȫ������G[v1]->Next ��NewNode����v2 �൱�ڰ�v2����v1->Next

		NewNode = (AdjList)malloc(sizeof(struct Node));
		NewNode->Adjv = v1;
		NewNode->Next = G[v2]->Next;
		G[v2]->Next = NewNode;  //v1����v2��->next ��Ϊ������ͼ ˫�����ӡ�
	}
}

int BFS(vertex v) {   //v=i
	queue<vertex> q;
	vertex tmp;
	int level = 0;
	int last = v;  // �ò����һ�η��ʵĽ�� 
	int tail = v;  // ÿ���ڱ�Ľ�� 
	AdjList node;
	visit[v] = true;
	int count = 1;  // ͳ�ƹ�ϵ�� 
	q.push(v); //push�ǲ���q���� queue���Ƚ��ȳ�
	while (!q.empty()) {  //��q����
		tmp = q.front(); //queue�ĵ�һ��Ԫ��   tmp=i
		q.pop(); //������
		// G[i]��һ�������Լ����±�    G[tmp]=G[i]
		node = G[tmp]->Next;
		while (node) {
			if (!visit[node->Adjv]) {  //node->Adjvû���ʹ�
				visit[node->Adjv] = true;
				q.push(node->Adjv);
				count++;
				tail = node->Adjv; // ÿ�θ��¸ý�� 
			}
			node = node->Next;
		}
		// ����õ�ǰ�����������һ����� 
		if (tmp == last) {
			level++;    // ���� +1  
			last = tail;   // ���� last 
		}
		// �������˽��� 
		if (level == 6)
			break;
	}
	return count;
}


void output(double result, int i) {
	printf("%d: %.2f%%\n", i, result);
}

void SDS() {  //SDS:���ȷָ���д
	int count;
	for (int i = 1; i <= N; i++) {
		// ÿ�γ�ʼ���������� 
		InitVisit();
		count = BFS(i);
		output((100.0 * count) / N, i);
	}
}


int main() {
	Init();
	SDS();
	system("pause");
	return 0;
}