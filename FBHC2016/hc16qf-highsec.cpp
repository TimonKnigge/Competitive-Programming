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

constexpr int NN = 0, NF = 1, FN = 2, FF = 3, FC = 4, CF = 5, CN = 6, NC = 7, CC = 8, AF = 9;

bool is(char c1, char c2, char c3, char c4) {
	return c1 == c3 && c2 == c4;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		int N;
		string G[2];
		cin >> N >> G[0] >> G[1];
		cout << "Case #" << t <<": ";

		int ans = 0;
		
		int status = NN;
		for (int i = 0; i < N; ++i) {
			// Gigantic FINITE STATE MACHINE
			int nstatus = status;
			if (is(G[0][i], G[1][i], 'X', 'X')) {
				nstatus = NN;
			} else if (is(G[0][i], G[1][i], 'X', '.')) {
				switch (status) {
					case NN:
					case FN:
					case CN:
						nstatus = NF;
						ans++;
						break;
					case NF:
					case FF:
					case CF:
						nstatus = NF;
						break;
					case NC:
					case CC:
					case FC:
					case AF:
						nstatus = NC;
						break;
					default:
						cerr << "NON-EXHAUSTIVE PATTERNS" << endl;
						break;
				}
			} else if (is(G[0][i], G[1][i], '.', 'X')) {
				switch (status) {
					case NN:
					case NF:
					case NC:
						nstatus = FN;
						ans++;
						break;
					case FN:
					case FF:
					case FC:
						nstatus = FN;
						break;
					case CN:
					case CC:
					case CF:
					case AF:
						nstatus = CN;
						break;
					default:
						cerr << "NON-EXHAUSTIVE PATTERNS" << endl;
				}
			} else if (is(G[0][i], G[1][i], '.', '.')) {
				switch (status) {
					case NN:
						nstatus = AF;
						ans++;
						break;
					case NF:
						nstatus = NC;
						break;
					case FN:
						nstatus = CN;
						break;
					case FF:
					case FC:
					case CF:
					case CC:
						// status does not change
						break;
					case CN:
						nstatus = CF;
						ans++;
						break;
					case NC:
						nstatus = FC;
						ans++;
						break;
					case AF:
						nstatus = FF;
						ans++;
						break;
				}
			}
			status = nstatus;
		}
		
		cout << ans;
		cout << '\n';
	}
	cout << flush;
	
	return 0;
}
