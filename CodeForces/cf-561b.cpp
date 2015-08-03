#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vvi edges(n);
    vector<bool> mustvisit(n, false);
    mustvisit[0] = true;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (a == b)
            mustvisit[a] = true;
        else {
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
    }

    vi component(n, -1);
    vi compsize;
    vector<bool> mustvisitcomp;
    vi oddeg;
    for (int s = 0; s < n; ++s) {
        if (component[s] != -1) continue;
        queue<int> qu;
        qu.push(s);
        oddeg.push_back(0);
        compsize.push_back(0);
        mustvisitcomp.push_back(false);
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            if (component[u] != -1) continue;
            component[u] = oddeg.size() - 1;
            compsize[component[u]]++;
            mustvisitcomp[component[u]] = mustvisitcomp[component[u]] && mustvisit[u];
            if (edges[u].size() & 1) oddeg[component[u]]++;
            for (int v : edges[u]) qu.push(v);
        }
    }
    
    int ans = 0, odd = oddeg[0];
    for (int c = 1; c < oddeg.size(); ++c) {
        if (compsize[c] == 1 && !mustvisitcomp[c]) continue;
        if (oddeg[c] == 0) continue;
        ans++;
        if (odd == 0) odd += oddeg[c];
        else odd += oddeg[c] - 2;
    }
    for (int c = 1; c < oddeg.size(); ++c) {
        if (compsize[c] == 1 && !mustvisitcomp[c]) continue;
        if (oddeg[c] > 0) continue;
        ans++;
        if (odd == 0) odd += 2;
    }

    ans += odd / 2;

    cout << ans << endl;

    return 0;
}


