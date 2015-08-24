#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

// suffixarray
struct S { int l, r, p; };
bool operator<(const S &lhs, const S &rhs) { 
	return lhs.l != rhs.l ? lhs.l < rhs.l : lhs.r < rhs.r; 
}
bool operator==(const S &lhs, const S &rhs) {
	return lhs.l == rhs.l && lhs.r == rhs.r;
}

struct SuffixArray {
	string s;
	int n;
	vvi P;
	SuffixArray(string &_s) : s(_s), n(_s.length()) { construct(); }
	void construct() {
		vector<S> L(n, {0, 0, 0});
		P.push_back(vi(n, 0));
		for (int i = 0; i < n; ++i) P[0][i] = int(s[i]);
		for (int k = 1, cnt = 1; cnt / 2 < n; ++k, cnt *= 2) {
			P.push_back(vi(n, 0));
			for (int i = 0; i < n; ++i)
				L[i] = { P[k - 1][i], i + cnt < n 
					? P[k - 1][i + cnt] : -1, i};
			sort(L.begin(), L.end());
			for (int i = 0; i < n; ++i)
				P[k][L[i].p] = (i > 0 && L[i] == L[i - 1]
				? P[k][L[i - 1].p] : i);
		}
	}
	vi &get_array() { return P.back(); }
	int lcp(int x, int y) {
		int k, ret = 0;
		if (x == y) return n - x;
		for (int k = P.size() - 1; k >= 0 && x < n && y < n; --k)
			if (P[k][x] == P[k][y]) {
				x += 1 << k;
				y += 1 << k;
				ret += 1 << k;
			}
		return ret;
	}
};
// -suffixarray

class MaxQueue {
public:
	stack<pair<int, int> > inbox, outbox;
	void enqueue(int v) {
		int m = v;
		if (!inbox.empty()) m = max(m, inbox.top().second);
		inbox.push({v, m});
	}
	void dequeue() {
		if (outbox.empty() && !inbox.empty()) {
			auto t = inbox.top(); inbox.pop();
			outbox.push({t.first, t.first});
			while (!inbox.empty()) {
				t = inbox.top(); inbox.pop();
				int m = max(t.first, outbox.top().second);
				outbox.push({t.first, m});
			}
		}
		outbox.pop();
	}
	int get_max() {
		if (outbox.empty()) return inbox.top().second;
		if (inbox.empty()) return outbox.top().second;
		return max(outbox.top().second, inbox.top().second);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int m;
	while (true) {
		cin >> m;
		if (m == 0) break;
		
		string s;
		cin >> s;
		SuffixArray sa(s);
		
		vector<int> arr(s.length(), 0);
		for (int i = 0; i < s.length(); ++i) {
			arr[sa.get_array()[i]] = i;
		}
		
		MaxQueue mq;
		int L = 0, C = -1;
		for (int i = 0; i < m; ++i) mq.enqueue(arr[i]);
		for (int i = 0; i < s.length() - m + 1; ++i) {
			if (i > 0) {
				mq.enqueue(arr[i + m - 1]);
			}

			int mn = sa.lcp(arr[i], arr[i + m - 1]);
			if (mn > L) {
				L = mn;
				C = mq.get_max();
			} else if (mn == L) {
				C = max(C, mq.get_max());
			}
			
			mq.dequeue();
		}

		if (L > 0) cout << L << ' ' << C << '\n';
		else cout << "none\n";
	}
	
	return 0;
}

