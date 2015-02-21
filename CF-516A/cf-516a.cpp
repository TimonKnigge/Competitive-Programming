#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <string>
#include <algorithm>

using namespace std;

int main() {

	vector<int> out;
	int n; cin >> n;

	for (int i = 0; i < n; ++i) {
		char c; cin >> c;

		switch (c) {
		case '2':
			out.push_back(2);
			break;
		case '3':
			out.push_back(3);
			break;
		case '4':
			out.push_back(3);
			out.push_back(2);
			out.push_back(2);
			break;
		case '5':
			out.push_back(5);
			break;
		case '6':
			out.push_back(5);
			out.push_back(3);
			break;
		case '7':
			out.push_back(7);
			break;
		case '8':
			out.push_back(7);
			out.push_back(2);
			out.push_back(2);
			out.push_back(2);
			break;
		case '9':
			out.push_back(7);
			out.push_back(2);
			out.push_back(3);
			out.push_back(3);
			break;
		}
	}

	sort(out.begin(), out.end());
	for (int i = 0; i < out.size(); ++i) {
		cout << out[out.size() - 1 - i];
	}
	cout << endl;

	return 0;
}