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

char lc(char c) {
	if (c < 'A' || c > 'Z') return c;
	else return char((c - 'A') + 'a');
}

void to_normal_form(string &in, string &out) {
	string tmp = in;
	
	// lowercase in
	for (size_t i = 0; i < in.size(); ++i)
		tmp[i] = lc(in[i]);
	
	// Is this a bmail.com address?
	// @bmail.com 10 chars
	bool bmail = true;
	if (in.size() < 10) bmail = false;
	else {
		string tmp2 = tmp.substr(tmp.size() - 10);
		bmail = (tmp2 == "@bmail.com");
	}
	
	if (!bmail) out = tmp;
	else {
		bool plus = false;
		size_t i = 0;
		for (; i < tmp.size(); ++i) {
			if (tmp[i] == '@') break;
			if (tmp[i] == '+') { plus = true; }
			if (plus) continue;
			if (tmp[i] != '.') out = out + tmp[i];
		}
		out = out + "@bmail.com";
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vector<string> mail(n, "");
	unordered_map<string, int> idmp;
	vector<vector<int> > lst;
	for (int i = 0; i < n; ++i) {
		cin >> mail[i];
		string tmp;
		to_normal_form(mail[i], tmp);
		
		auto it = idmp.find(tmp);
		if (it == idmp.end()) {
			int id = idmp.size();
			idmp.insert({tmp, id});
			lst.push_back(vector<int>(1, i));
		} else lst[it->second].push_back(i);
	}
	
	cout << lst.size() << '\n';
	for (size_t i = 0; i < lst.size(); ++i) {
		vector<int> &l = lst[i];
		cout << l.size();
		for (size_t j = 0; j < l.size(); ++j)
			cout << " " << mail[l[j]];
		cout << '\n';
	}
	cout << flush;
	
	return 0;
}
