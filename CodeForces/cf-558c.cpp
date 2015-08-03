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
    
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    
    vector< vector<bool> > bitwise(n);
    vector<bool> prefix;
    bool set = false;
    for (int i = 0; i < n; ++i) {
        int v = a[i];
        while (v > 0) {
            if (v % 2 == 1) bitwise[i].push_back(true);
            else bitwise[i].push_back(false);
            v /= 2;
        }
        if (!set) {
            set = true;
            for (int j = bitwise[i].size() - 1; j >= 0; --j) {
                prefix.push_back(bitwise[i][j]);
            }
        } else {
	    int j, k;
            for (j = bitwise[i].size() - 1, k = 0; j >= 0 && k < prefix.size(); --j, ++k) {
                if (bitwise[i][j] != prefix[k]) break;
            }
	    while (k < prefix.size()) prefix.pop_back();
        }
    }


    int pfl = prefix.size();
    vector<int> shl(n, -1), reml(n, -1), reml_sort;
    for (int i = 0; i < n; ++i) {
        for (int j = bitwise[i].size() - 1 - pfl; j >= 0; --j) {
            if (bitwise[i][j]) {
                shl[i] = j + 1;
                reml[i] = int(bitwise[i].size()) - pfl - shl[i];
                reml_sort.push_back(reml[i]);
                break;
            }
        }
        if (shl[i] != -1) continue;
        shl[i] = 0;
        reml[i] = int(bitwise[i].size()) - pfl - shl[i];
        reml_sort.push_back(reml[i]);
    }
    sort(reml_sort.begin(), reml_sort.end());
    int median = reml_sort.size() == 0 ? 0 : reml_sort[reml_sort.size() / 2];
   

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        // remove non-common prefix stuff
        ans += shl[i];
        // length of the remaining string
        int leng = bitwise[i].size() - shl[i] - pfl;
        // shift to the correct length
        ans += abs(leng - median);
    }

    cout << ans << endl;

    return 0;
}
