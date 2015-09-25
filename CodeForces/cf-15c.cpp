#include <cstdio>
using namespace std;
typedef long long ll;

ll f(ll x) {
	switch (x%4) {
		case 0: return 0;
		case 1: return x - 1;
		case 2: return 1;
		default: return x;
	}
}

int main() {
	int n;
	scanf("%d", &n);
	
	ll nimsum = 0LL;
	for (int i = 0; i < n; ++i) {
		ll x, m;
		scanf("%I64d %I64d", &x, &m);
		ll nim = f(x + m) ^ f(x);
		nimsum = nimsum ^ nim;
	}
	
	printf(nimsum != 0 ? "tolik\n" : "bolik\n");
	
	return 0;
}
