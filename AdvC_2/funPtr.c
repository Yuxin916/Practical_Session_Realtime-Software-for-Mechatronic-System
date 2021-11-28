// Pointers to Functions: Key Concepts

// Functions are stored in memory
// Pointers can point to memory location


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

	int (*p)(int, int);		
	// takes two arguments and returns an integer

	int add(int x, int y)
	{
		return x + y;
	}

	int sub(int x, int y)
	{
		return x - y;
	}

	p = add;
	printf("%d\n", (*p)(2, 3));		//5

	p = sub;
	printf("%d\n", (*p)(2, 3));		//-1

	exit(0);
}