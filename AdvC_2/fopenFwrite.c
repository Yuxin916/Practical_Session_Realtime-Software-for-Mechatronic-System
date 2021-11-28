#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Buffered I/O --- Formatted I/O
// create the data file and write array & struct to it

// fopen() -- FILE *fopen(const char *filename, const char *mode)
	// filename − This is the C string containing the name of the file to be opened.
	// mode − This is the C string containing a file access mode.
	// returns a FILE pointer. Otherwise, NULL is returned.

// fwrite() -- size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
	// ptr − pointer to the array of elements to be written.
	// size − size in bytes of each element to be written.
	// nmemb − number of elements, each one with a size of size bytes.
	// stream − pointer to a FILE object that specifies an output stream.
	// returns the number of complete elements successfully written / read
	
FILE *fp;
float data[10];

struct person
{
	char name[10];
	int age;
};
struct person x;

int main()
{

	if ((fp = fopen("datasize.dat", "w")) == NULL)
	{
		perror("cannot open");
		exit(1);
	}

	if (fwrite(&data[3], sizeof(float), 4, fp) != 4)
		perror("cannot write");

	if (fwrite(&x, sizeof(x), 1, fp) != 1)
		perror("cannot write");

	exit(0);
}