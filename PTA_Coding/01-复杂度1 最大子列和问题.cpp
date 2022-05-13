/*
01-复杂度1 最大子列和问题
*/





#include<iostream>
using namespace std;
int main() {
    int n, num, sum = 0, max = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> num;
        sum += num;
        if (sum > max)max = sum;
        else if (sum < 0)sum = 0;
    }
    cout << max;
    return 0;
}