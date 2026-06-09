#include <stdio.h>

int abs (int n)
{ 
	return (n<0)?-n:n;
		 
} 
int power (int n, int p)
{	if (p==0){
		return n=1; }
	
	int a = n;
	for (int i=1; i!=p; i++)
	{
		a=a*n;
	}
	n = a;
return n;	
}
int main (void)
{ 
	int n, p;
	scanf("%d%d", &n, &p);
	if (p<0 || abs(n)>=1000 || p >=1000)
	{
		return 0;}
	printf ("%d", power(n, p));
		return 0;
	
}
