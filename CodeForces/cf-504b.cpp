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

const int INF = 2000000000;	                 // 9
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
	vi p1(n, -1), p2(n, -1);
	for (int i = 0; i < n; ++i) { cin >> p1[i]; }
	for (int i = 0; i < n; ++i) { cin >> p2[i]; }
	bool sw = false;
	for (int i = 0; i < n; ++i) { 
		if (p1[i] == p2[i]) continue;
		if (p1[i] > p2[i]) sw = true;
		break;
	}
	if (sw) for (int i = 0; i < n; ++i) swap(p1[i], p2[i]);

	vi po(n, -1);
	for (int i = 0; i < n; ++i) po[p2[p1[i]]] = i;

	for (int i = 0; i < n; ++i) cout << po[i] << " \n"[i == n - 1];
	cout << flush;

	return 0;
}
