#include <stdio.h>
#include <stdlib.h>

int total;
int count;

main(){
	total=0;
	count=0;
	{
		int count;
		count=5;
		printf("Local count=%d\n",count);		//5


}
	printf("Global count=%d\n",count);		//0
		
}