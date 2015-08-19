#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	vector<int> depth(N + 2, -1);
	set<int> st;
	long long C = 0;
	for (int i = 0; i < N; ++i) {
		int x;
		cin >> x;
		auto it2 = st.lower_bound(x);
		depth[x] = 0;
		if (it2 != st.end())
			depth[x] = max(depth[x], 1 + depth[*it2]);
		if (st.size() > 0 && it2 != st.begin()) {
			it2--;
			depth[x] = max(depth[x], 1 + depth[*it2]);
		}
		
		C += (long long)depth[x];
		cout << C << '\n';
		
		st.insert(x);
	}
	cout << flush;
	
	return 0;
}
