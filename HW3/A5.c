#include <stdio.h>

int main(void)
{	
	int a, b, c;
	float x;
	scanf ("%d%d%d", &a, &b, &c);
	x=(float)(a+b+c)/3;
	
	printf ("%.2f", x);
	
	
	return 0;
}

