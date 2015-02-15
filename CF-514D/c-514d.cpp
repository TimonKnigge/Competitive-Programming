#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <stack>
#include <algorithm>

using namespace std;

typedef long long ll;

template <class T>
class MaxQueue {
public:
	stack< pair<T, T> > inbox, outbox;
	void enqueue(T val) {
		T m = val;
		if (!inbox.empty())
			m = max(m, inbox.top().second);
		inbox.push(pair<T, T>(val, m));
	}
	bool dequeue(T* d = nullptr) {
		if (outbox.empty() && !inbox.empty()) {
			pair<T, T> t = inbox.top(); inbox.pop();
			outbox.push(pair<T, T>(t.first, t.first));
			while (!inbox.empty()) {
				t = inbox.top(); inbox.pop();
				T m = max(t.first, outbox.top().second);
				outbox.push(pair<T, T>(t.first, m));
			}
		}
		if (outbox.empty()) return false;
		else {
			if(d != nullptr) *d = outbox.top().first;
			outbox.pop();
			return true;
		}
	}
	bool empty() { return outbox.empty() && inbox.empty(); }
	size_t size() { return outbox.size() + inbox.size(); }
	T get_max() {
		if (!outbox.empty() && !inbox.empty())
			return max(outbox.top().second, inbox.top().second);
		if (outbox.empty()) return inbox.top().second;
		return outbox.top().second;
	}
};

int main() {
	
	int n, m; ll k;
	cin >> n >> m >> k;

	// Read input
	vector< vector<ll> > droid(n, vector<ll>(m, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> droid[i][j];
		}
	}

	// Move a sliding window [l, r)
	int l = 0, r, best = 0; ll cost;
	vector<ll> shots(m, 0);
	vector<	MaxQueue<ll> > active(m);
	for (r = 1; r <= n; ++r) {

		// Enter droid r - 1
		cost = 0;
		for (int i = 0; i < m; ++i) {
			active[i].enqueue(droid[r - 1][i]);
			cost += active[i].get_max();
		}

		// Discard droids on the left until the solution is valid
		while (l < r && cost > k) {
			cost = 0; l++;
			for (int i = 0; i < m; ++i) {
				active[i].dequeue();
				if (!active[i].empty())
					cost += active[i].get_max();
			}
		}

		// Maybe store the solution
		if (r - l > best) {
			best = r - l;
			for (int i = 0; i < m; ++i) {
				shots[i] = active[i].get_max();
			}
		}
	}

	cout << shots[0];
	for (int i = 1; i < m; ++i)
		cout << ' ' << shots[i];
	cout << endl;

	return 0;
}