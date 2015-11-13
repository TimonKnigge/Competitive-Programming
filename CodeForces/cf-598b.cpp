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
	char val;
	int size, priority;
	Node *l = NULL, *r = NULL;
	Node(char _val) : val(_val), size(1) { priority = rand(); }
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
void insert(Node *&t, char val, int pos) {
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
char at(Node *t, int pos) {
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
void printtree(Node *t) {
	if (t == NULL) return;
	printtree(t->l);
	cout << t->val;
	printtree(t->r);
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string s;
	cin >> s;
	
	Node *t = NULL;
	for (int i = 0; i < s.size(); ++i)
		insert(t, s[i], i);
	
	int q;
	cin >> q;
	while (q--) {
		int l, r, k;
		cin >> l >> r >> k;
		k %= (r - l + 1);
		if (k == 0) continue;
		
		Node *lt = NULL, *tmp = NULL, *mt = NULL, *rt = NULL;
		split(t, lt, tmp, l - 1);
		split(tmp, mt, rt, r - l + 1);
//		printtree(lt); cout << '-';
//		printtree(mt); cout << '-';
//		printtree(rt); cout << endl;
		
		int len = r - l + 1;
		Node *tmp2 = NULL, *tmp3 = NULL;
		split(mt, tmp2, tmp3, len - k);
		merge(mt, tmp3, tmp2);
		merge(tmp, lt, mt);
		merge(t, tmp, rt);
		
//		printtree(t); cout << endl;
	}
	
	printtree(t);
	cout << endl;
	
	return 0;
}
