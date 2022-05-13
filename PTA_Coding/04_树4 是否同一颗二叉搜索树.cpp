#include<iostream>
#include<string>
using namespace std;
typedef struct TreeNode* Tree;
struct TreeNode {
	int v;
	Tree Left;
	Tree Right;
	int flag;
};
Tree MakeTree(int N);
Tree NewNode(int V);
Tree Insert(Tree T, int V);
int check(Tree T, int V);
int Judge(Tree T, int N);
void  ResetT(Tree T);
void FreeTree(Tree T);

int main() {
    int N, L, i;
    Tree T;

    cin >> N;        //输入第一个N
    while (N) {
        cin >> L;
        T = MakeTree(N);
        for (i = 0; i < L; i++) {
            if (Judge(T, N))
                cout << "Yes" << endl;
            else
                cout << "No " << endl;
            ResetT(T);  // 清除T中的flag
        }
        FreeTree(T);
        cin >> N;    //输入第二个N 直到N为空 退出循环
    } // while循环结束
    return 0;
}

Tree MakeTree(int N)
{
    Tree T;
    int i, V;
    cin >> V;
    T = NewNode(V);
    for (i = 1; i < N; i++) //i从1开始,因为第一个数已经读好了
    {
        cin >> V;
        T = Insert(T, V);
    }
    return T;
}


// 创建新结点,返回结构指针
Tree NewNode(int V) {
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    T->v = V;
    T->Left = T->Right = NULL;
    T->flag = 0;
    return T;
}


// 递归加入新的结点
Tree Insert(Tree T, int V) {
    if (!T)
        T = NewNode(V);
    else {
        if (V > T->v)
            T->Right = Insert(T->Right, V);
        else
            T->Left = Insert(T->Left, V);
    }
    return T;
}


/*在树T中按顺序搜索序列3 2 4 1中的每个数
如果每次搜索所经过的结点在前面均出现过，则一致
否则(某次搜索中遇到前面未出现的结点)，则不一致*/
int check(Tree T, int V) {
    if (T->flag)
    {//flag不等于0的情况
        if (V < T->v)
            return check(T->Left, V);
        else if (V > T->v)
            return check(T->Right, V);
        else
            return 0;
    }
    else
    {// T->flag = 0 的情况
        if (V == T->v)
        {
            T->flag = 1;
            return 1;
        }
        else
            return 0;
    }
}


int Judge(Tree T, int N) {
    int V, Tflag = 1;

    cin >> V;
    // 先和根结点比
    if (T->v != V)
        Tflag = 0;  // 这里不要直接return 0,不然之后的数就不读了
    else
        T->flag = 1;

    // 依次比较接下来N-1个数
    for (int i = 1; i < N; i++) {
        cin >> V;
        if ((Tflag) && (check(T, V)))
            Tflag = 1;
        else Tflag = 0;
    }
    return Tflag;
}

// 重置flag, 清除T中各结点的flag
void  ResetT(Tree T) {
    if (T->Left)
        ResetT(T->Left);
    if (T->Right)
        ResetT(T->Right);
    T->flag = 0;
}

void FreeTree(Tree T) {
    if (T->Left)
        FreeTree(T->Left);
    if (T->Right)
        FreeTree(T->Right);
    free(T);
}