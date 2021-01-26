#include <iostream>
#include "functions.h"
using namespace std;

int main() {
	int a, b, n = 0, digit = 0, numCount = 0, goodVal = 0, range = 0;
	bool doubleDigit = false;
	
	cout << "Enter numbers a <= b: ";
	cin >> a;
	cin >> b;
	
	if (a <= 0 || b < 0) {
		cout << "Invalid input";
	}
	else if ( b < a) {
		cout << "Invalid input";
	}
	else if (b > 10000) {
		cout << "Invalid input";
	}
	else {
		for (int n = a; n <= b; ++n) {
			digit = 0;
			for (int j = 0; j < 10; ++j) {
				int val = countDigitOccurrences(n, digit);
				if (val > 1) {
					numCount += 1;
					break;
				}
				digit += 1;
			}
		}
		range = b - a;
		range += 1;
		goodVal = range - numCount;
		cout << "There are " << goodVal << " valid numbers between " << a << " and " << b << endl;
	}
	return 0;
}
