#include <stdio.h>

int main()
{	
	int a;
	int r;
	scanf ("%d", &a);
	r = a%10; 
	r *=  (a/10)%10; 
	r *=  (a/100)%10;
	printf ("%d", r);
	return 0;
	}
