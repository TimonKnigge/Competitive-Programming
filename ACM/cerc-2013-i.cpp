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

struct Node {
	ll val, mx;
	int size, priority;
	bool rev = false;
	Node *l = NULL, *r = NULL, *par = NULL; 
	Node(ll _val) : val(_val), mx(_val), size(1) { priority = rand(); }
};
int size(Node *p) { return p == NULL ? 0 : p->size; }
ll getmax(Node *p) { return p == NULL ? -LLINF : p->mx; }
void setparent(Node *p, Node *par) { if (p != NULL) p->par = par; }
bool ischild(Node *p, Node *c) {
	if (c == NULL || p == NULL) return false;
	return (p->l == c || p->r == c);
}
int index(Node *n) {
	int ret = size(n->l);
	while (ischild(n->par, n)) {
		if (n->par->r == n)
			ret += size(n->par->l) + 1;
		n = n->par;
	}
	return ret;
}
void update(Node *p) {
	if (p == NULL) return;
	p->size = 1 + size(p->l) + size(p->r);
	p->mx = max(p->val, max(getmax(p->l), getmax(p->r)));
	setparent(p->l, p);
	setparent(p->r, p);
}
void propagate(Node *p) {
	if (p == NULL || !p->rev) return;
	swap(p->l, p->r);
	if (p->l != NULL) p->l->rev ^= true;
	if (p->r != NULL) p->r->rev ^= true;
	p->rev = false;
}
void merge(Node *&t, Node *l, Node *r) {
	propagate(l); propagate(r);
	if (l == NULL)      { t = r; }
	else if (r == NULL) { t = l; }
	else if (l->priority > r->priority) {
		merge(l->r, l->r, r); t = l; }
	else { merge(r->l, l, r->l); t = r; }
	update(t);
}
void split(Node *t, Node *&l, Node *&r, int at) {
	propagate(t);
	if (t == NULL) { l = r = NULL; return; }
	int id = size(t->l) + 1;
	if (id > at) { split(t->l, l, t->l, at); r = t; }
	else { split(t->r, t->r, r, at - id); l = t; }
	update(t);
}
void insert(Node *&t, ll val, int pos) {
	propagate(t);
	Node *n = new Node(val), *l, *r;
	split(t, l, r, pos);
	merge(t, l, n);
	merge(t, t, r);
}
void erase(Node *&t, int pos, bool del = true) {
	propagate(t);
	Node *L, *rm;
	split(t, t, L, pos);
	split(L, rm, L, 1);
	merge(t, t, L);
	if (del && rm != NULL) delete rm;
}
void reverse(Node *t, int l, int r) {
	propagate(t);
	Node *L, *R;
	split(t, t, L, l);
	split(L, L, R, r - l + 1);
	if (L != NULL) L->rev = true;
	merge(t, t, L);
	merge(t, t, R);
}
ll at(Node *t, int pos) {
	propagate(t);
	int id = size(t->l);
	if (pos == id) return t->val;
	else if (pos > id) return at(t->r, pos - id - 1);
	else return at(t->l, pos);
}
ll range_maximum(Node *t, int l, int r) {
	propagate(t);
	Node *L, *R;
	split(t, t, L, l);
	split(L, L, R, r - l + 1);
	ll ret = getmax(L);
	merge(t, t, L);
	merge(t, t, R);
	return ret;
}
void cleanup(Node *p) {
	if (p == NULL) return;
	cleanup(p->l); cleanup(p->r);
	delete p;
}
void debugprint(Node *p) {
	if (p == NULL) return;
	debugprint(p->l);
	cerr << p->val << ' ';
	debugprint(p->r);
}

//	bool ischild(Node *p, Node *c)
//	int index(Node *n)
	

void solve() {
	int N;
	scanf("%d", &N);
	vector<int> P(N, 0);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &P[i]);
		--P[i];
	}
	
	vector<Node*> node(N, NULL);
	Node *tree = NULL, *tmp = NULL, *tmp2 = NULL, *tmp3 = NULL;
	for (int i = 0; i < N; ++i) {
		node[P[i]] = new Node(P[i]);
		merge(tmp, tree, node[P[i]]);
		tree = tmp;
	}
	
	vector<pair<int, int> > swaps;
	for (int i = 0; i < N; ++i) {
//		cerr << "Start placing " << i << " at " << index(node[i]) << endl;
//		debugprint(tree); cerr << endl;
		int p = index(node[i]);
		if (p - i > (N - i) / 2) {
			int l = ((N - i) % 2 == 0 ? i : i + 1);
			int r = N - 1;
			swaps.push_back({l, r});
			split(tree, tmp2, tree, l);
			split(tree, tree, tmp, (r-l+1) / 2);
			split(tmp, tmp, tmp3, r - l + 1 - (r-l+1)/2);
			merge(tmp, tmp2, tmp);
			merge(tree, tmp, tree);
			merge(tree, tree, tmp3);
			tmp = tmp2 = tmp3 = NULL;
//			cerr << "Swapped [" << l << ", " << r << "]: ";
//			debugprint(tree);
//			cerr << endl;
		}
		p = index(node[i]);
		if (p != i) {
			int l = i;
			int r = p + (p-i-1);
			swaps.push_back({l, r});
			split(tree, tmp2, tree, l);
			split(tree, tree, tmp, (r-l+1) / 2);
			split(tmp, tmp, tmp3, r - l + 1 - (r-l+1)/2);
			merge(tmp, tmp2, tmp);
			merge(tree, tmp, tree);
			merge(tree, tree, tmp3);
			tmp = tmp2 = tmp3 = NULL;
//			cerr << "Swapped [" << l << ", " << r << "]: ";
//			debugprint(tree);
//			cerr << endl;
		}
	}
	
	cleanup(tree);
	
	cout << swaps.size() << endl;
	for (size_t i = 0; i < swaps.size(); ++i)
		cout << 1+swaps[i].first << ' ' << 1+swaps[i].second << '\n';
}

int main() {
	
	int T;
	scanf("%d", &T);
	while (T--) solve();
	
	return 0;
}
