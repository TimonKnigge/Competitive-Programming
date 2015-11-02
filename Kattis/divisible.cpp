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
#include <unordered_map>
#include <cstring>

using namespace std;
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int cnt[1000000];


void scan(int &x){	// doesn't handle negative numbers
	char c;
	while((x=getchar_unlocked())<'0');
	for(x-='0'; '0'<=(c=getchar_unlocked()); x=10*x+c-'0');
}
void print(ll x){
	char buf[20], *p=buf;
	if(!x) putchar_unlocked('0');
	else{
		while(x) *p++='0'+x%10, x/=10;
		do putchar_unlocked(*--p); while(p!=buf);
	}
}

int c, d, n, x, sum;
ll ans = 0LL;

int main() {
	
	scan(c);
	while (c--) {
		scan(d);
		scan(n);

		// For each position, find out whether it is the end point of a
		// sequence divisible by d.
		memset(cnt, 0, d * sizeof(int));
		ans = 0LL;
		sum = 0;
		
		while (n--) {
			cnt[sum]++;
			scan(x);
			sum = (sum + x) % d;
			ans += cnt[sum];
		}
		print(ans);
		putchar_unlocked('\n');
	}
	
	return 0;
}

