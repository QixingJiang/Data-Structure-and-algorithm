#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*�˺���������󳤶ȵĶ���
���ǵ���󳤶���Ҫ����Ŀ�����Ĵ�һλ
������Ϊ����Ҫһ��λ��������'\0'���ж��ַ����Ľ�β*/
#define Max_Password_Len 17
#define Max_Account_Len 11
#define MaxTableSize 1000000

/*����״̬�Ķ���
�����������ʾ�ɹ���״̬
�ø�����0��ʾʧ�ܵ�״̬
��������ǿ��֢�������һ��*/
#define ERROR_WrongPW   -2
#define ERROR_Exist     -1
#define ERROR_NOT_Exist  0
#define New_OK          1
#define Login_OK        2


/******************************�����ϣ��***********************************/
typedef char AccountType[Max_Account_Len];//�˺����Ͷ���
typedef char PasswordType[Max_Password_Len];//�������Ͷ���
typedef int Index;
typedef enum Pattern { New, Log } ;//����ģʽ���½��˺�������˺�

typedef struct
{
	AccountType Account;
	PasswordType Password;
}ElemType;//�������͵Ķ��壬ÿ����Ӧһ���û����ں��û����˺ź�����

//����ָ��Ķ���
typedef struct LNode* PtrToLNode;
//������Ķ���
struct LNode
{
	PtrToLNode Next;
	ElemType Data;
};
typedef PtrToLNode List;//����Ķ���
typedef PtrToLNode Position;//��ϣ���н��λ�õĶ���

//��ϣ��Ķ���
typedef struct TblNode* HashTable;
struct TblNode
{
	int TableSize;//��ϣ��Ĵ�С    
	List Heads;//��������б�ͷ�ڵ������
};

/*****************���ֺ���***************************/
int NextPrime(int N)//����N����һ������
{
	int i, P;
	P = N % 2 ? N + 2 : N + 1;
	//PΪN֮��ĵ�һ������    
	while (P < MaxTableSize)
	{
		for (i = (int)sqrt(P); i > 2; i--)//��Ϊֻ��������������iΪ2ʱ�ͽ�����            
			if (P % i == 0)
				break;
		if (i == 2)
			break;//iΪ2˵��PΪ����        
		else
			P += 2;//i!=2˵��P������������Pָ����һ������    
	}
	return P;
}

int Hash(int Key, int TableSize)
{//����Keyֵ���Ӧ�Ĺ�ϣֵ�������ڹ�ϣ���еĴ����±�
	return Key % TableSize;
}

HashTable CreateTable(int TableSize)
{    //����յĹ�ϣ��
	HashTable H;
	int i;
	H = (HashTable)malloc(sizeof(TblNode));
	H->TableSize = NextPrime(TableSize);
	H->Heads = (List)malloc(sizeof(LNode) * H->TableSize);
	for (i = 0; i < H->TableSize; i++)
	{
		H->Heads[i].Data.Account[0] = '\0';
		H->Heads[i].Data.Password[0] = '\0';
		H->Heads[i].Next = NULL;
	}
	return H;
}

Position Find(HashTable H, ElemType Key)
{
	Position Pos;
	Index p;
	if (strlen(Key.Account) > 5) //�˺Ŵ���5λʱȡ���5λ       
		p = Hash(atoi(Key.Account + strlen(Key.Account) - 5), H->TableSize);
	else//�˺Ų�����5λ�����������      
		p = Hash(atoi(Key.Account), H->TableSize);
	Pos = H->Heads[p].Next;
	while (Pos && strcmp(Key.Account, Pos->Data.Account))
		Pos = Pos->Next;
	return Pos;//Posָ���û����ݵ�λ�ã�û��ע��ͷ���NULL
}
/*********************�ж�����ĺ���******************************/
int NewOrLog(HashTable H, ElemType Key, Pattern P)
{    //����״̬����
	Position Pos, NewPos;
	Index p;
	Pos = Find(H, Key);
	switch (P)
	{
	case Log:
		if (Pos == NULL)
			return ERROR_NOT_Exist;//��½ʱ�������˺�          
		else if (strcmp(Pos->Data.Password, Key.Password) ||(strlen(Key.Password) > 16 || strlen(Key.Password) < 6)) //���������˲�һ�����п����ǳ��ȵĲ�ͬ
			return ERROR_WrongPW; //���������ʽ����          
		else
			return Login_OK;//�˺ź��������ȷ�����Ե�¼        

	case New:
		if (Pos != NULL)
			return ERROR_Exist; //�½��˺�ʱ�����Ѿ������������˺���           
		else
		{
			NewPos = (Position)malloc(sizeof(LNode));
			strcpy(NewPos->Data.Account, Key.Account);
			strcpy(NewPos->Data.Password, Key.Password);
			if (strlen(Key.Account) > 5)
				p = Hash(atoi(Key.Account +strlen(Key.Account) - 5), H->TableSize);
			else
				p = Hash(atoi(Key.Account), H->TableSize);
			NewPos->Next = H->Heads[p].Next;
			H->Heads[p].Next = NewPos;
			return New_OK; //������ֵ�����ز���ɹ�           
		}
	}
}

void DestroyTable(HashTable H)
{    //���ٹ�ϣ��
	PtrToLNode p, q;
	int i;
	for (i = 0; i < H->TableSize; i++)
	{
		q = H->Heads[i].Next;
		while (q)
		{
			p = q->Next;
			free(q);
			q = p;
		}
	}
	free(H);
}


/*************************main����********************************/
int main(void)
{
	int N, i;
	ElemType Key;
	char Input;
	Pattern P;
	HashTable H;
	scanf("%d", &N);
	H = CreateTable(2 * N);
	for (i = 0; i < N; i++)
	{
		scanf("\n%c %s %s", &Input, Key.Account, Key.Password);
		P = (Input == 'L') ? Log : New;
		switch (NewOrLog(H, Key, P))
		{//�����ݲ�ͬ����ֵ�����Ӧ״̬����            
		case ERROR_Exist:
			printf("ERROR: Exist\n");
			break;
		case ERROR_NOT_Exist:
			printf("ERROR: Not Exist\n");
			break;
		case ERROR_WrongPW:
			printf("ERROR: Wrong PW\n");
			break;
		case Login_OK:
			printf("Login: OK\n");
			break;
		case New_OK:
			printf("New: OK\n");
			break;
		}
	}
	DestroyTable(H);
	return 0;
}