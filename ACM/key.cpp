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


struct Node {
	ll val;
	int size, priority;
	Node *l = NULL, *r = NULL;
	Node(ll _val) : val(_val), size(1) { priority = rand(); }
};
int size(Node *p) { return p == NULL ? 0 : p->size; }
void update(Node *p) {
	if (p == NULL) return;
	p->size = 1 + size(p->l) + size(p->r);
}
void merge(Node *&t, Node *l, Node *r) {
	if (l == NULL)      { t = r; }
	else if (r == NULL) { t = l; }
	else if (l->priority > r->priority) {
		merge(l->r, l->r, r); t = l; }
	else { merge(r->l, l, r->l); t = r; }
	update(t);
}
void split(Node *t, Node *&l, Node *&r, int at) {
	if (t == NULL) { l = r = NULL; return; }
	int id = size(t->l) + 1;
	if (id > at) { split(t->l, l, t->l, at); r = t; }
	else { split(t->r, t->r, r, at - id); l = t; }
	update(t);
}
void insert(Node *&t, ll val, int pos) {
	Node *n = new Node(val), *l, *r;
	split(t, l, r, pos);
	merge(t, l, n);
	merge(t, t, r);
}
void erase(Node *&t, int pos, bool del = true) {
	Node *L, *rm;
	split(t, t, L, pos);
	split(L, rm, L, 1);
	merge(t, t, L);
	if (del && rm != NULL) delete rm;
}
ll at(Node *t, int pos) {
	int id = size(t->l);
	if (pos == id) return t->val;
	else if (pos > id) return at(t->r, pos - id - 1);
	else return at(t->l, pos);
}
void cleanup(Node *p) {
	if (p == NULL) return;
	cleanup(p->l); cleanup(p->r);
	delete p;
}
void append(Node *p, vi &v) {
	if (p == NULL) return;
	append(p->l, v);
	v.push_back(p->val);
	append(p->r, v);
}

int main() {
	
	freopen("key.in", "r", stdin);
	freopen("key.out", "w", stdout);
	
	int N, M;
	scanf("%d %d", &N, &M);
	vi rel(N + M + 10, -1);
	vector<Node*> tr(N + M + 10, NULL);
	
	for (int i = 1; i <= N; ++i) {
		int v;
		scanf("%d", &v);
		if (rel[v] == -1) {
			rel[v] = v;
			tr[v] = new Node(i);
			continue;
		}
		int r = rel[v];
		while (r != rel[r]) r = rel[r];
		int rr = v;
//		cerr << "r: " << r << endl;
		while (rr != r) {
			int tmp = rel[rr];
			rel[rr] = r;
			rr = tmp;
		}
		
		// We insert in the segment rooted at position r
		// Insert i into the tree
		insert(tr[r], i, v - r);
		int sz = size(tr[r]) - 1;
		int j = r + sz;
		while (true) {
			if (rel[j] == -1) {
				rel[j] = r;
				break;
			} else {
				sz = size(tr[j]);
				rel[j] = r;
				Node *tmp;
				merge(tmp, tr[r], tr[j]);
				tr[r] = tmp;
				tr[j] = NULL;
				j += sz;
			}
		}
//		for (int a = 0; a < rel.size(); ++a)
//			cerr << rel[a] << ' ';cerr<<endl;
	}
	
	// Print the result
	vi ans;
	for (int i = 0; i < tr.size(); ++i) {
		if (tr[i] == NULL) continue;
		while (ans.size() < i) ans.push_back(0);
		append(tr[i], ans);
//		cerr << "Appended from position " << i << endl;
	}
	cout << ans.size() - 1 << endl;
	for (int i = 1; i < ans.size(); ++i)
		cout << ans[i] << " \n"[i + 1 == ans.size()];
	
	return 0;
}
