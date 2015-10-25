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


class UnionFind {
private:
	vi par, rank, size; int c;
public:
	UnionFind(int n) : par(n), rank(n,0), size(n,1), c(n) {
		for (int i = 0; i < n; ++i) par[i] = i;
	}

	int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
	bool same(int i, int j) { return find(i) == find(j); }
	int get_size(int i) { return size[find(i)]; }
	int count() { return c; }

	void union_set(int i, int j) {
		if ((i = find(i)) == (j = find(j))) return;
		c--;
		if (rank[i] > rank[j]) swap(i, j);
		par[i] = j; size[j] += size[i];
		if (rank[i] == rank[j]) rank[j]++;
	}
};

struct tile {
	ll X, Y, W, H;
	tile() : X(0), Y(0), W(0), H(0) { };
	bool operator<(const tile &r) const {
		if (X == r.X) return Y < r.Y;
		return X < r.X;
	}
};

struct T {
	ll ex;
	int ix;
	set<pair<ll, int> >::iterator it;
	T(ll ex, int ix, set<pair<ll, int> >::iterator it)
		: ex(ex), ix(ix), it(it) { };
	bool operator<(const T &r) const {
		return ex > r.ex;
	}
};

int main() {
	
	int N;
	scanf("%d", &N);
	
	vector<tile> tiles(N, tile());
	for (int i = 0; i < N; ++i) {
		int _X, _Y, _W, _H;
		scanf("%d %d %d %d", &_X, &_Y, &_W, &_H);
		tiles[i].X = _X;
		tiles[i].Y = _Y;
		tiles[i].W = _W;
		tiles[i].H = _H;
	}
	
	sort(tiles.begin(), tiles.end());
	
	vector<ll> area(N, 0);
	for (int i = 0; i < N; ++i) {
		area[i] = tiles[i].W * tiles[i].H;
//		cerr << i <<  "(X=" << tiles[i].X << " Y=" << tiles[i].Y << " W=" << tiles[i].W << " H=" << tiles[i].H << ")" << endl;
	}
	
	UnionFind uf(N);
	set<pair<ll, int> > st;
	// {Exit time, {index, set iterator}}
	priority_queue<T> pq;
	for (int i = 0; i < N; ++i) {
//	cerr << "Round " << i << endl;
		while (!pq.empty() && pq.top().ex < tiles[i].X) {
			st.erase(pq.top().it);
//			cerr << "Erasing "<<pq.top().it->second<< " on turn of " << i << endl;
//			cerr << pq.top().ex << ' ' << tiles[i].X<<endl;
			
			pq.pop();
		}

		// Union the new square
		ll x1 = tiles[i].X, y1 = tiles[i].Y;
		ll x2 = x1+tiles[i].W, y2 = tiles[i].H+y1;
		
		auto it = st.lower_bound({y1, -INF});
		while (it != st.end() && it->first - tiles[it->second].H <= y2) {
//			cerr<<"Considering " << it->second << " from " << i << endl;
			// Union it->second and i
			if (!uf.same(it->second, i) /*
			&& ((it->first > y1 && it->first - tiles[it->second].H < y2) ||
			(tiles[it->second].X + tiles[it->second].W > x1 
			&& (it->first == y1 || it->first - tiles[it->second].H == y2)))*/) {
				ll newar = area[uf.find(i)] + area[uf.find(it->second)];
				uf.union_set(i, it->second);
				area[uf.find(i)] = newar;
//				cerr << "Unioning " << i << ' ' << it->second<<endl;
			}
			
			it++;
		}
		
		set<pair<ll, int> >::iterator it2 = st.insert({y2, i}).first;
		pq.push(T(x2, i, it2));
		
//		cerr<< "Current ordering: "<<endl;:wq

//		for (auto it : st) cerr << it.first << ' ' << it.second << ", ";
//		cerr<<endl;
	}
	
	ll best = 0LL;
	for (int i = 0; i < N; ++i) {
		if (area[i] > best) best = area[i];
//		cerr << i << ' '<< area[i] << endl;
	}
	
	cout << best << endl;
	
	return 0;
}
