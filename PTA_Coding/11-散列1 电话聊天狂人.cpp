/*
使用分离链接法
*/
#include<iostream>
using namespace std;
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
/**************************Hash表定义模块***************************************/
#define KEYLENGTH 11 //关键词字符串的最大长度  define后面别加分号。。。。。  
typedef char ElementType[KEYLENGTH + 1];  //关键词类型用字符串   +1是因为C语言字符串结尾占了一个位置
typedef int Index;   //散列地址类型 
#define MAXD 5
typedef struct LNode* PtrToLNode;  //链表的定义
struct LNode {
    ElementType Data;
    PtrToLNode Next;
    int Count;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;


typedef struct TblNode* HashTable;
struct TblNode {    //散列表结点定义
    int TableSize;
    List Heads;  //指向链表头结点的数组

};


/***************************NextPrime模块********************************/
#define MAXTABLESIZE 1000000
int NextPrime(int N)
{   //返回大于N且不超过MAXTABLESIZE的最小素数
    int i, p = (N % 2) ? N + 2 : N + 1;//三元运算符 从大于N的下一个奇数开始
    while (p < MAXTABLESIZE) {
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p % i)) break; //p不是素数
        if (i == 2) break;
        else p += 2;
    }
    return p;
}

/**********************************建立表CreateTable*******************************************************/
HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = NextPrime(TableSize);
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));
    for (i = 0; i < H->TableSize; i++) {
        H->Heads[i].Data[0] = '\0';
        H->Heads[i].Next = NULL;
        H->Heads[i].Count = 0;
    }
    return H;
}

/*****************************Hash函数***********************************/
int Hash(ElementType Key, int P)
{//除留余数法的散列函数
    return atoi(Key + KEYLENGTH - MAXD) % P;
}
/*************************************Find********************************/

Position Find(HashTable H, ElementType Key)
{
    Position P;
    Index Pos;

    Pos = Hash(Key, H->TableSize);  //初始化散列位置  其中KEY不能直接传进去因为要传入的是后五位数字 需要进行处理

    P = H->Heads[Pos].Next;//从该链表的第一个结点开始

    while (P && strcmp(P->Data, Key))
        P = P->Next;

    return P;

}

/************************************插入Insetr函数*************************************/
bool Insert(HashTable H, ElementType Key)
{
    Position P, NewCell;
    Index Pos;
    P = Find(H, Key);
    if (!P) {   //关键词未找到，可以插入
        NewCell = (Position)malloc(sizeof(struct LNode));
        strcpy(NewCell->Data, Key);
        NewCell->Count = 1;
        Pos = Hash(Key, H->TableSize);

        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return true;
    }
    else {  //关键词已存在
        P->Count++;
        return false;
    }
}
void ScanAndOutput(HashTable H)
{
    int i, PCnt;
    int MaxCnt = 0;
    ElementType MinPhone;
    MinPhone[0] = '\0';
    List Ptr;
    for (i = 0; i < H->TableSize; i++)  //扫描链表
    {
        Ptr = H->Heads[i].Next;
        while (Ptr)
        {
            if (Ptr->Count > MaxCnt)     //更新最大童话cishu
            {
                MaxCnt = Ptr->Count;
                strcpy(MinPhone, Ptr->Data); // rcpy:string copy  把A字符串复制给B
                    PCnt = 1;
            }
            else if (Ptr->Count == MaxCnt)   //又找到一个有最大通话次数的
            {
                PCnt++;
                if (strcmp(MinPhone, Ptr->Data) > 0) // rcmp:string compare  比较字符
                    strcpy(MinPhone, Ptr->Data);   //更新狂人的最小手机号
            }
            Ptr = Ptr->Next; //如果不是上面情况 就直接扫描下一个
        }
    }
    cout << MinPhone << " " << MaxCnt;
    if (PCnt > 1) 
        cout <<" "<<PCnt << endl; //如果不唯一 输出这样的人数
    else 
        cout << endl;
}



void DestroyTable(HashTable H) {
    int i;
    Position p, tmp;

    for (i = 0; i < H->TableSize; i++) {
        p = H->Heads[i].Next;
        while (p) {
            tmp = p->Next;
            free(p);
            p = tmp;
        }
    }
    free(H->Heads);
    free(H);
}

int main()
{
    int N, i;
    //创建散列表
    HashTable H;
    ElementType Key;
    cin >> N;
    H = CreateTable(N * 2);
    //读入号码插入表中
    for (i = 0; i < N; i++)
    {
        cin >> Key; Insert(H, Key);   //每条通话记录有两个号码
        cin >> Key; Insert(H, Key);
    }
    //扫描表输出狂人
    ScanAndOutput(H);
    //输出后释放空间
    DestroyTable(H);
    system("pause");
    return 0;




}
