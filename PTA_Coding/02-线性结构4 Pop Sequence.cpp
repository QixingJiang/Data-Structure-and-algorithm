/*
02-线性结构4 Pop Sequence
*/

#include<iostream>
#include<vector>
#include<stack>
using namespace std;


int main()
{
	int m, k, n;
	cin >> m >> n >> k;
	for (int i = 0; i < k; i++)
	{
		bool b = true;
		stack<int> s;
		vector<int>v(n + 1);
		int cur = 1;
		for (int j = 0; j < n; j++)
		{
			cin >> v[j];
			while (s.size() <= m && b == true)
			{
				if (s.empty() || s.top() != v[j])
				{
					s.push(cur);
					cur++;
				}
				else if (s.top() == v[j])
				{
					s.pop();
					break;
				}
			}
			if (s.size() > m)
			{
				b = false;
			}
		}
		if (b == true) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}