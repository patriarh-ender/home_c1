#include <stdio.h>
int rec (int a)
{	
	//~ int n=1;
	if(a>0)		
		return a + rec(a - 1);
//~ return rec(a-1);
	else
		return 0;	
	
	
}

int main()
{
	int a;
	scanf("%d", &a);
	rec (a);
	printf ("%d", rec(a));
	return 0;
}

