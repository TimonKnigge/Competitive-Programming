#include<iostream>
#include<string>
#include<stack>

using namespace std;

const bool CURVE_OPEN = false, SQUARE_OPEN = true;

int main(){

	int T;
	cin >> T;
	while (T-- > 0){

		stack<bool> st;
		string in;
		cin >> in;

		bool valid = true;

		for (auto i = in.begin(); i < in.end(); i++){
			if ((*i) == '(')
				st.push(CURVE_OPEN);
			else if ((*i) == '[')
				st.push(SQUARE_OPEN);
			else if ((*i) == ')'){
				if (st.size() > 0 && st.top() == CURVE_OPEN)
					st.pop();
				else{
					valid = false;
					break;
				}
			}
			else{
				if (st.size() > 0 && st.top() == SQUARE_OPEN)
					st.pop();
				else{
					valid = false;
					break;
				}
			}
		}

		cout << (valid ? "Yes" : "No") << endl;

	}

	return 0;
}