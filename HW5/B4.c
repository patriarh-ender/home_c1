#include <stdio.h>

int main()
{ 	
	int a, e=0, n=0;
	scanf("%d", &a); 
	e=a;
	while (n<3){
		e=e/10;
		n++;
		if (e==0 && 0<=n && n<=2){
			goto NO;}
	}
	if (e==0 && n==3){
			printf ("YES");goto YES;
			}
		 NO:
		 printf ("NO");
		//~ printf("%d%d", e, n);
	
		
		
		
	

YES:
return 0;
}	
