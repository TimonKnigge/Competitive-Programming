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

const int N = 2e6;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> l(N, -1), r(N, -1), c(N, 0);

    int M = 0;
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        ai--;
        c[ai]++;
        M = max(M, c[ai]);
        if (l[ai] == -1) l[ai] = i;
        r[ai] = i;
    }
    
    int ll = -1, rr = n;
    for (int i = 0; i < N; ++i) {
        if (c[i] < M) continue;
        if (r[i] - l[i] < rr - ll) {
            rr = r[i]; ll = l[i];
        }
    }

    cout << (ll + 1) << ' ' << (rr + 1) << endl;
    
    return 0;
}
