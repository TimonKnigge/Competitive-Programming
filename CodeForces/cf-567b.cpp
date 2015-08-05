#include <iostream>
#include <cstdio>
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
    scanf("%d", &n);
    vector<pair<bool, int>> event;
    vector<bool> inroom(1e6, false);
    int st = 0;
    for (int i = 0; i < n; ++i) {
        char c; int v;
        scanf(" %c %d", &c, &v);
        if (c == '+') {
            inroom[v - 1] = true;
            event.push_back({false, v - 1});
        } else {
            if (!inroom[v - 1]) {
                st++;
            }
            event.push_back({true, v - 1});
        } 
    }

    int M = st;
    for (int i = 0; i < n; ++i) {
        if (event[i].first) st--; else st++;
        M = max(M, st);
    }

    printf("%d\n", M);
    
    return 0;
}
