#include <stdio.h>
#include <stdlib.h>
// Pointer to array 

void func1(int t[])
{
	int i;
	for (i = 0; i < 2; i++)
	{
		t[i + 2] = 0x11;
	}
}

int main()
{
	int a[5] = {7, 4, 9, 11, 8};
	int *p;
	int x, d;

	int i, j;
	int tt[] = {1, 2, 3, 4, 5, 6};
	int ss[2][3] = {{1, 2, 3}, {4, 5, 6}};

	// print array
	printf("a[5]={");
	for (d = 0; d < 5; d++)
	{
		printf("%d", a[d]);
		if (d == 4)
			printf("}\n");
		else
			printf(",");
	} //a[5]={7,4,9,11,8}

	//********************start 1st program********************
	p = &a[0];
	printf("p=&a[0],*p=%d\n", *p); //p=&a[0],*p=7
	p = a;
	printf("p=a,*p=%d\n", *p); //p=a,*p=7
	//name of array also represents pointer to 1st element
	x = *(p + 3);
	printf("x=*(p+3)=%d\n", x); //x=*(p+3)=11
	x = a[3];
	printf("x=a[3]=%d\n", x); //x=a[3]=11

	p = &a[3];
	x = *(p - 1);
	printf("p=&a[3],x=*(p-1)=%d\n", x); //p=&a[3],x=*(p-1)=9
	x = a[2];
	printf("x=a[2]=%d\n", x); //x=a[2]=9
	//offset is available in both pointer and name format

	//********************start 2nd program********************

	printf("\n tt[]={");
	for (j = 0; j < 6; j++)
	{
		printf("%2x", tt[j]);
		if (j == 5)
			printf("}\n");
		else
			printf(",");
	}

	printf("ss[][]={");
	for (i = 0; i < 2; i++)
	{
		printf("{");
		for (j = 0; j < 3; j++)
		{
			printf("%2x", ss[i][j]);
			if (j == 2)
				printf("}");
			else
				printf(",");
		}
		if (i == 2)
			printf("}");
		else
			printf(",");
	}
	printf("}");

	func1(&tt[0]);
	printf("\nFirst printf->");
	for (j = 0; j < 6; j++)
		printf("%2x ", tt[j]);

	func1(&ss[0][0]);
	printf("\nSecond printf->");
	for (i = 0; i < 2; i++)
		for (j = 0; j < 3; j++)
			printf("%2x ", ss[i][j]);

	printf("\nAlt printf->");
	for (j = 0; j < 6; j++)
		printf("%2x ", ss[0][j]);

	printf("\n");
	// how 2d array store in memory
	return (0);
}