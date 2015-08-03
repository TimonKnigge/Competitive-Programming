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

void lexosort(string& a, int s, int l) {
    if (l % 2 == 1) return;
    
    lexosort(a, s, l / 2);
    lexosort(a, s + l / 2, l / 2);

    bool swap = true;
    for (int i = 0; i < l / 2; ++i) {
        if (a[s + i] < a[s + i + l / 2]) { swap = false; break; }
        if (a[s + i] > a[s + i + l / 2]) { swap = true; break; }
    }
 
    if (swap) {
        for (int i = 0; i < l / 2; ++i) {
            char tmp = a[s + i];
            a[s + i] = a[s + i + l / 2];
            a[s + i + l / 2] = tmp;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    string a, b;
    cin >> a >> b;
    
    lexosort(a, 0, a.length());
    lexosort(b, 0, b.length());
    
    cout << (a == b ? "YES" : "NO") << endl;
       
    return 0;
}

