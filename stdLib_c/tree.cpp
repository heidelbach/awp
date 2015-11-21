#include "node.h"

#include <cstdlib>
#include <iostream>

signed int compare(int const *const a, int const *const b)
{
	return *a - *b;
}

int main()
{
	int a[] = { 10, 12, 11, 13, 14, 16, 17, 15, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 };
	Node<int> *treePtr = Node<int>::create(a, compare);
	for (int i = 1; i < 20; ++i)
	{
		treePtr->add(a + i);
		std::cout << *treePtr << std::endl; 
		treePtr = treePtr->balance();
		std::cout << *treePtr << std::endl;
		system("timeout 2");
	}
	treePtr->free();
	system("timeout 20");
	return EXIT_SUCCESS;
}