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
    
    int n; ll k, k2;
    cin >> n >> k;
    k2 = k * k;
    vector<ll> a(n, 0LL);
    for (int i = 0; i < n; ++i) cin >> a[i];
    map<ll, ll> co1, co2;
    
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] % k2 == 0) {
            ll val = a[i] / k2;
            auto it = co2.find(val);
            if (it != co2.end()) ans += it->second;
        }
        if (a[i] % k == 0) {
            ll val = a[i] / k;
            auto it = co1.find(val);
            if (it != co1.end()) {
                auto it2 = co2.find(val);
                if (it2 != co2.end()) it2->second += it->second;
                else co2.insert({val, it->second});
            }
        }
        auto it3 = co1.find(a[i]);
        if (it3 != co1.end()) it3->second++;
        else co1.insert({a[i], 1});
    }

    cout << ans << endl;
    
    return 0;
}
