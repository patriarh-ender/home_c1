#include <stdio.h>

int main()
{	
	int a, b, c, r, max;
	scanf ("%d", &a);
	b = a%10; 
	c =  (a/10)%10; 
	r =  (a/100)%10;
	max = b > c ? b : c;
	max = max> r ? max: r;
	printf("%d", max);
	return 0;
	}
