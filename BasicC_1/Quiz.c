#include <stdio.h>
#include <stdlib.h>

int main(){
	int i,b,a,x;
	
	i=10; 
	printf("i = %d\n",i++);  //10
	
	i=10; 
	printf("i = %d\n",++i); //11
	
	i=(b=1+2)+4; 
	printf("i = %d\n",i);  //7
	
	i=(3<=8)+4; 
	printf("i = %d\n",i);  //5
	
	i=(1<<1); 
	printf("i = %d\n",i);  //2
	
	a=(x<2)? 5 : 12; 
	printf("a = %d\n",a); // 12			assume x = 2 
	
}