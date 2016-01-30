#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

template <class T>
class MinQueue {
public:
	stack< pair<T, T> > inbox, outbox;
	void enqueue(T val) {
		T m = val;
		if (!inbox.empty()) m = min(m, inbox.top().second);
		inbox.push(pair<T, T>(val, m));
	}
	bool dequeue(T* d = nullptr) {
		if (outbox.empty() && !inbox.empty()) {
			pair<T, T> t = inbox.top(); inbox.pop();
			outbox.push(pair<T, T>(t.first, t.first));
			while (!inbox.empty()) {
				t = inbox.top(); inbox.pop();
				T m = min(t.first, outbox.top().second);
				outbox.push(pair<T, T>(t.first, m));
			}
		}
		if (outbox.empty()) return false;
		else {
			if (d != nullptr) *d = outbox.top().first;
			outbox.pop();
			return true;
		}
	}
	bool empty() { return outbox.empty() && inbox.empty(); }
	size_t size() { return outbox.size() + inbox.size(); }
	T get_min() {
		if (outbox.empty()) return inbox.top().second;
		if (inbox.empty()) return outbox.top().second;
		return min(outbox.top().second, inbox.top().second);
	}
};

int main() {
	
	while (true) {
		int n;
		scanf("%d", &n);
		
		if (n == 0) break;
		
		vi a(n, 0);
		for (int i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		
		vi b(n+n, 0);
		b[0] = a[0];
		for (int i = 1; i < n+n; ++i)
			b[i] = b[i-1] + a[i%n];
		
		// q: voor welke 0<=i<n
		// geldt: a[0]+..+a[i-1] >= b[i],..,b[i+n-1]
		
		MinQueue<int> mq;
		for (int i = 0; i < n; ++i)
			mq.enqueue(b[i]);
		
		int sum = 0, ans = 0;
		for (int i = 0; i < n; ++i) {
			if (mq.get_min() >= sum)
				++ans;
			mq.dequeue();
			mq.enqueue(b[n + i]);
			sum += a[i];
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
