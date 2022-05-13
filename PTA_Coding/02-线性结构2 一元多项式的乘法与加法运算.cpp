/*
02-线性结构2 一元多项式的乘法与加法运算
*/
#include<iostream>
using namespace std;
//第二章 小白专场	
typedef struct PolyNode* Polynomial;
struct PolyNode {
	int coef;    //系数   coefficient
	int expon;  //指数项  exponential
	Polynomial link;
};
//定义Attach函数 连接
void Attach(int c, int e, Polynomial* pRear)
{
	Polynomial P;

	P = (Polynomial)malloc(sizeof(struct PolyNode));  //申请结点P
	P->coef = c;    //对新结点赋值
	P->expon = e;
	P->link = NULL;
	(*pRear)->link = P;   //把新申请的P插到Rear后面   *pRear是指针Polynomial的指针 代表当前结果表达式尾部指针
	*pRear = P;   //修改*pRear的值



}

//读取多项式
Polynomial ReadPoly()
{
	Polynomial P, Rear, t;
	int c, e, N;
	cin >> N;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;   //P先指向一个空结点 就不用去判断多项式是否为空不用分情况了
	Rear = P;
	while (N--)    //当N≠0  执行循环
	{
		cin >> c >> e;       //读进一个个c和e代表多项式项数
		Attach(c, e, &Rear);  //因为是值传递 用的&  让Rear结点即P结点指向加进来的
	}
	t = P;
	P = P->link; //让P不指向空结点 而是指向实际上的第一项 P->link这项
	free(t);   //用t删除P这个临时生成的头结点
	return P;
}
//多项式乘法
Polynomial Mult(Polynomial P1, Polynomial P2)
{
	Polynomial P, Rear, t1, t2, t;
	int c, e;
	P = (Polynomial)malloc(sizeof(struct PolyNode));  //申请结点P
	P->link = NULL;
	Rear = P;
	t1 = P1;
	t2 = P2;
	if (!t1 || !t2) return NULL;        //!代表非  ||代表或

	while (t2)    //求个初始项
	{
		Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
		t2 = t2->link;
	}    //求P1的第一项和P2整个多项式的乘积作为初始项
	t1 = t1->link;   //开始求P1的剩下项和P2的乘积   不在循环里
	while (t1)
	{
		t2 = P2;
		Rear = P;
		while (t2)
		{
			e = t1->expon + t2->expon;
			c = t1->coef * t2->coef;
			//判断上一步Rear （初始项）的下一项的指数次数	跟要插入的指数e大小关系
			while (Rear->link && Rear->link->expon > e)    //如果比插入的要大 那Rear后移 
			{
				Rear = Rear->link;
			}
			if (Rear->link && Rear->link->expon == e)   //相等的话系数相加即可 
			{
				if (Rear->link->coef + c)   //不会正负抵消
					Rear->link->coef += c;
				else {
					t = Rear->link;
					Rear->link = t->link;
					free(t);
				}
			}
			else    //如果比插入的要小 那插入在Rear和Rear下一项之间  
			{
				t = (Polynomial)malloc(sizeof(struct PolyNode));
				t->coef = c;
				t->expon = e;
				t->link = Rear->link;
				Rear->link = t;
				Rear = Rear->link;   //更新Rear
			}
			t2 = t2->link;  //循环++
		}
		t1 = t1->link;
	}
	t = P;
	P = P->link;
	free(t);  //把P节点本来指向的空结点去掉
	return P;

}
//多项式加法
Polynomial Add(Polynomial P1, Polynomial P2)
{
	Polynomial P, Rear, t1, t2, t;  // 结构多项式的头 尾.
	P = (Polynomial)malloc(sizeof(struct PolyNode));  //插入一个空结点
	P->link = NULL;
	Rear = P; /* 由P 记录结果多项式链表头结点 */
	t2 = P2;
	t1 = P1;

	while (t1 && t2) /* 当两个多项式都有非零项(都不空)待处理时 */
		if (t1->expon > t2->expon)
		{	 // // p1大   系数和指素接到rear的后面
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
	/* 将未处理完的另一个多项式的所有节点依次复制到结果多项式中去 */
	// p1不空
	while (t1)
	{
		Attach(t1->coef, t1->expon, &Rear);
		t1 = t1->link;

	}
	// p2 不空
	while (t2)
	{
		Attach(t2->coef, t2->expon, &Rear);
		t2 = t2->link;

	}
	// 释放临时结点
	t = P;
	P = P->link; /*令front指向结果多项式第一个非零项 */
	free(t); /* 释放临时空表头结点 */
	return P;
}
//多项式输出打印
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
			cout << " ";    //每一项之间要用空格隔开
		cout << P->coef << " " << P->expon;
		P = P->link;
	}
	cout << endl;
}
int main()
{
	Polynomial P1, P2, PP, PS;
	P1 = ReadPoly();  //读入多项式1
	P2 = ReadPoly(); //读入多项式2
	PP = Mult(P1, P2);
	PrintPoly(PP); //乘法运算并输出
	PS = Add(P1, P2);
	PrintPoly(PS); //加法运算并输出

	system("pause");
	return 0;
}