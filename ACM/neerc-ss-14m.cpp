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

void errr(int l1, int p1, int l2, int p2, char c) {
	cout << l1 << ":" << p1 << ": warning: ";
	cout << "shadowed declaration of " << c;
	cout << ", the shadowed position is ";
	cout << l2 << ":" << p2 << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N >> ws;
	
	vector<string> line(N, "");
	for (int i = 0; i < N; ++i)
		getline(cin, line[i]);
	
	vector<vector<pair<int, int> > > mp(26, vector<pair<int, int> >());
	vector<vector<char> > undo(50 * 50 + 3, vector<char>());
	int undo_index = 0;
	
	for (int l = 0; l < N; ++l) {
		string &ln = line[l];
		for (int i = 0; i < ln.length(); ++i) {
			switch (ln[i]) {
			case ' ': break;
			case '{':
				// Introduce a new scope
				undo_index++;
				break;
			case '}':
				// Remove the current scope
				for (char c : undo[undo_index]) {
					mp[c - 'a'].pop_back();
				}
				undo[undo_index].clear();
				undo_index--;
				break;
			default:
				// A letter
				if (mp[ln[i] - 'a'].size() > 0)
					errr(l + 1, i + 1, mp[ln[i] - 'a'].back().first + 1, mp[ln[i] - 'a'].back().second + 1, ln[i]);
				mp[ln[i] - 'a'].push_back({l, i});
				undo[undo_index].push_back(ln[i]);
			}
		}
	}
	
	cout << flush;
	
	return 0;
}
