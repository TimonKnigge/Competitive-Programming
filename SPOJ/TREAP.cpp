#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

typedef long long ll;
const ll LLINF = 2e16, LLBOUND = 2e15;

struct Node {
	ll val, mx, mn, mdiff;
	int size, priority;
	Node *l, *r;
	Node(ll _val) : val(_val), mx(_val), mn(_val), mdiff(LLINF), size(1) {
		priority = rand();
	}
};

int size(Node *p) { return p == NULL ? 0 : p->size; }
ll getmax(Node *p) { return p == NULL ? -LLINF : p->mx; }
ll getmin(Node *p) { return p == NULL ? LLINF : p->mn; }
ll getmdiff(Node *p) { return p == NULL ? LLINF : p->mdiff; }
void update(Node *p) {
	if (p == NULL) return;
	p->size = 1 + size(p->l) + size(p->r);
	p->mx = max(p->val, max(getmax(p->l), getmax(p->r)));
	p->mn = min(p->val, min(getmin(p->l), getmin(p->r)));
	p->mdiff = LLINF;
	if (p->l != NULL)
		p->mdiff = min(p->mdiff, min(getmdiff(p->l), p->val - getmax(p->l)));
	if (p->r != NULL)
		p->mdiff = min(p->mdiff, min(getmdiff(p->r), getmin(p->r) - p->val));
}
void merge(Node *&t, Node *l, Node *r) {
	if (l == NULL)      { t = r; }
	else if (r == NULL) { t = l; }
	else if (l->priority > r->priority) {
		merge(l->r, l->r, r);
		t = l;
	} else {
		merge(r->l, l, r->l);
		t = r;
	}
	update(t);
}
void splitat(Node *t, Node *&l, Node *&r, int at) {
	if (t == NULL) { l = r = NULL; return; }
	int id = size(t->l);
	if (id > at) {
		splitat(t->l, l, t->l, at); 
		r = t;
	} else {
		splitat(t->r, t->r, r, at - id - 1);
		l = t;
	}
	update(t);
}
ll Nquery(Node *t, int i, int j) {
	Node *l, *r;
	splitat(t, l, t, i - 1);
	splitat(t, t, r, j - i);
	ll ret = getmdiff(t);
	merge(t, l, t);
	merge(t, t, r);
	return (ret <= 0 || ret > LLBOUND ? -1 : ret);
}
ll Xquery(Node *t, int i, int j) {
	Node *l, *r;
	splitat(t, l, t, i - 1);
	splitat(t, t, r, j - i);
	ll ret = getmax(t) - getmin(t);
	merge(t, l, t);
	merge(t, t, r);
	return (ret <= 0 || ret > LLBOUND ? -1 : ret);
}
void split(Node *t, Node *&l, Node *&r, ll val) {
	if (t == NULL) { l = r = NULL; return; }
	if (t->val >= val) {
		split(t->l, l, t->l, val);
		r = t;
	} else {
		split(t->r, t->r, r, val);
		l = t;
	}
	update(t);
}
void insert(Node *&t, ll val) {
	Node *n = new Node(val), *l, *r;
	split(t, l, t, val);
	split(t, t, r, val + 1);
	merge(t, l, n);
	merge(t, t, r);
}
void erase(Node *&t, ll val, bool del = true) {
	Node *L, *rm;
	split(t, t, L, val);
	split(L, rm, L, val + 1);
	merge(t, t, L);
	if (del && rm != NULL) delete rm;
}
void inorder(Node *p) {
	if (p == NULL) return;
	inorder(p->l);
	cout << p->val << ' ';
	inorder(p->r);
}
void cleanup(Node *p) {
	if (p == NULL) return;
	cleanup(p->l); cleanup(p->r);
	delete p;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	Node *tree = NULL;
	
	srand(time(NULL));
	
	int Q;
	cin >> Q;
	for (int q = 1; q <= Q; ++q) {
		char c;
		cin >> c;
		switch (c) {
			case 'I':
				ll k;
				cin >> k;
				insert(tree, k);
				break;
			case 'D':
				ll kd;
				cin >> kd;
				erase(tree, kd);
				break;
			case 'X':
				int l, r;
				cin >> l >> r;
				if (r - l < 1) cout << -1 << '\n';
				else cout << Xquery(tree, l, r) << '\n';
				break;
			case 'N':
				int ll, rr;
				cin >> ll >> rr;
				if (rr - ll < 1) cout << -1 << '\n';
				else cout << Nquery(tree, ll, rr) << '\n';
				break;
		}
//		cout << "   ";
//		inorder(tree); cout << endl;
	}
	cout << flush;
	cleanup(tree);
	
	return 0;
}

