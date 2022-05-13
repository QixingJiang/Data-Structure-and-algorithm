/*
02-���Խṹ2 һԪ����ʽ�ĳ˷���ӷ�����
*/
#include<iostream>
using namespace std;
//�ڶ��� С��ר��	
typedef struct PolyNode* Polynomial;
struct PolyNode {
	int coef;    //ϵ��   coefficient
	int expon;  //ָ����  exponential
	Polynomial link;
};
//����Attach���� ����
void Attach(int c, int e, Polynomial* pRear)
{
	Polynomial P;

	P = (Polynomial)malloc(sizeof(struct PolyNode));  //������P
	P->coef = c;    //���½�㸳ֵ
	P->expon = e;
	P->link = NULL;
	(*pRear)->link = P;   //���������P�嵽Rear����   *pRear��ָ��Polynomial��ָ�� ����ǰ������ʽβ��ָ��
	*pRear = P;   //�޸�*pRear��ֵ



}

//��ȡ����ʽ
Polynomial ReadPoly()
{
	Polynomial P, Rear, t;
	int c, e, N;
	cin >> N;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;   //P��ָ��һ���ս�� �Ͳ���ȥ�ж϶���ʽ�Ƿ�Ϊ�ղ��÷������
	Rear = P;
	while (N--)    //��N��0  ִ��ѭ��
	{
		cin >> c >> e;       //����һ����c��e�������ʽ����
		Attach(c, e, &Rear);  //��Ϊ��ֵ���� �õ�&  ��Rear��㼴P���ָ��ӽ�����
	}
	t = P;
	P = P->link; //��P��ָ��ս�� ����ָ��ʵ���ϵĵ�һ�� P->link����
	free(t);   //��tɾ��P�����ʱ���ɵ�ͷ���
	return P;
}
//����ʽ�˷�
Polynomial Mult(Polynomial P1, Polynomial P2)
{
	Polynomial P, Rear, t1, t2, t;
	int c, e;
	P = (Polynomial)malloc(sizeof(struct PolyNode));  //������P
	P->link = NULL;
	Rear = P;
	t1 = P1;
	t2 = P2;
	if (!t1 || !t2) return NULL;        //!�����  ||�����

	while (t2)    //�����ʼ��
	{
		Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
		t2 = t2->link;
	}    //��P1�ĵ�һ���P2��������ʽ�ĳ˻���Ϊ��ʼ��
	t1 = t1->link;   //��ʼ��P1��ʣ�����P2�ĳ˻�   ����ѭ����
	while (t1)
	{
		t2 = P2;
		Rear = P;
		while (t2)
		{
			e = t1->expon + t2->expon;
			c = t1->coef * t2->coef;
			//�ж���һ��Rear ����ʼ�����һ���ָ������	��Ҫ�����ָ��e��С��ϵ
			while (Rear->link && Rear->link->expon > e)    //����Ȳ����Ҫ�� ��Rear���� 
			{
				Rear = Rear->link;
			}
			if (Rear->link && Rear->link->expon == e)   //��ȵĻ�ϵ����Ӽ��� 
			{
				if (Rear->link->coef + c)   //������������
					Rear->link->coef += c;
				else {
					t = Rear->link;
					Rear->link = t->link;
					free(t);
				}
			}
			else    //����Ȳ����ҪС �ǲ�����Rear��Rear��һ��֮��  
			{
				t = (Polynomial)malloc(sizeof(struct PolyNode));
				t->coef = c;
				t->expon = e;
				t->link = Rear->link;
				Rear->link = t;
				Rear = Rear->link;   //����Rear
			}
			t2 = t2->link;  //ѭ��++
		}
		t1 = t1->link;
	}
	t = P;
	P = P->link;
	free(t);  //��P�ڵ㱾��ָ��Ŀս��ȥ��
	return P;

}
//����ʽ�ӷ�
Polynomial Add(Polynomial P1, Polynomial P2)
{
	Polynomial P, Rear, t1, t2, t;  // �ṹ����ʽ��ͷ β.
	P = (Polynomial)malloc(sizeof(struct PolyNode));  //����һ���ս��
	P->link = NULL;
	Rear = P; /* ��P ��¼�������ʽ����ͷ��� */
	t2 = P2;
	t1 = P1;

	while (t1 && t2) /* ����������ʽ���з�����(������)������ʱ */
		if (t1->expon > t2->expon)
		{	 // // p1��   ϵ����ָ�ؽӵ�rear�ĺ���
			Attach(t1->coef, t1->expon, &Rear);
			t1 = t1->link;
		}
		else if (t1->expon < t2->expon)
		{
			Attach(t2->coef, t2->expon, &Rear);
			t2 = t2->link;
		}
		else
		{
			//p1 = p2
			if (t1->coef + t2->coef) Attach(t1->coef + t2->coef, t1->expon, &Rear);
			t1 = t1->link;
			t2 = t2->link;
		}
	/* ��δ���������һ������ʽ�����нڵ����θ��Ƶ��������ʽ��ȥ */
	// p1����
	while (t1)
	{
		Attach(t1->coef, t1->expon, &Rear);
		t1 = t1->link;

	}
	// p2 ����
	while (t2)
	{
		Attach(t2->coef, t2->expon, &Rear);
		t2 = t2->link;

	}
	// �ͷ���ʱ���
	t = P;
	P = P->link; /*��frontָ��������ʽ��һ�������� */
	free(t); /* �ͷ���ʱ�ձ�ͷ��� */
	return P;
}
//����ʽ�����ӡ
void PrintPoly(Polynomial P)
{
	int flag = 0;
	if (!P)
	{
		cout << "0 0" << endl;
		return;
	}
	while (P)
	{
		if (!flag)
			flag = 1;
		else
			cout << " ";    //ÿһ��֮��Ҫ�ÿո����
		cout << P->coef << " " << P->expon;
		P = P->link;
	}
	cout << endl;
}
int main()
{
	Polynomial P1, P2, PP, PS;
	P1 = ReadPoly();  //�������ʽ1
	P2 = ReadPoly(); //�������ʽ2
	PP = Mult(P1, P2);
	PrintPoly(PP); //�˷����㲢���
	PS = Add(P1, P2);
	PrintPoly(PS); //�ӷ����㲢���

	system("pause");
	return 0;
}