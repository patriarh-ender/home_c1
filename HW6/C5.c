#include <stdio.h>
int gaus(int);
int main()
{
	int a;
	scanf ("%d", &a);
	if (a==0)
	goto END;
	
	printf ("%d",  gaus(a));
END:	
return 0;
}
int gaus (int a)
{
	int sum=0;
	sum=(a*(a+1))/2;
	return sum;
}
