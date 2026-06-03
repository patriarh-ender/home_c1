#include <stdio.h>

int main()
{ 	
	int a, b, i, sum;
	scanf("%d%d", &a, &b); 
	if (a<0){
		sum = ((a*-1)+b);
		}
	if (a<=b && sum<= 100 )
	{ goto CICAL;
		}
		else goto HOME;
		CICAL:
	for(i=a; i<=b; i++){
		//~ printf("%d ", i);
		printf("%d ", i*i);
		//~ printf("%d\n", i*i*i);
		}
	
	HOME:
	return 0;
}	
