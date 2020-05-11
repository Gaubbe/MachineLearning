#include "src/maths/Matrix.h"
#include <iostream>
int main()
{
	maths::Matrix a(2, 2);
	maths::Matrix b(2, 2);
	
	a.m_Elements[0] = 1;
	a.m_Elements[1] = 2;
	a.m_Elements[2] = 3;
	a.m_Elements[3] = 4;

	b.m_Elements[0] = 5;
	b.m_Elements[1] = 6;
	b.m_Elements[2] = 7;
	b.m_Elements[3] = 8;

	maths::Matrix c = *maths::Matrix::transpose(&a);

	std::cout << c.m_Elements[0] << std::endl;
	std::cout << c.m_Elements[1] << std::endl;
	std::cout << c.m_Elements[2] << std::endl;
	std::cout << c.m_Elements[3] << std::endl;

	return 0;
}