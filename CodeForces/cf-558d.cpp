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
    
    int h, q; cin >> h >> q;
    vector< vector< pair<ll, ll>>> qu(h);
    
    for (int x = 0; x < q; ++x) {
        int i; ll L, R; bool ans;
        cin >> i >> L >> R >> ans;
        if(!ans) qu[i - 1].push_back({L, R});
        else {
              if (L > (1LL << (i - 1))) qu[i - 1].push_back({(1LL << (i - 1)), L - 1});
              if (R < (-1LL + (1LL << i))) qu[i - 1].push_back({R + 1, -1LL + (1LL << i)});
        }
    }
    vector<pair<ll, ll>> iv[50];
    for (int l = 0; l < h; ++l) {
        vector<pair<ll, ll>> ivtemp;
        for (int i = 0; i < qu[l].size(); ++i) {
            ivtemp.push_back(qu[l][i]);
        }
        if (l > 0)
            for (int i = 0; i < iv[l - 1].size(); ++i) {
                ll _L = iv[l - 1][i].first, _R = iv[l - 1][i].second;
                ivtemp.push_back({_L * 2, _R * 2 + 1});
            }
        sort(ivtemp.begin(), ivtemp.end());
        
        if (ivtemp.size() == 0) continue;
        ll myL = ivtemp[0].first, myR = ivtemp[0].second;
        for (int i = 1; i < ivtemp.size(); ++i) {
            if (ivtemp[i].first > 1LL + myR) {
                iv[l].push_back({myL, myR});
                myL = ivtemp[i].first; myR = ivtemp[i].second;
            } else myR = max(myR, ivtemp[i].second);
        }
        iv[l].push_back({myL, myR});
    }
    
    ll _L = (1LL << (h - 1)), _R = -1LL + (1LL << h);
    h -- ;
    if (iv[h].size() == 0) if (h == 0) cout << 1 << endl; else cout << "Data not sufficient!" << endl;
    else if (iv[h].size() == 1) {
        if (iv[h][0].first == _L && iv[h][0].second == _R) cout << "Game cheated!" << endl;
        else if (iv[h][0].first == _L + 1 && iv[h][0].second == _R) cout << _L << endl;
        else if (iv[h][0].first == _L && iv[h][0].second == _R - 1) cout << _R << endl;
        else cout << "Data not sufficient!"  << endl;
    } else if (iv[h].size() == 2) {
        if (iv[h][0].first == _L && iv[h][1].second == _R
            && iv[h][0].second + 2 == iv[h][1].first)
            cout << (iv[h][0].second + 1) << endl;
        else cout << "Data not sufficient!" <<  endl;
    } else {
        cout << "Data not sufficient!"  <<  endl;
    }
    
    return 0;
}
