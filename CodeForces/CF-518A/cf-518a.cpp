#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {

	string s, t;
	cin >> s >> t;

	// Create the lexicographically next string (after s).
	string out;
	bool madeswitch = false;
	for (int i = s.length() - 1; i >= 0; --i) {
		char sat = s.at(i), tat = t.at(i);
		if (sat != 'z' && !madeswitch) {
			out = (char)(1 + (int)sat) + out;
			madeswitch = true;
		}
		else if (sat == 'z' && !madeswitch)
			out = 'a' + out;
		else out = sat + out;
	}
	
	// Check if out equals t
	bool idc = true;
	for (int i = 0; i < t.length(); ++i)
		idc = idc && (t.at(i) == out.at(i));

	if (idc)
		cout << "No such string" << endl;
	else cout << out;

	return 0;
}