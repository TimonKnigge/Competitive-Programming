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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ii> vals;
    for (int i = 0; i < n; ++i) {
        int x, a;
        cin >> x >> a;
        vals.push_back({x, a});
    }
    
    sort(vals.begin(), vals.end());
    int m = 0;
    for (; m < n; ++m) { if (vals[m].first > 0) break; }
    
    ll ans = 0;
    int l = m - 1, r = m;
    while (l >= 0 && r < n) {
          ans += vals[l].second + vals[r].second;
          l--; r++;
    }

    if (l >= 0) ans += vals[l].second;
    else if (r < n) ans += vals[r].second;

    cout << ans << endl;
    
    return 0;
}
