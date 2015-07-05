#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

#define INF 2000000000

typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {
	int N, H, L;
	cin >> N >> H >> L;

	vi d(N, INF);
	vvi e(N);
	queue<int> qu;

	for (int i = 0; i < H; ++i) {
		int x; cin >> x;
		d[x] = 0;
		qu.push(x);
	}

	for (int i = 0; i < L; ++i) {
		int a, b;
		cin >> a >> b;
		e[a].push_back(b);
		e[b].push_back(a);
	}

	while (!qu.empty()) {
		int u = qu.front(); qu.pop();
		for (int v : e[u]) {
			if (d[u] + 1 < d[v]) {
				d[v] = d[u] + 1;
				qu.push(v);
			}
		}
	}

	int u = 0;
	for (int v = 1; v < N; ++v) {
		if (d[v] > d[u]) {
			u = v;
		}
	}
	cout << u << endl;
}