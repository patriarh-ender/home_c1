#include <stdio.h>

int main()
{ 	
	int a, e1, e2;
	scanf("%d", &a); 
	if (a<=0){goto END;}
	while (a!=0)
	{
	e1 = a%10;
	e2 = a/10%10;
	a=a/10;
	END:
	if (e1==e2)	{
		printf ("YES"); break;}	
		else if (e1!=e2 && a==0){ 
			printf ("NO"); break;
		}
	}
	
	
	return 0;
}	
