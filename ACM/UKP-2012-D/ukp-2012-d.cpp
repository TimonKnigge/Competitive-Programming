#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

typedef pair<int, int> ii;

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {

		string inp;
		cin >> inp;
		
		vector<vector<ii>> dp(inp.length(), vector<ii>(4, ii(-1, -1)));

		// preprocess the first two layers
		for (int bs = 0; bs < 4; ++bs) {
			bool match = ((bs & 1) ^ (inp.at(0) == '0'));
			if (match || (inp.at(0) == '.'))
				dp[0][bs] = ii(1 - (bs & 1), bs & 1);
		}
		for (int bs = 0; bs < 4; ++bs) {

		}
	}


	return 0;
}