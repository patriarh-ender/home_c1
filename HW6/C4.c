
#include <stdio.h>

int funx(int x)
{ 	
	int i=0;
	if (x>=-20 && x<2) 
		i=x*x;
	if (x>=2) 
		i=x*x+4*x+5;
	if (x<-2)
		  i=4;
	return i; 
	
}

int main (void)
{
	int a=1, b, c=0;
	
	while (a!=0)
		{
			scanf ("%d", &a);
			b=funx(a);
			if (b>c)
			c=b;	
		}
	printf ("%d", c);
	return 0;
}
