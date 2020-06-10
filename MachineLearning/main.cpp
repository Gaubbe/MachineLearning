#include "src/maths/Matrix.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>

int main()
{
	maths::Matrix a(1000, 1000);
	maths::Matrix b(1000, 1000);

	srand(time(NULL));

	for (int i = 0; i < 1000 * 1000; i++) {
		a.mElements[i] = ((double) rand() / (double) INT_MAX)*1000;
		b.mElements[i] = ((double) rand() / (double) INT_MAX)*1000;
	}

	auto start = std::chrono::high_resolution_clock::now();
	maths::Matrix c = a ^ b;
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	return 0;
}