#include<iostream>
#include<unordered_map>
#include<string>

using namespace std;

int main(){

	int cases;
	cin >> cases;

	while (cases-- > 0){
		int n;
		cin >> n;

		unordered_map<string, int> counts;

		string name, category;

		// count how many different items there are of each category
		while (n--){
			cin >> name >> category;

			if (counts.count(category) > 0)
				counts[category]++;
			else
				counts[category] = 1;
		}

		// Calculate all possible combinations
		int product = 1;
		for (auto i = counts.begin(); i != counts.end(); i++){
			// (+1 because nothing of this category is also an option)
			product *= 1 + (*i).second;
		}

		// -1 because nothing from any category is not an option
		cout << (product - 1) << endl;
	}

	return 0;
}