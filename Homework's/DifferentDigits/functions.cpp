#include <iostream>
#include "functions.h"
using namespace std;

int countDigitOccurrences(int n, int digit) {
	int numCount = 0;
	while (n > 0) {
		int num = n % 10;
		n = n / 10;
		if (num == digit) {
			numCount += 1;
		}
	}
	return numCount;
}
