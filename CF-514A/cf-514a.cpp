#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

#ifdef _MSC_VER
#define scanf scanf_s
#endif

char mp(char c) {
	return (char)('9' - (c - '0'));
}

int main() {

	char c;
	string in;
	cin >> in;
	for(int i = 0; i < in.length(); ++i) {
		c = in.at(i);
		char d = mp(c);
		if (c < d)
			cout << c;
		else if (i == 0 && d == '0')
			cout << c;
		else
			cout << d;
	}
	cout << endl;

	return 0;
}