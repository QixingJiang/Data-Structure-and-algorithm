/*
����6 Sort with Swap(0, i)
��˼����ֻ������0��һ�������н���������
���һ������Ҫ����ɹ�����С��������
������㷽���ο���Խ��С��ר�����û��������������򣩡�	
*/

//10-����6 Sort with Swap(0, i)
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
#define MaxN 100001

int main()
{
    int A[MaxN];
    int N;
    int i, j, p, S = 0, K = 0;

    cin >> N;

    for (i = 0; i < N; i++) {
        cin >> A[i];
        if (A[i] == i)
            S++;  // ���㵥Ԫ������S
    }

    int initial = A[0];  // ��A[0]��������

    // �����Ԫ������K
    for (i = 0; i < N; i++) {
        if (A[i] != i) {   //��A[i]������i��ʱ�����A[i]�͵�һ����Ԫ�������
            j = i;
            while (A[j] != j) {     //ע������j�����ж� ����j=A[j]����ÿ��ѭ������ı�j �ͻ�ʵ����Դ�Ĺ���
                p = j;  // ��j������p��
                j = A[j];  // ����j=A[j]
                A[p] = p;  //ԭʼ��jλ=j  �����൱��A[j]=[j] ������ԭ����j �൱��ԭ����j�Ѿ�����Դ��
            }
            K++;   
        }
    }

    if (initial == 0)
        printf("%d\n", N - S + K);   // ��A[0]=0,��ô˵��û�а���0�Ķ�Ԫ����  
    else
        printf("%d\n", N - S + K - 2);   // ����0�Ķ�Ԫ��, ��������=N-S+K-2

    return 0;
}