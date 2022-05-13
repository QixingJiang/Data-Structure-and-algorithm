/*
排序6 Sort with Swap(0, i)
意思就是只允许用0和一个数进行交换来排序
输出一个序列要排序成功的最小交换次数
具体计算方法参考陈越的小白专场，用环来做（物理排序）。	
*/

//10-排序6 Sort with Swap(0, i)
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
            S++;  // 计算单元环个数S
    }

    int initial = A[0];  // 把A[0]保存起来

    // 计算多元环个数K
    for (i = 0; i < N; i++) {
        if (A[i] != i) {   //当A[i]不等于i的时候，这个A[i]就当一个多元环的起点
            j = i;
            while (A[j] != j) {     //注意是用j来做判断 下面j=A[j]导致每次循环都会改变j 就会实现溯源的功能
                p = j;  // 把j保存在p里
                j = A[j];  // 更新j=A[j]
                A[p] = p;  //原始第j位=j  这里相当于A[j]=[j] 但是是原来的j 相当于原来的j已经被溯源了
            }
            K++;   
        }
    }

    if (initial == 0)
        printf("%d\n", N - S + K);   // 当A[0]=0,那么说明没有包含0的多元环。  
    else
        printf("%d\n", N - S + K - 2);   // 包含0的多元环, 交换次数=N-S+K-2

    return 0;
}