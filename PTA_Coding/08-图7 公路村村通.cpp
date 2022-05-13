// 08-ͼ7 ��·���ͨ   ��С������  Ӧ��Kruskal�㷨

#include<iostream>
using namespace std;
#define MaxVertexNum 1000
#define INFINITY 65535

typedef int Vertex; // �ö����±��ʾ����,Ϊ����
typedef char DataType;
typedef int WeightType; // �ߵ�Ȩֵ��Ϊint

/* ********************* LGraph *******************/
// �ߵĶ�����֮ǰ��ͬ
typedef struct ENode* PtrENode;
struct ENode
{
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrENode Edge;

// �ڽӵ�Ķ��� �߱�
typedef struct AdjVNode* PtrAdjVNode;
struct AdjVNode
{
    Vertex AdjV; // �ڽӵ��±�
    WeightType Weight; // ��Ȩ��
    PtrAdjVNode Next;  // ָ����һ���ڽӵ����ָ��
};

// �����ͷ���Ķ��� �����
struct VNode {
    PtrAdjVNode FirstEdge;  // �߱�ͷָ��
    // DataType Data;   // �涥������,һ�㲻��
};
typedef struct VNode AdjList[MaxVertexNum];

// Graph struct
/* ͼ���Ķ��� */
typedef struct GNode* PtrGNode;
struct GNode
{
    int Nv; //������
    int Ne; // ����
    AdjList G; // �ڽӱ�. ��һ��sizeΪMaxVertexNum������,ÿһ��Ԫ�ض���һ�����VNode
};
typedef PtrGNode LGraph;

// ��ʼ����VertexNum�����㵫û�бߵ�ͼ
LGraph CreateGraph(int VertexNum)
{
    LGraph Graph;
    Vertex v, w;

    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for (v = 0; v < Graph->Nv; v++)
        Graph->G[v].FirstEdge = NULL; // ÿһ������v��FirstEdge���ǿյ�, ��Ŵ�0�� Graph->Nv-1
    return Graph;
}

// ����һ����
void InsertEdge(LGraph Graph, Edge E)  /* �����<V1, V2> */
{
    PtrAdjVNode NewNode;

    /* ΪV2�����µ��ڽӵ� */
    NewNode = (PtrAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    /* ��V2����V1�ı�ͷ, ��ͷ�ϲ��� */
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    /********** ��������ͼ����Ҫ����� <V2, V1> **********/
    /* ΪV1�����µ��ڽӵ� */
    NewNode = (PtrAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;
    /* ��V1����V2�ı�ͷ */
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}


// ��ͼ
LGraph BuildGraph() {
    LGraph Graph;
    Edge E;
    Vertex V, V1, V2;
    int Nv, i;

    cin >> Nv;
    Graph = CreateGraph(Nv);

    cin >> Graph->Ne;
    if (Graph->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode)); // �����߽��
        for (i = 0; i < Graph->Ne; i++)
        {
            /* �����,��ʽΪ ��� �յ� Ȩ�� */
            cin >> V1 >> V2 >> E->Weight;
            E->V1 = V1 - 1;
            E->V2 = V2 - 1;
            InsertEdge(Graph, E);
        }
    }
    /* ������������ݵĻ�����������
    for (V=0; V<Graph->Nv; V++)
        scanf(" %c", &(Graph->Data[V]));
    */
    return Graph;
}

/* ********************* Kruskal ********************* */
typedef Vertex ElementType;  // Ĭ��Ԫ���÷Ǹ�������ʾ
typedef Vertex SetName;  // �ø��ڵ��±���Ϊ��������
typedef ElementType SetType[MaxVertexNum];

// ���鼯
// ��ʼ��ȫΪ-1
void InitializeVSet(SetType S, int N) {
    ElementType X;
    for (X = 0; X < N; X++)
        S[X] = -1;
}

void Union(SetType S, SetName Root1, SetName Root2) {
    if (S[Root1] > S[Root2]) {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
    else {
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
}

SetName Find(SetType S, ElementType X) {
    if (S[X] < 0)  // �ҵ����ϵĸ�
        return X;
    else
        return S[X] = Find(S, S[X]); //�ݹ����
}

bool CheckCycle(SetType VSet, Vertex V1, Vertex V2) {
    Vertex Root1, Root2;
    Root1 = Find(VSet, V1);
    Root2 = Find(VSet, V2);

    if (Root1 == Root2)
        return false;   //���ɻ�·
    else {
        Union(VSet, Root1, Root2);
        return true;
    }

}


// �ߵ���С��
// ��N��Ԫ�صı������� ESet[p]Ϊ�����Ӷѵ���Ϊ����Weight����С��
void PercDown(Edge ESet, int p, int N) {
    // ֱ��������,���ö�heap�ṹ��
    int Parent, Child;
    struct ENode X;

    X = ESet[p];
    for (Parent = p; (Parent * 2 + 1) < N; Parent = Child) {
        Child = Parent * 2 + 1;
        if ((Child != N - 1) && (ESet[Child].Weight > ESet[Child + 1].Weight))
            Child++;
        if (X.Weight <= ESet[Child].Weight)
            break;
        else  /* ����X */
            ESet[Parent] = ESet[Child];
    }
    ESet[Parent] = X;
}

/* ��ͼ�ıߴ�������ESet�����ҳ�ʼ��Ϊ��С�� */
void InitializeESet(LGraph Graph, Edge ESet) {
    Vertex V;
    PtrAdjVNode W;
    int ECount = 0;

    /* ��ͼ�ıߴ�������ESet */
    for (V = 0; V < Graph->Nv; V++) {
        for (W = Graph->G[V].FirstEdge; W; W = W->Next) {
            if (V < W->AdjV) {  /* �����ظ�¼������ͼ�ıߣ�ֻ��V1<V2�ı� */
                ESet[ECount].V1 = V;
                ESet[ECount].V2 = W->AdjV;
                ESet[ECount].Weight = W->Weight;
                ECount++;
            }

        }
    }
    /* ����Ϊ��С�� �����һ�����ĸ��ڵ�(Size/2)��ʼ,�����ڵ�(1)Ϊֹ*/
    for (ECount = Graph->Ne / 2; ECount >= 0; ECount--)
        PercDown(ESet, ECount, Graph->Ne);
}

void Swap(struct ENode* a, struct ENode* b) {
    struct ENode c;
    c = *a;
    *a = *b;
    *b = c;
}

/* ������ǰ�ѵĴ�СCurrentSize������ǰ��С��λ�õ����������� */
int GetEdge(Edge ESet, int CurrentSize) {
    Swap(&ESet[0], &ESet[CurrentSize - 1]);  /* ����С���뵱ǰ�ѵ����һ��λ�õı߽��� */
    PercDown(ESet, 0, CurrentSize - 1);  /* ��ʣ�µı߼�����������С��  */

    return CurrentSize - 1; /* ������С������λ�� */
}


int Kruskal(LGraph Graph, LGraph MST) {
    WeightType TotalWeight;
    int ECount, NextEdeg;
    SetType VSet;  // ��������
    Edge ESet;  // ������

    InitializeVSet(VSet, Graph->Nv);  // ��ʼ�����㲢�鼯
    ESet = (Edge)malloc(sizeof(struct ENode) * Graph->Ne);  // ���������ռ�
    InitializeESet(Graph, ESet);  // ��ʼ���ߵ���С��

    // ����MSTͼ
    MST = CreateGraph(Graph->Nv);
    TotalWeight = 0;
    ECount = 0;

    NextEdeg = Graph->Ne;  // ԭʼ�߼��ϵĹ�ģ
    while (ECount < Graph->Nv - 1) {  // ���ռ��ı�С�ڶ�����-1ʱ
        NextEdeg = GetEdge(ESet, NextEdeg);
        if (NextEdeg < 0) // �߼��Ѿ���
            break;
        if (CheckCycle(VSet, ESet[NextEdeg].V1, ESet[NextEdeg].V2))  // ��������ɻ�·
        {
            // ����ߵ�MST��
            InsertEdge(MST, ESet + NextEdeg);  // �൱�� &ESet[NextEdge]
            TotalWeight += ESet[NextEdeg].Weight;
            ECount++;
        }
    }// whileѭ������
    if (ECount < Graph->Nv - 1)
        TotalWeight = -1; //  �����Ա�֤ ͨ��  ���ô����־

    return TotalWeight;
}


/* ********************������************************ */
int main()
{
    LGraph Graph, MST;
    int TotalWeight;
    Graph = BuildGraph();
    TotalWeight = Kruskal(Graph, MST);
    cout << TotalWeight << endl;
    return 0;
}




























