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
#include <math.h>

const int INF = 2000000000;                     // 9
const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long double ld;

// Dijkstra
void dijkstra(vvii &edges, int s, vi &dist) {
    dist.assign(edges.size(), LLINF);
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    dist[s] = 0; pq.push(ii(0, s));
    while (!pq.empty()) {
        ii top = pq.top(); pq.pop();
        ll u = top.second, d = top.first;
        if (d == dist[u]) {
            for (ii it : edges[u]) {
                ll v = it.first, d_uv = it.second;
                if (dist[u] + d_uv < dist[v]) {
                    dist[v] = dist[u] + d_uv;
                    pq.push(ii(dist[v], v));
                }
            }
        }
    }
}
// -Dijkstra

// Toposort
int s_ix = 0;
void visit (int u, vvi &edges, vb &visited, vi &sorted) {
    visited[u] = true;
    for (int v : edges[u]) if (!visited[v]) visit(v, edges, visited, sorted);
    sorted[s_ix--] = u;
}
// -Toposort

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, s, t;
    cin >> n >> m >> s >> t; 
    s--; t--;

    vvii edges(n, vii()), rev_edges(n, vii());
    vvi edgesid(n, vi());
    for (int i = 0; i < m; ++i) {
        ll a, b, l; cin >> a >> b >> l;
        edges[a - 1].push_back({b - 1, l});
        edgesid[a - 1].push_back(i);
        rev_edges[b - 1].push_back({a - 1, l});
    }
    vi sdist, tdist;
    dijkstra(edges, s, sdist);
    dijkstra(rev_edges, t, tdist);

    vector<ll> status(m, 0), val(m, -10);
    vvi sh_edges(n, vi()), sh_edgesid(n, vi()); // Shortest path graph
    for (int u = 0; u < n; ++u) {
        for (int j = 0; j < edges[u].size(); ++j) {
            auto vv = edges[u][j];
            int v = vv.first;
            pair<int, ll> info = {edgesid[u][j], vv.second};
            ll l = info.second;
            ll mm = sdist[u] + tdist[v] + l - sdist[t];
            if (sdist[u] == LLINF || tdist[v] == LLINF) continue;
            if (mm < l - 1) { status[info.first] = 1; val[info.first] = mm; }
            if (mm == 0){ sh_edges[u].push_back(v); sh_edgesid[u].push_back(info.first); }
        }
    }
    vi sorted(n, -1);
    vi sortedinv(n, -1);
    vb visited(n, false);
    s_ix = n - 1;
    visit(s, sh_edges, visited, sorted); // Toposort from s
    // Invert the sorting
    for (int i = 0; i < n; ++i) if(sorted[i] != -1) sortedinv[sorted[i]] = i;
    vb is_art_point(n, false);
    visited.assign(n, false);

    int r = 0;
    for (int i = 0; i < n; ++i) {
        r = max(r, i);
        if (sorted[i] != -1) {
            if (i == r) is_art_point[sorted[i]] = true;
            for (int v : sh_edges[sorted[i]]) r = max(r, int(sortedinv[v]));
        }
        visited[i] = true;
    }

    for (int u = 0; u < n; ++u) {
        if (!is_art_point[u]) continue;
        for (int j = 0; j < sh_edges[u].size(); ++j) {
            int v = sh_edges[u][j];
            if (!is_art_point[v]) continue;
            if (sh_edges[u].size() > 1) continue;
            status[sh_edgesid[u][j]] = 2;
        }
    }

    for (int i = 0; i < m; ++i) {
        if (status[i] == 0 || (val[i] == -10 && status[i] == 1)) cout << "NO\n";
        if (status[i] == 1) cout << "CAN " << (val[i] + 1) << '\n';
        if (status[i] == 2) cout << "YES\n";
    }
    return 0;
}
