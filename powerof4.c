/*find out whether a given number is a power of 4 w/o using division or mode */
#include <stdio.h>
int main()
{
	int a,b=1;
	scanf("%d",&a);
	while(b!=0 && a > 0)
{
	if((a|b)==b){
		printf("y\n");
		return 0;}
	b<<=2;
}
	printf("n\n");	
	return 0;
}

