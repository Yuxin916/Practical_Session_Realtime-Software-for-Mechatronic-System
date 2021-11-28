#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Buffered I/O --- Formatted I/O
// create the numbers file and everytime overwrite to it

// fopen() -- FILE *fopen(const char *filename, const char *mode)
	// filename − This is the C string containing the name of the file to be opened.
	// mode − This is the C string containing a file access mode.
	// returns a FILE pointer. Otherwise, NULL is returned.

// fprintf() -- int fprintf(FILE *stream, const char *format, ...)
	// stream − This is the pointer to a FILE object that identifies the stream.
	// format
	// returns the total number of characters written or a negative number is returned.

int main()
{
	FILE *fp;
	int i;

	if ((fp = fopen("numbers", "w")) == NULL)
	{
		perror("cannot open");
		exit(1);
	}

	for (i = 0; i < 10; i++)
		if (fprintf(fp, "%d\n", i) != 2)
		{
			perror("cannot write");
			exit(1);
		}
	fclose(fp);
	exit(0);
}