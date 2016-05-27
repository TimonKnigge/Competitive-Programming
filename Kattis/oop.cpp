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

constexpr int INF = 2000000000;
constexpr ll LLINF = 9000000000000000000;

// 01
// 23
// All points should be within [-B, B] x [-B, B]
template <ll B, int CAP>
struct QuadTree {
	struct node {
		int ch = -1, pc = 0;
		ll x1 = -B, y1 = -B, x2 = B, y2 = B;
		ii pt = {LLINF, LLINF};
	};
	vector<node> tree;
	int T = 0;
	QuadTree() { tree.assign(CAP, node()); make_node(-B, -B, B, B); }
	int make_node(ll x1, ll y1, ll x2, ll y2) {
		tree[T].x1 = x1; tree[T].y1 = y1;
		tree[T].x2 = x2; tree[T].y2 = y2;
		return T++;
	}
	void insert(ii pt, int w, int n = 0) {
		node &nd = tree[n];
		if ((nd.ch < 0 && nd.pt == make_pair(LLINF, LLINF)) || nd.pt == pt) {
			nd.pt = pt;
			nd.pc += w;
			return;
		}
		int xm = (nd.x1+nd.x2) / 2, ym = (nd.y1+nd.y2) / 2;
		if (nd.pt != make_pair(LLINF, LLINF)) {
			nd.ch = make_node(nd.x1, nd.y1, xm,    ym);
			make_node(xm+1,  nd.y1, nd.x2, ym);
			make_node(nd.x1, ym+1,  xm,    nd.y2);
			make_node(xm+1,  ym+1,  nd.x2, nd.y2);
			insert_child(nd.pt, nd.pc, n);
			nd.pt = {LLINF, LLINF};
		}
		insert_child(pt, w, n);
		nd.pc = 0;
		for (int i = 0; i < 4; ++i) nd.pc += tree[nd.ch + i].pc;
	}
	void insert_child(ii pt, int w, int n) {
		node &nd = tree[n];
		if (pt.first <= (nd.x1+nd.x2) / 2)
			if (pt.second <= (nd.y1+nd.y2) / 2)
				insert(pt, w, nd.ch);
			else	insert(pt, w, nd.ch + 2);
		else	if (pt.second <= (nd.y1+nd.y2) / 2)
				insert(pt, w, nd.ch + 1);
			else	insert(pt, w, nd.ch + 3);
	}
	int query(ll x1, ll y1, ll x2, ll y2, int n = 0) {
		node &nd = tree[n];
		if (x1 <= nd.x1 && y1 <= nd.y1 && nd.x2 <= x2 && nd.y2 <= y2)
			return nd.pc;
		if (nd.x2 < x1 || x2 < nd.x1 || nd.y2 < y1 || y2 < nd.y1)
			return 0LL;
		ll ret = 0LL;
		if (nd.ch >= 0)
			for (int i = 0; i < 4; ++i)
				ret += query(x1, y1, x2, y2, nd.ch + i);
		else if (nd.pt != make_pair(LLINF, LLINF))
			if (x1 <= nd.pt.first && nd.pt.first <= x2
			 && y1 <= nd.pt.second && nd.pt.second <= y2)
				ret += nd.pc;
		return ret;
	}
	void print_tree(int n = 0) {
		node &nd = tree[n];
		cerr << n << ": " << nd.x1 << ' ' << nd.y1 << ' ' << nd.x2 << ' ' << nd.y2 << " - " << nd.pc;
		if (nd.ch >= 0) {
			cerr << " - ";
			cerr << nd.ch << ' ' << nd.ch+1 << ' ' << nd.ch+2 << ' '<< nd.ch+3 << endl;
			for (int i = 0; i < 4; ++i) print_tree(nd.ch+i);
		} else cerr << endl;
	}
};

const int ALPHABET_SIZE = 26;
inline int mp(char c) { return c - 'a'; }

struct Node {
	map<int, Node*> ch;
//	Node* ch[ALPHABET_SIZE];
	bool isleaf = false;
	int lc = 0, rc = 0;
	Node() {
//		for(int i = 0; i < ALPHABET_SIZE; ++i) ch[i] = nullptr;
	}
	
	Node *tryfind(int v) {
		auto it = ch.find(v);
		Node *ret = nullptr;
		if (it == ch.end())
			ch.insert({v, ret = new Node()});
		else	ret = it->second;
		return ret;
	}

	void insert(string &s, size_t i = 0) {
		if (i == s.length()) isleaf = true;
		else {
			int v = mp(s[i]);
//			if (ch[v] == nullptr)
//				ch[v] = new Node();
//			ch[v]->insert(s, i + 1);
			tryfind(v)->insert(s, i + 1);
		}
	}
	void rinsert(string &s, int i) {
		if (i == -1) isleaf = true;
		else {
			int v = mp(s[i]);
//			if (ch[v] == nullptr) ch[v] = new Node();
//			ch[v]->rinsert(s, i - 1);
			tryfind(v)->rinsert(s, i - 1);
		}
	}
	
	ii getleaf(string &s, size_t i = 0) {
		if (i == s.length()) return {lc, rc};
		else {
			int v = mp(s[i]);
			auto it = ch.find(v);
			if (it == ch.end()) return {-1, -1};
			else return it->second->getleaf(s, i+1);
//			if (ch[v] == nullptr) return {-1, -1};
//			else return ch[v]->getleaf(s, i + 1);
		}
	}
	
	ii getleaf_r(string &s, int i) {
		if (i == -1) return {lc, rc};
		else {
			int v = mp(s[i]);
			auto it = ch.find(v);
			if (it == ch.end()) return {-1, -1};
			else return it->second->getleaf_r(s, i-1);
//			if (ch[v] == nullptr) return {-1, -1};
//			else return ch[v]->getleaf_r(s, i - 1);
		}
	}
	
	ii getleaf_ast(string &s, size_t i) {
		if (s[i] == '*') return {lc, rc};
		int v = mp(s[i]);
		auto it = ch.find(v);
		if (it == ch.end()) return {-1, -1};
		else return it->second->getleaf_ast(s, i+1);
//		if (ch[v] == nullptr) return {-1, -1};
//		else return ch[v]->getleaf_ast(s, i + 1);
	}
	
	ii getleaf_rast(string &s, size_t i) {
		if (s[i] == '*') return {lc, rc};
		int v = mp(s[i]);
		auto it = ch.find(v);
		if (it == ch.end()) return {-1, -1};
		else return it->second->getleaf_rast(s, i-1);
//		if (ch[v] == nullptr) return {-1, -1};
//		else return ch[v]->getleaf_rast(s, i-1);
	}

	void leaf_fix(int &c) {
		lc = rc = c;
		if (isleaf) rc = ++c;
		for (auto n : ch) {
			n.second->leaf_fix(c);
			rc = max(rc, n.second->rc);
		}
//		for (int i = 0; i < ALPHABET_SIZE; ++i)
//			if (ch[i] != nullptr) {
//				ch[i]->leaf_fix(c);
//				rc = max(rc, ch[i]->rc);
//			}
	}

//	void cleanup() {
//		for (int i = 0; i < ALPHABET_SIZE; ++i)
//			if (ch[i] != nullptr) {
//				ch[i]->cleanup();
//				delete ch[i];
//			}
//	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	QuadTree<100000, 4000100> qt;
	
	int N, Q;
	cin >> N >> Q >> ws;
	
	vector<string> inp(N, "");
	Node *ft = new Node(), *bt = new Node();
	for (int i = 0; i < N; ++i) {
		getline(cin, inp[i]);
		ft->insert(inp[i]);
		bt->rinsert(inp[i], inp[i].length() - 1);
	}
	
	int fc = 0, bc = 0;
	ft->leaf_fix(fc);
	bt->leaf_fix(bc);
	
	vii lr(N, {-1, -1});
	for (int i = 0; i < N; ++i) {
		lr[i].first = ft->getleaf(inp[i], 0).first;
		lr[i].second = bt->getleaf_r(inp[i], inp[i].length()-1).first;
//		cerr << i << ' ' << lr[i].first << ' '<<lr[i].second << endl;
	}
	
	vii bysize;
	for (int i = 0; i < N; ++i) bysize.push_back({inp[i].size(), i});
	sort(bysize.rbegin(), bysize.rend());
	inp.clear();
	
	vector<string> query(Q, "");
	vii qbysize;
	for (int q = 0; q < Q; ++q) {
		getline(cin, query[q]);
		qbysize.push_back({query[q].size(), q});
	}
	sort(qbysize.rbegin(), qbysize.rend());
	vi ans(Q, 0LL);
	
	// Handle queries one by one
	for (int _q = 0, i = 0; _q < Q; ++_q) {
		int q = qbysize[_q].second;
		
		// Insert all strings that are strictly smaller
		while (i < N && bysize[i].first + 1 >= qbysize[_q].first) {
			int s = bysize[i].second;
			qt.insert(lr[s], 1);
			++i;
		}
		
		// Process the query
		ii prefr = ft->getleaf_ast(query[q], 0);
		ii suffr = bt->getleaf_rast(query[q], query[q].length()-1);
		if (prefr.second == -1 || suffr.second == -1) continue;
		
//		cerr << q << "  ";
//		cerr << prefr.first << ' ' <<prefr.second << "  ";
//		cerr << suffr.first << ' ' <<suffr.second << endl;
		--prefr.second;
		--suffr.second;
		
		ans[q] = qt.query(prefr.first, suffr.first, prefr.second, suffr.second);
	}
	
	for (size_t i = 0; i < ans.size(); ++i) cout << ans[i] << '\n';
	
	return 0;
}
