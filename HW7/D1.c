#include <stdio.h>
void rec (int a)
{	
	
	if(a>1)		
		 rec(a-1);
	printf("%5d",a);	
	
	
}

int main()
{
	int a;
	scanf("%d", &a);
	rec (a);
	return 0;
}

