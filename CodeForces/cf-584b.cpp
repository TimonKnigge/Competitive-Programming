#include <cstdio>
using namespace std;

using ll = long long;

ll modpow(ll a, ll b, ll m) {
  if (b == 0) return 1;
  if (b == 1) return a;
  ll r = modpow((a*a) % m, b / 2, m);
  if (b&1) r = (r * a) % m;
  return r;  
}

int main() {
  int N;
  scanf("%d", &N);
  ll t1 = modpow(27, N, 1e9 + 7);
  ll t2 = modpow(7, N, 1e9 + 7);
  ll o = t1 - t2;
  if (o < 0) o += 1e9 + 7;
  printf("%d\n", int(o));
  return 0;
}
