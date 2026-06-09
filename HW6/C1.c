#include <stdio.h>

int abs (int n)
{ 
	return (n<0)?-n:n;		 
} 
	
int main (void)
{
	int n;
	scanf ("%d", &n);
	printf ("%d", abs(n));
	return 0;
}

