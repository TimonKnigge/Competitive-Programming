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
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

ll poly(char a, char b, char c) {
	return (a - 'A')
		+ (b - 'A') * 26
		+ (c - 'A') * 26 * 26;
}

void printfrompoly(ll p) {
	cout << char('A' + p%26);
	p /= 26;
	cout << char('A' + p%26);
	p /= 26;
	cout << char('A' + p%26);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	
	vi op1(N, 0LL), op2(N, 0LL);
	for (int i = 0; i < N; ++i) {
		string a, b;
		cin >> a >> b;
		op1[i] = poly(a[0], a[1], a[2]);
		op2[i] = poly(a[0], a[1], b[0]);
	}
	
	vvi owner(26*26*26, vi());
	for (int i = 0; i < N; ++i)
		owner[op1[i]].push_back(i);
	
	queue<ll> q;
	for (int i = 0; i < 26*26*26; ++i)
		if (owner[i].size() > 1)
			q.push(i);
	
	bool pos = true;
	while (!q.empty() && pos) {
		vi t1, t2;
		ll poly = q.front();
		q.pop();
		if (owner[poly].size() <= 1)
			continue;
		for (ll i : owner[poly])
			if (op2[i] == poly)
				t2.push_back(i);
			else	t1.push_back(i);
		owner[poly].clear();
		if (t2.size() > 1)
			pos = false;
		else if (t2.size() == 1)
			owner[poly].push_back(t2[0]);
		for (ll v : t1) {
			owner[op2[v]].push_back(v);
			if (owner[op2[v]].size() > 1)
				q.push(op2[v]);
		}
	}
	
	if (pos) {
		cout << "YES" << endl;
		vi finalpoly(N, -1LL);
		for (int i = 0; i < 26*26*26; ++i)
			for (ll v : owner[i])
				finalpoly[v] = i;
		for (int i = 0; i < N; ++i) {
			printfrompoly(finalpoly[i]);
			cout << endl;
		}
	} else	cout << "NO" << endl;
	
	return 0;
}
