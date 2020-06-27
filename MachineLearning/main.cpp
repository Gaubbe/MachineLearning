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

	for (unsigned int i = 0; i < a.GetSize(); i++)
		a.mElements[i] = i;// rand() % 10;

	for (unsigned int i = 0; i < b.GetSize(); i++)
		b.mElements[i] = i;// rand() % 10;

	auto start = std::chrono::high_resolution_clock::now();
	maths::Matrix c = a ^ b;
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	//for (int i = 0; i < c.GetSize(); i++)
	//	std::cout << c.mElements[i] << std::endl;
	return 0;
}