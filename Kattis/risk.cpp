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
#include <string.h>  // Include for memset!
#include <complex>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

const int INF = 2000000000;                     // 9
const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

// Flow
struct FlowNetwork {
    struct edge {
        int v, nxt; ll cap, flo; bool mark;
        edge(int _v, ll _cap, int _nxt, bool _ma) : v(_v), cap(_cap), nxt(_nxt), flo(0), mark(_ma) { }
    };
    int n, edge_count = 0, *h;
    vector<edge> e;
    FlowNetwork(int V, int E = 0) : n(V) {
        e.reserve(2 * (E == 0 ? V : E));
        memset(h = new int[V], -1, n * sizeof(int));
    }
    void add_edge(int u, int v, ll uv_cap, ll vu_cap = 0, bool mark = false) {
        e.push_back(edge(v, uv_cap, h[u], mark)); h[u] = edge_count++;
        e.push_back(edge(u, vu_cap, h[v], mark)); h[v] = edge_count++;
    }
    void cleanup() { delete[] h; }
    void reset() {
        for (int i = 0; i < e.size(); ++i) e[i].flo = 0;
    }
    // Only copy what is needed:
    ll dinic(int s, int t);
    ll dinic_augment(int s, int t, int* d, ll cap);
};
// -Flow
// Dinic (1 <= n <= 100)
#define MAXV 210
ll FlowNetwork::dinic_augment(int s, int t, int* d, ll cap) {
    if (s == t) return cap;
    ll f = 0, df = 0;
    for (int i = h[s]; i != -1; i = e[i].nxt) {
        if (e[i].cap > e[i].flo && d[s] + 1 == d[e[i].v]) {
            f += (df = dinic_augment(e[i].v, t, d, min(cap, e[i].cap - e[i].flo)));
            e[i].flo += df;
            e[i ^ 1].flo -= df;
            if((cap -= df) == 0) break;            
    }    }
    return f;
}

ll FlowNetwork::dinic(int s, int t) {
    int q[MAXV], d[MAXV]; ll f = 0;
    while (true) {
        memset(d, -1, n * sizeof(int));
        int l = 0, r = 0, u = -1, i;
        d[q[r++] = s] = 0;
        while (l != r && u != t)
            for (u = q[l++], i = h[u]; i != -1; i = e[i].nxt) 
                if (e[i].cap > e[i].flo && d[e[i].v] == -1)
                    d[q[r++] = e[i].v] = d[u] + 1;
        if (d[t] == -1) break;
        f += dinic_augment(s, t, d, LLINF);
    }
    return f;
}
// -Dinic
bool reachable(FlowNetwork& fn, int so, int si, ll ncap, int lo, int bo) {
    for (int i = 0; i < fn.e.size(); ++i) {
        if (fn.e[i].mark) fn.e[i].cap = ncap;
    }
    fn.reset();
    return (fn.dinic(so, si) >= (lo + ncap * bo));
}

const int LOCKED = 0, BORDERING = 1, HOSTILE = 2, INDETERMINATE = -1;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t ) {

    int n;
    cin >> n;
    ll _sum = 0;
    vector<int> a(n, 0), status(n, INDETERMINATE);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        _sum += a[i];
        if (a[i] == 0) status[i] = HOSTILE;
    }
    
    vector<vector<bool>> adj(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i) {
        string ss; cin >> ss;
        for (int j = 0; j < n; ++j) {
            adj[i][j] = (ss[j] == 'Y');
        }
    }
    
    int lo = 0, bo = 0;
    for (int i = 0; i < n; ++i) {
        if (status[i] != INDETERMINATE) continue;
        for (int j = 0; j < n && status[i] == INDETERMINATE; ++j) {
            if (adj[i][j] && status[j] == HOSTILE) status[i] = BORDERING;
        }
        if (status[i] == INDETERMINATE) status[i] = LOCKED;
        if (status[i] == LOCKED) lo ++;
        else bo++;
    }
    
    // construct flow network
    FlowNetwork fn(2 * (n + 1));
    int SOURCE = 2 * n, SINK = 2 * n + 1;
    
    for (int u = 0; u < n; ++u) {
        if (status[u] == HOSTILE) continue;
        fn.add_edge(SOURCE, u, a[u], 0, false);
        fn.add_edge(u + n, SINK, 1, 0, status[u] == BORDERING);
        for (int v = 0; v < n; ++v) {
            if ((adj[u][v] || u == v) && status[v] != HOSTILE) {
                fn.add_edge(u, v + n, LLINF, 0, false);
            }
        }
    }
    
    // binsearch the answer
    ll l = 0, h = _sum + 1;
    while (l < h) {
        ll m = (l + h) / 2;
        if (reachable(fn, SOURCE, SINK, m, lo, bo)) {
            l = m + 1;
        } else {
            h = m;
        }
    }
    
    cout << (l - 1) << endl;

    }

    return 0;
}
