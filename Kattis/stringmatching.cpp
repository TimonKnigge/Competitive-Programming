#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>

using namespace std;
typedef vector<int> vi;

#ifndef _MSC_VER
#define scanf_s scanf
#endif

void compute_prefix_function(string& word, vi& pi) {
	pi.assign(word.length(), 0);
	pi[0] = -1; 
	if (word.length() > 1) pi[1] = 0;
	int i = 2, k = 0;

	while (i < pi.size()) {
		if (word[i - 1] == word[k]) {
			pi[i++] = ++k;
		}
		else if (k > 0) k = pi[k];
		else { pi[i++] = 0; }
	}
}

void knuth_morris_pratt(string& sentence, string& word, vi& matches) {
	int q = -1; vi pi;
	compute_prefix_function(word, pi);
	for (int i = 0; i < sentence.length(); ++i) {
		while (q >= 0 && word[q + 1] != sentence[i]) q = pi[q];
		if (word[q + 1] == sentence[i]) q++;
		if (q == word.length() - 1) {
			matches.push_back(i - word.length() + 1);
			q = pi[q];
		}
	}
}

int main() {
	string p, s;
	while (getline(cin, p)) {
		getline(cin, s);
		if (p.length() * s.length() < 1) break;
		vi matches;
		knuth_morris_pratt(s, p, matches);
		for (int i = 0; i < matches.size(); ++i)
			cout << matches[i] << ' ';
		cout << endl;
	}
	return 0;
}