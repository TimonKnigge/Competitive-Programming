#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

typedef vector<int> vi;

int successive_difference(int a, int b) {
	return (b - a + 360000) % 360000;
}

void compute_prefix_function(vi& word, vi& pi) {
	pi.assign(word.size(), 0);
	pi[0] = -1;
	if (word.size() > 1) pi[1] = 0;
	int i = 2, k = 0;
	while (i < pi.size()) {
		if (word[i - 1] == word[k]) 
			pi[i++] = ++k;
		else if (k > 0) k = pi[k];
		else pi[i++] = 0;
	}
}

bool kmp(vi& sentence, vi& word) {
	int q = -1; vi pi;
	compute_prefix_function(word, pi);
	for (int i = 0; i < sentence.size(); ++i) {
		while (q >= 0 && word[q + 1] != sentence[i]) q = pi[q];
		if (word[q + 1] == sentence[i]) q++;
		if (q == word.size() - 1) {
			return true;
		}
	}
	return false;
}

int main() {

	// Take input
	int n;
	cin >> n;
	vi h1(n), h2(n);
	for (int i = 0; i < n; ++i) cin >> h1[i];
	for (int i = 0; i < n; ++i) cin >> h2[i];

	sort(h1.begin(), h1.end());
	sort(h2.begin(), h2.end());

	// Construct the pattern and sentence
	vi pat(n), sen(2 * n);
	for (int i = 0; i < n; ++i) pat[i] = successive_difference(h1[i], h1[(i + 1) % n]);
	for (int i = 0; i < n; ++i) 
		sen[i] = sen[i + n] = successive_difference(h2[i], h2[(i + 1) % n]);

	// Match
	cout << (kmp(sen, pat) ? "possible" : "impossible") << endl;

	return 0;
}