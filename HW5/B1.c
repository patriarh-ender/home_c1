#include <stdio.h>

int main()
{ 	
	int a, i;
	//~ printf("Chislo ot 1 do 100\n");
	scanf("%d", &a);
	if (a>100)
	{ printf("ne to");
		goto HOME;
		}
	for(i=1; i<=a; i++){
		printf("%d ", i);
		printf("%d ", i*i);
		printf("%d\n", i*i*i);
		}
	
	HOME:
	return 0;
}	
