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
    
    int h;
    cin >> h;
    string path;
    getline(cin, path);

    ll s = (1 << (h + 1)) - 1, d = 1;
    for (int i = 0; i < path.length(); ++i) {
        if (path[i] != 'L' && path[i] != 'R') continue;
        ll l = 0, r = 0;
        if (s & 1) {
            r = s - 2 * d;
            l = r + 1;
        } else {
            l = s - 2 * d;
            r = l - 1;
        }
        if (path[i] == 'L') {
            d = s - l;
            s = l;
        } else {
            d = s - r;
            s = r;
        } 
    }

    cout << s << endl;

    return 0;
}
