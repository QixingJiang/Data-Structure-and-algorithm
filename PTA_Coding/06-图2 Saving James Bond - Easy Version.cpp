// 06-ͼ2 Saving James Bond - Easy Version
#include<iostream>
#include<math.h>
#define MAX 101

using namespace std;
struct crocodile   //crocodile�������˼
{
    int hori;
    int vert;  //hori��vert�ֱ��Ǻ������������
    bool shore;
    bool jump;
    bool visited;
};
typedef struct crocodile croco[MAX];
croco c;  // ȫ�ֱ�������c,ÿһ���struct crocodile
int answer = 0; // ȫ�ֱ���

int Distance(int x1, int y1, int x2, int y2) {
    int distance = (int)sqrt(pow((y2 - y1), 2) + pow((x2 - x1), 2));
    return distance;
}
//�ж��ܷ񵽰���
bool NearShore(int x, int y, int D) {
    if ((50 - abs(x)) <= D || (50 - abs(y)) <= D)
        return true;
    else
        return false;
}

bool FirstJump(int x, int y, int D) {
    int dist = (int)sqrt(pow(x, 2) + pow(y, 2));
    if (dist <= D + 15 / 2)
        return true;
    else
        return false;
}

// ��ʼ�� N������
void Initial(int N, int D) {
    int x, y;
    for (int i = 0; i < N; i++) {
        cin >> x;
        cin >> y;
        c[i].hori = x;
        c[i].vert = y;
        c[i].shore = NearShore(x, y, D);
        c[i].jump = FirstJump(x, y, D);
        c[i].visited = false;
    }
}

// DFS����
int DFS(struct crocodile* v, int N, int D) {
    int dist;
    v->visited = true;
    if (v->shore)   //��ֱ�ӵ����߾�ֱ��answer=1
        answer = 1;
    for (int i = 0; i < N; i++) 
    {
        dist = Distance(v->hori, v->vert, c[i].hori, c[i].vert);
        if (dist <= D && (c[i].visited == false))   //���������Ծc[i] ����c[i]��û���Թ�
            answer=DFS(&c[i], N, D);   //ͨ��������DFS 
        if (answer==1) break;
    }
    return answer;                                  

}



int main()
{
    int N, D, i;   //NΪ�������� DΪ��Ծ����
    cin >> N;
    cin >> D;
    Initial(N, D);
    bool result = false;

    for (i = 0; i < N; i++) {
        if (c[i].jump) {// �ҵ�һ��������  
            result = DFS(&c[i], N, D);
            if (result) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;


    return 0;
}