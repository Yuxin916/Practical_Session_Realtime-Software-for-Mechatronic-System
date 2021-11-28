#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Buffered I/O
// writes a string to file but not including the null character.

// fopen() -- FILE *fopen(const char *filename, const char *mode)
	// filename − This is the C string containing the name of the file to be opened.
	// mode − This is the C string containing a file access mode.
	// returns a FILE pointer. Otherwise, NULL is returned.
// fputs() -- int fputs(const char *str, FILE *stream)
	// str −- array containing the null-terminated sequence of characters to be written.
	// stream − pointer to a FILE object where the string is to be written.
	// returns a non-negative value, or else on error it returns EOF.

int main()
{
	int i;
	FILE *fp;
	char *str[] = {"one", "two", "three"};

	if ((fp = fopen("doc.dat", "w")) == NULL)
	{
		perror("cannot open");
		exit(1);
	}

	for (i = 0; i < 3; i++)
		if (fputs(str[i], fp) == EOF)
		{
			printf("Cannot write");
			exit(1);
		}
	fclose(fp);
	exit(0);
}