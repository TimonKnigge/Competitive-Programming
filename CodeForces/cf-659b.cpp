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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M;
	cin >> N >> M;
	
	vector<string> name(N, "");
	vvii pointregion(M, vii());
	for (int i = 0; i < N; ++i) {
		cin >> name[i];
		
		int r, p;
		cin >> r >> p;
		
		pointregion[r - 1].push_back({p, i});
	}
	
	for (int r = 0; r < M; ++r) {
		sort(pointregion[r].rbegin(), pointregion[r].rend());
		
		if (pointregion[r].size() > 2 &&
			pointregion[r][1].first == pointregion[r][2].first)
			cout << "?\n";
		else cout << name[pointregion[r][0].second] << " "
			<< name[pointregion[r][1].second] << '\n';
	}
	
	return 0;
}
