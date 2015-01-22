#include<iostream>

using namespace std;

int factorial[11];

// Gives the number of permutations of a set of 10 digits given their respective frequencies.
long long indistFactorial(int count[10]){
	int den = 1;

	for (int i = 0; i < 10; i++){
		den *= factorial[count[i]];
	}

	return factorial[10] / den;
}

// Same as above, but allows for skewing the factorial.
long long skewedIndistFactorial(int count[10], int sk1, int sk2){
	int den = 1;

	for (int i = 0; i < 10; i++){
		den *= factorial[count[i]];
	}

	return sk1 * factorial[sk2] / den;
}

// Returns the number of valid permutations of the digits given (i.e. arrangements with no leading zeroes).
long long validPermutations(int count[2][10]){
	if (count[0][0] == 0)
		return indistFactorial(count[0]) * indistFactorial(count[1]);
	else if (count[0][0] == 1)
		return skewedIndistFactorial(count[0], 9, 9) * indistFactorial(count[1]);
	else
		return skewedIndistFactorial(count[0], 8, 9) * indistFactorial(count[1]);
}

bool bitIsSet(int var, int pos){
	return (var & (1 << pos));
}

int main(){

	// Some precomputation
	factorial[0] = factorial[1] = 1;
	for (int i = 2; i <= 10; i++)
		factorial[i] = i * factorial[i - 1];
	
	// Holds the frequency of each digit in each subset.
	int count[2][10];
	fill_n(count[0], 10, 0);
	fill_n(count[1], 10, 0);

	// Iterate over all bitmasks
	long long total = 0;
	for (int mask = 0; mask < (1 << 20); mask++){
		// Only accept bitmasks that induce an even partition
		if (__popcnt(mask) != 10) continue;

		// Calculate the alternating sum of the digits
		int altsum = 0;
		bool skip = false;
		for (int i = 0; i < 10; i++){
			// Check in which subset each of the i's belongs
			bool b1 = bitIsSet(mask, 2 * i),
				b2 = bitIsSet(mask, 2 * i + 1);

			// Add it to the alternating sum and record it
			altsum += i * (b1 ? 1 : -1)
					+ i * (b2 ? 1 : -1);
			count[b1 ? 0 : 1][i]++;
			count[b2 ? 0 : 1][i]++;

			// Check if the bitmask is still valid
			skip = skip || (b2 && !b1);
		}
				
		// If the resulting number is divisible by 11 and the bitmask was valid, count it.
		if (abs(altsum) % 11 == 0 && !skip){
			total += validPermutations(count);
		}

		// Reset the arrays
		fill_n(count[0], 10, 0);
		fill_n(count[1], 10, 0);
	}

	// Output!
	cout << "There are " << total << " double pandigital numbers divisible by 11." << endl;
}