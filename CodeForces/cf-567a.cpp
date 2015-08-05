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
    vector<ll> a(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    ll lhs = a[0], rhs = a[n - 1];
    for (int i = 0; i < n; ++i) {
        ll m = LLINF, M = -1;
        if (i > 0) m = min(m, a[i] - a[i - 1]);
        if (i < n - 1) m = min(m, a[i + 1] - a[i]);
        M = max(a[i] - a[0], a[n - 1] - a[i]);
        cout << m << ' ' << M << '\n';
    }
    
    return 0;
}
