#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <chrono>

using namespace std;
using namespace __gnu_pbds;
using namespace chrono;

typedef long long ll;
using order_tree = tree<int, int, less<int>, rb_tree_tag,
	tree_order_statistics_node_update>;

int main() {
	int N;
	scanf("%d", &N);
	auto beg = high_resolution_clock::now();
	vector<int> el(N, 0);
	vector<pair<int, int>> st(N, {0, 0});
	for (int i = 0; i < N; ++i) {
		scanf("%d", &el[i]);
		st[i] = {i - el[i], -i};
	}
	
	bool sorted = true;
	for (int i = 1; i < N; ++i)
		sorted = sorted && (el[i - 1] < el[i]);
	
	if (sorted) printf("Cool Array\n");
	else {
		int bi = -1, bj = -1, bcount = -1;
		ll C = 0;
		bool cont = true;
		auto ms = milliseconds(1950);
		sort(st.begin(), st.end());
		for (int _j = N - 1; cont && _j >= 0; --_j) {
			int j = -st[_j].second;
			order_tree tr;
			for (int i = j - 1; cont && i >= 0; --i) {
				C++;
				if (((C&63LL)==0)&&
				high_resolution_clock::now()-beg>ms) {
					cont = false; break; }
				if (el[i] < el[j]) continue;
				int tcount = tr.order_of_key(el[i]);
				tr.insert({el[i], el[i]});
				if (tcount > bcount || (tcount == bcount
					&& (i < bi || (i == bi && j < bj)))) {
					bcount = tcount;
					bi = i; bj = j;
				}
			}
		}

		printf("%d %d\n", 1 + bi, 1 + bj);
	}
	
	return 0;
}
