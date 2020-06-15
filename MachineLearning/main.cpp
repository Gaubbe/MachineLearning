#include "src/maths/Matrix.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>

int main()
{
	maths::Matrix a(3, 3);
	maths::Matrix b(3, 3);

	srand(time(NULL));

	for (int i = 0; i < 3 * 3; i++) {
		a.mElements[i] = i;
		b.mElements[i] = i;
	}

	auto start = std::chrono::high_resolution_clock::now();
	maths::Matrix c = a ^ b;
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
	for (int i = 0; i < 9; i++)
		std::cout << c.mElements[i] << std::endl;
	return 0;
}