/*
ʹ�÷������ӷ�
*/
#include<iostream>
using namespace std;
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
/**************************Hash����ģ��***************************************/
#define KEYLENGTH 11 //�ؼ����ַ�������󳤶�  define�����ӷֺš���������  
typedef char ElementType[KEYLENGTH + 1];  //�ؼ����������ַ���   +1����ΪC�����ַ�����βռ��һ��λ��
typedef int Index;   //ɢ�е�ַ���� 
#define MAXD 5
typedef struct LNode* PtrToLNode;  //����Ķ���
struct LNode {
    ElementType Data;
    PtrToLNode Next;
    int Count;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;


typedef struct TblNode* HashTable;
struct TblNode {    //ɢ�б��㶨��
    int TableSize;
    List Heads;  //ָ������ͷ��������

};


/***************************NextPrimeģ��********************************/
#define MAXTABLESIZE 1000000
int NextPrime(int N)
{   //���ش���N�Ҳ�����MAXTABLESIZE����С����
    int i, p = (N % 2) ? N + 2 : N + 1;//��Ԫ����� �Ӵ���N����һ��������ʼ
    while (p < MAXTABLESIZE) {
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p % i)) break; //p��������
        if (i == 2) break;
        else p += 2;
    }
    return p;
}

/**********************************������CreateTable*******************************************************/
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

/*****************************Hash����***********************************/
int Hash(ElementType Key, int P)
{//������������ɢ�к���
    return atoi(Key + KEYLENGTH - MAXD) % P;
}
/*************************************Find********************************/

Position Find(HashTable H, ElementType Key)
{
    Position P;
    Index Pos;

    Pos = Hash(Key, H->TableSize);  //��ʼ��ɢ��λ��  ����KEY����ֱ�Ӵ���ȥ��ΪҪ������Ǻ���λ���� ��Ҫ���д���

    P = H->Heads[Pos].Next;//�Ӹ�����ĵ�һ����㿪ʼ

    while (P && strcmp(P->Data, Key))
        P = P->Next;

    return P;

}

/************************************����Insetr����*************************************/
bool Insert(HashTable H, ElementType Key)
{
    Position P, NewCell;
    Index Pos;
    P = Find(H, Key);
    if (!P) {   //�ؼ���δ�ҵ������Բ���
        NewCell = (Position)malloc(sizeof(struct LNode));
        strcpy(NewCell->Data, Key);
        NewCell->Count = 1;
        Pos = Hash(Key, H->TableSize);

        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return true;
    }
    else {  //�ؼ����Ѵ���
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
    for (i = 0; i < H->TableSize; i++)  //ɨ������
    {
        Ptr = H->Heads[i].Next;
        while (Ptr)
        {
            if (Ptr->Count > MaxCnt)     //�������ͯ��cishu
            {
                MaxCnt = Ptr->Count;
                strcpy(MinPhone, Ptr->Data); // rcpy:string copy  ��A�ַ������Ƹ�B
                    PCnt = 1;
            }
            else if (Ptr->Count == MaxCnt)   //���ҵ�һ�������ͨ��������
            {
                PCnt++;
                if (strcmp(MinPhone, Ptr->Data) > 0) // rcmp:string compare  �Ƚ��ַ�
                    strcpy(MinPhone, Ptr->Data);   //���¿��˵���С�ֻ���
            }
            Ptr = Ptr->Next; //�������������� ��ֱ��ɨ����һ��
        }
    }
    cout << MinPhone << " " << MaxCnt;
    if (PCnt > 1) 
        cout <<" "<<PCnt << endl; //�����Ψһ �������������
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
    //����ɢ�б�
    HashTable H;
    ElementType Key;
    cin >> N;
    H = CreateTable(N * 2);
    //�������������
    for (i = 0; i < N; i++)
    {
        cin >> Key; Insert(H, Key);   //ÿ��ͨ����¼����������
        cin >> Key; Insert(H, Key);
    }
    //ɨ����������
    ScanAndOutput(H);
    //������ͷſռ�
    DestroyTable(H);
    system("pause");
    return 0;




}
