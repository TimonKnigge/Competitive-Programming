#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

template<class T>
T sq(T a) { return a * a; }
ll dot(ll x1, ll y1, ll x2, ll y2) {
	return x1 * x2 + y1 * y2;
}


#define MY_PI 3.14159265358979323846
ld pr2(ld r) {
	return MY_PI * r;
}

int main() {
	
	int n, _x, _y;
	scanf("%d %d %d", &n, &_x, &_y);
	
	ll px = _x, py = _y;
	
	vector<ll> X(n, 0), Y(n, 0);
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &_x, &_y);
		X[i] = _x;
		Y[i] = _y;
	}
	
	ld Msq = 0LL, msq = LLINF;
	for (int i = 0; i < n; ++i) {
		Msq = max(Msq, ld(sq(px - X[i]) + sq(py - Y[i])));
		msq = min(msq, ld(sq(px - X[i]) + sq(py - Y[i])));
		if (i > 0) {
			int j = (i + 1) % n;
			if (X[i] == X[j] && Y[i] == Y[j]) continue;
			ld part = ld(dot(X[j]-X[i],Y[j]-Y[i],px-X[i],py-Y[i]))
				/ ld(sq(X[j]-X[i])+sq(Y[j]-Y[i]));
			part = max(ld(0.0), min(ld(1.0), part));
			ld ppx = X[i] + (X[j] - X[i]) * part;
			ld ppy = Y[i] + (Y[j] - Y[i]) * part;
			msq = min(msq, ld(sq(px-ppx)+sq(py-ppy)));
		}
	}
	
	ld ans = pr2(Msq - msq);
	printf("%.8lf\n", double(ans));
	
	return 0;
}
