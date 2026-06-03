#include <stdio.h>

int main()
{ 	
	int a, b, i, sum, e=0;
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
		e +=i*i;
		//~ printf("%d\n", i*i*i);
		}
	printf("%d ", e );
	HOME:
	return 0;
}	
