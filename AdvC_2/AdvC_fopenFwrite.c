#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

float data[10];

struct person{
	char name[10];
	int age;
};
struct person x;

int main(){

if(fwrite(&data[3],sizeof(float),f,fp)!=4) perror("cannot write");

if(fwrite(&x,sizeof(x),1,fp)!=1) perror("cannot write");

exit(0);
}