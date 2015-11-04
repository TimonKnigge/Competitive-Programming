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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

void add_number(int x, vector<char> &outp);

// (x-c) + abs(x-c) is 0 for x<=c and 2x-2c for x > c
void add_jump(int c, vector<char> &vec) {
	vec.push_back('(');
	vec.push_back('t');
	vec.push_back('-');
	add_number(c, vec);
	vec.push_back(')');
	vec.push_back('+');
	vec.push_back('a');
	vec.push_back('b');
	vec.push_back('s');
	vec.push_back('(');
	vec.push_back('(');
	vec.push_back('t');
	vec.push_back('-');
	add_number(c, vec);
	vec.push_back(')');
	vec.push_back(')');
}

void add_number(int x, vector<char> &outp) {
	vector<char> st;
	if (x == 0) st.push_back('0');
	while (x > 0) {
		st.push_back('0' + (x%10));
		x /= 10;
	}
	while (st.size() > 0) {
		outp.push_back(st.back());
		st.pop_back();
	}
}

void make_number(int x, vector<char> &outp) {
//	cerr << "asked for "<<x<<endl;
	if (x < 0) {
		outp.push_back('(');
		outp.push_back('0');
		outp.push_back('-');
		make_number(-x, outp);
		outp.push_back(')');
		return;
	}
	if (x == 0) outp.push_back('0');
	else if (x <= 50) {
		add_number(x, outp);
	} else {
		// Decompose into multiples of 50
		outp.push_back('(');
		add_number(x % 50, outp);
		outp.push_back('+');
		outp.push_back('(');
		add_number(50, outp);
		outp.push_back('*');
		make_number(x / 50, outp);
		outp.push_back(')');
		
		outp.push_back(')');
	}
}

void construct(vi &a) {
	int pre = 0;
	vector<char> outp;
	
	int add = 0;
	for (int t = 1; t <= a.size(); ++t) {
		int val = (t > 1 ? a[t - 2] : 0);
		val += add;
		// We want to reach a[t]
		int req = a[t - 1] - val;
		
		if (t > 1) {
			pre++;
			outp.push_back(')');
			outp.push_back('+');
			outp.push_back('(');
		}
//		cerr<<req<<endl;
			
		outp.push_back('(');
		add_jump(t - 1, outp);
		outp.push_back(')');
		
		outp.push_back('*');
		make_number(req / 2, outp);
		a[t - 1] = val + 2 * (req / 2);
		
		if (t > 1) {
			outp.push_back(')');
		}
		
		add += 2 * (req / 2);
	}
	pre++;
	outp.push_back(')');
	
	while (pre--) cout << '(';
	for (size_t i = 0; i < outp.size(); ++i)
		cout << outp[i];
	cout << endl;
}

int main() {
	
	int n;
	scanf("%d", &n);
	
	vi x(n, 0), y(n, 0), r(n, 0);
	for (int i = 0; i < n; ++i) {
		scanf("%d %d %d", &x[i], &y[i], &r[i]);
	}
	
	// Construct the x function
	construct(x);
	construct(y);
	
	return 0;
}
