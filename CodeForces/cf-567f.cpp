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
#include <cassert>

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

ll dp[72][72];

// Satisfies
bool satisfies(int v1, int v2, pair<int, ii> con) {
    if (con.first == 1) return v1 == v2;
    if (con.first == 2) return v1 < v2;
    if (con.first == 3) return v1 > v2;
    if (con.first == 4) return v1 <= v2;
    return v1 >= v2;
}

#define ff second.first
#define sf second.second

ll ways(int l, int r, vector<pair<int, ii>> constraints) {
    if (dp[l][r] == -1) {
        if (l + 1 == r) {
            // Only
            bool stf = true;
            for (auto it : constraints) { 
                if (it.ff >= l && it.ff <= r
                    && it.sf >= l && it.sf <= r)
                    stf = stf && satisfies(0, 0, it);
            }
            dp[l][r] = stf ? 1 : 0;
        } else {
            bool stf1 = true, stf2 = true, stf3 = true;
            for (auto it : constraints) {
                if (!(it.ff >= l && it.ff <= r && it.sf >= l && it.sf <= r))
                    continue;
                // l , l + 1
                if ((it.ff == l || it.ff == l + 1) && (it.sf == l || it.sf == l + 1))
                    stf1 = stf1 && satisfies(0, 0, it);
                else if (it.ff == l || it.ff == l + 1)
                    stf1 = stf1 && satisfies(0, 1, it);
                else if (it.sf == l || it.sf == l + 1)
                    stf1 = stf1 && satisfies(1, 0, it);
                // l , r
                if ((it.ff == l || it.ff == r) && (it.sf == l || it.sf == r))
                    stf2 = stf2 && satisfies(0, 0, it);
                else if (it.ff == l || it.ff == r)
                    stf2 = stf2 && satisfies(0, 1, it);
                else if (it.sf == l || it.sf == r)
                    stf2 = stf2 && satisfies(1, 0, it);
                // r - 1, r
                if ((it.ff == r - 1 || it.ff == r) && (it.sf == r - 1 || it.sf == r))
                    stf3 = stf3 && satisfies(0, 0, it);
                else if (it.ff == r - 1 || it.ff == r)
                    stf3 = stf3 && satisfies(0, 1, it);
                else if (it.sf == r - 1 || it.sf == r)
                    stf3 = stf3 && satisfies(1, 0, it);

            }
            dp[l][r] = 0;
            if (stf1) dp[l][r] += ways(l + 2, r, constraints);
            if (stf2) dp[l][r] += ways(l + 1, r - 1, constraints);
            if (stf3) dp[l][r] += ways(l, r - 2, constraints);
        }
    }
    return dp[l][r];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < 72; ++i) for (int j = 0; j < 72; ++j) dp[i][j] = -1;
    
    int n, k;
    cin >> n >> k;
    vector<pair<int, ii>> constraints;
    for (int i = 0; i < k; ++i) {
        int x, y; string c;
        cin >> x >> c >> y;
        x--; y--;
        int type = 1;
        if (c == "<") type = 2;
        if (c == ">") type = 3;
        if (c == "<=") type = 4;
        if (c == ">=") type = 5;
        constraints.push_back({type, {x, y}});
    }

    cout << ways(0, 2 * n - 1, constraints) << endl;
    
    return 0;
}
