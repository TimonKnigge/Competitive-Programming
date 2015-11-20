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

char hard[8] = {'b', 'c', 'd', 'g', 'k', 'n', 'p', 't'};
char endd[3] = {'a', 'o', 'u'};

void modify(string &in, string &out) {
	bool uc = (in[0] >= 'A' && in[0] <= 'Z');
	if (uc) in[0] = char(int(in[0]) - 'A' + 'a');
	
	// First letter goes to nearest hard consonant
	int nst = 0;
	for (int i = 1; i < 8; ++i) {
		if (abs(in[0] - hard[i]) < abs(in[0] - hard[nst]))
			nst = i;
	}
	in[0] = hard[nst];
	
	out = in[0];
	bool dsh = false;
	for (int i = 1; i < in.size(); ++i) {
		if (in[i] == '-') {
			dsh = true;
			continue;
		}
		if (!dsh) {
			out = out + in[i];
			continue;
		}
		char bp = in[i];
		for (int j = 0; j < 8; ++j) {
			if (bp == hard[j]) bp = hard[nst];
		}
		out = out + bp;
	}
	
	char lst = out[out.size() - 1];
	for (int j = 0; j < 8; ++j) {
		if (hard[j] != lst) continue;
		int bk = 0;
		for (int k = 1; k < 3; ++k) {
			if (abs(lst - endd[k]) < abs(lst - endd[bk]))
				bk = k;
		}
		out = out + endd[bk] + 'h';
		break;
	}
	if (uc) out[0] = char(int(out[0]) - 'a' + 'A');
}

int main() {
	
	string inp, outp;
	bool f = false;
	while (cin >> inp) {
		if (f) cout << " "; else f = true;
		modify(inp, outp);
		cout << outp;
	}
	cout << endl;
	
	return 0;
}
