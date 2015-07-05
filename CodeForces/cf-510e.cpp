#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <cmath>
#include <cstring>

#define INF 2000000000
#define LLINF 9000000000000000

using namespace std;

typedef pair <int, int > ii;
typedef vector <int > vi;
typedef vector < vi > vvi;
typedef vector < ii > vii;
typedef vector < vii > vvii;
typedef vector <bool > vb;
typedef long long ll;
typedef long double ld;

// PRIMES
ll _sieve_size;
bitset<10000010> bs;
vi primes;

void sieve(ll upperbound) {
	_sieve_size = upperbound + 1;
	bs.reset(); bs.flip();
	bs.set(0, false); bs.set(1, false);
	for (ll i = 2; i <= _sieve_size; ++i) {
		for (ll j = i * i; j <= _sieve_size; j += i) bs.set((size_t)j, false);
		primes.push_back((int)i);
	}
}

bool is_prime(ll N) {
	if (N < _sieve_size) return bs.test(N);
	for (int i = 0; i < primes.size(); ++i) if (N % primes[i] == 0) return false;
	return true;
}
// -PRIMES
// MAXFLOW
struct FlowNetwork {
	struct edge {
		int v, nxt; ll cap, flo;
		edge(int _v, ll _cap, int _nxt) : v(_v), cap(_cap), nxt(_nxt), flo(0) { }
	};
	int n, edge_count = 0, *h;
	vector<edge> e;
	FlowNetwork(int V, int E = 0) : n(V) {
		e.reserve(2 * (E == 0 ? V : E));
		memset(h = new int[V], -1, n * sizeof(int));
	}
	void add_edge(int u, int v, ll uv_cap, ll vu_cap = 0) {
		e.push_back(edge(v, uv_cap, h[u])); h[u] = edge_count++;
		e.push_back(edge(u, vu_cap, h[v])); h[v] = edge_count++;
	}
	void cleanup() { delete[] h; }
	ll edmonds_karp(int s, int t);
};
#define MAXV 300
ll FlowNetwork::edmonds_karp(int s, int t) {
	int v, p[MAXV], q[MAXV]; ll f = 0, c[MAXV];
	while (true) {
		memset(p, -1, n * sizeof(int));
		int i, u = -1, l = 0, r = 0;
		c[s] = LLINF; p[q[r++] = s] = -2;
		while (l != r && u != t) {
			for (u = q[l++], i = h[u]; i != -1; i = e[i].nxt) {
				if (e[i].cap > e[i].flo && p[v = e[i].v] == -1) {
					p[q[r++] = v] = i;
					c[v] = min(c[u], e[i].cap - e[i].flo);
				}
			}
		}
		if (p[t] == -1) break;
		for (i = p[t]; i != -2; i = p[e[i ^ 1].v]) {
			e[i].flo += c[t]; e[i ^ 1].flo -= c[t];
		}
		f += c[t];
	}
	return f;
}
// -MAXFLOW

struct Fox {
public:
	int a = -1, id = -1;
	bool odd = false;
	vector<int> nbrs;
	Fox() {}
	Fox(int a, int id) : a(a), odd(a % 2 == 1), id(id) {}
};

// DFS
void dfs(int ix, vector<Fox>& mine, vector<Fox>& other, bitset<210>& vs, vvi& table) {
	vs.set(mine[ix].id, true);
	table[table.size() - 1].push_back(mine[ix].id);
	for (int nx : mine[ix].nbrs) {
		if (vs.test(other[nx].id)) continue;
//		cout << mine[ix].a << "(" << mine[ix].id << ") next to " << other[nx].a << " (" << other[nx].id << ") (sum is " << (mine[ix].a + other[nx].a) << ")" << endl;
		dfs(nx, other, mine, vs, table);
	}
}
// -DFS

int main() {
	sieve(1e5);
	int n;
	cin >> n;

	// Take input, divide foxes into two groups: even and odd foxes.
	vector<Fox> oddFoxes, evenFoxes;
	for (int i = 0; i < n; ++i) {
		int a; cin >> a;
		if (a % 2 == 0)
			evenFoxes.push_back(Fox(a, i + 1));
		else
			oddFoxes.push_back(Fox(a, i + 1));
	}

	// Groups of parity should be of the same size
	int evsize = evenFoxes.size(),
		odsize = oddFoxes.size();
	if (evsize != odsize)
		cout << "Impossible" << endl;
	else {
		// Connect all odd foxes to the sink, even foxes to the source:
		// 0 = source, 1..ev.size() == even foxes,
		// ev.size() + 1..ev.size()+od.size() == odd foxes,
		// ev.size() + od.size() + 1 = sink
		int SOURCE = 0,
			SINK = evsize + odsize + 1;
		FlowNetwork fn(n + 2);
		for (int i = 0; i < evsize; ++i) {
			fn.add_edge(SOURCE, i + 1, 2);
		}
		for (int i = 0; i < odsize; ++i) {
			fn.add_edge(evsize + i + 1, SINK, 2);
		}

		// Connect all foxes whose numbers sum to a prime
		for (int i = 0; i < evsize; ++i) {
			for (int j = 0; j < odsize; ++j) {
				if (is_prime(evenFoxes[i].a + oddFoxes[j].a)) {
					fn.add_edge(i + 1, evsize + j + 1, 1);
				}
			}
		}
		
		// Match!
		ll flow = fn.edmonds_karp(SOURCE, SINK);
		
		// Did we match everyone?
		if (flow <  2 * evsize) {
			cout << "Impossible" << endl;
		}
		else {
			// Retrieve the seating
			for (int i = 0; i < fn.e.size(); ++i) {
				if (fn.e[i].cap != 1) continue;
				if (fn.e[i].flo != 1) continue;
				int ev = fn.e[i ^ 1].v - 1,
					od = fn.e[i].v - 1 - evsize;
				evenFoxes[ev].nbrs.push_back(od);
				oddFoxes[od].nbrs.push_back(ev);
			}

			// Gather everyone around a table through a dfs
			vvi table; bitset<210> vs; vs.reset();
			for (int i = 0; i < evsize; ++i) {
				if (vs.test(evenFoxes[i].id)) continue;
				table.push_back(vi());
				dfs(i, evenFoxes, oddFoxes, vs, table);
			}

			// do output
			cout << table.size() << endl;
			for (vi& t : table) {
				cout << t.size();
				for (int i = 0; i < t.size(); ++i)
					cout << ' ' << t[i];
				cout << endl;
			}
		}
		fn.cleanup();
	}
	
	return 0;
}
