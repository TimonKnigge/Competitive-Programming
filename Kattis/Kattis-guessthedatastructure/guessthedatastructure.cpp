#include <iostream>
#include <stdio.h>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

#ifdef _MSC_VER
#define scanf scanf_s
#endif

int main() {

	int n;
	while (scanf("%d", &n) != EOF) {
		
		bool is_st = true, is_qu = true, is_pq = true;
		stack<int> st;
		queue<int> qu;
		priority_queue<int> pq;

		for (int i = 0; i < n; ++i) {
			int c, x;
			scanf("%d %d", &c, &x);
			if (c == 1) {
				st.push(x);
				qu.push(x);
				pq.push(x);
			}
			else {
				if (st.empty())
					is_st = is_qu = is_pq = false;
				else {
					is_st = is_st && (st.top() == x); st.pop();
					is_qu = is_qu && (qu.front() == x); qu.pop();
					is_pq = is_pq && (pq.top() == x); pq.pop();
				}
			}
		}

		vector<string> o;
		if (is_st) o.push_back("stack");
		if (is_qu) o.push_back("queue");
		if (is_pq) o.push_back("priority queue");
		cout << (o.empty() ? "impossible" : ((o.size() > 1) ? "not sure" : o[0])) << endl;
	}
	
	return 0;
}