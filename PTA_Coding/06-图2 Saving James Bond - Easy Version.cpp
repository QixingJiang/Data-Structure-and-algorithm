// 06-图2 Saving James Bond - Easy Version
#include<iostream>
#include<math.h>
#define MAX 101

using namespace std;
struct crocodile   //crocodile鳄鱼的意思
{
    int hori;
    int vert;  //hori和vert分别是横坐标和纵坐标
    bool shore;
    bool jump;
    bool visited;
};
typedef struct crocodile croco[MAX];
croco c;  // 全局变量数组c,每一项都是struct crocodile
int answer = 0; // 全局变量

int Distance(int x1, int y1, int x2, int y2) {
    int distance = (int)sqrt(pow((y2 - y1), 2) + pow((x2 - x1), 2));
    return distance;
}
//判断能否到岸边
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

// 初始化 N个鳄鱼
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

// DFS遍历
int DFS(struct crocodile* v, int N, int D) {
    int dist;
    v->visited = true;
    if (v->shore)   //能直接到岸边就直接answer=1
        answer = 1;
    for (int i = 0; i < N; i++) 
    {
        dist = Distance(v->hori, v->vert, c[i].hori, c[i].vert);
        if (dist <= D && (c[i].visited == false))   //如果可以跳跃c[i] 而且c[i]还没尝试过
            answer=DFS(&c[i], N, D);   //通过迭代来DFS 
        if (answer==1) break;
    }
    return answer;                                  

}



int main()
{
    int N, D, i;   //N为鳄鱼数量 D为跳跃距离
    cin >> N;
    cin >> D;
    Initial(N, D);
    bool result = false;

    for (i = 0; i < N; i++) {
        if (c[i].jump) {// 找第一跳的鳄鱼  
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