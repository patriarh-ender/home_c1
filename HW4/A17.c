#include <stdio.h>

int main()
{ int a;
	scanf("%d", &a);
	if (a>0 && a<= 12 ){
		if (a== 1 || a==12 || a==2 ){
			printf ("winter");}
		if(a>=3 && a<= 5 ){
			printf ("spring");}
		if(a>=6 && a<= 8 ){
			printf ("summer");}
		if(a>=9 && a<= 11 ){
			printf ("autumn");}
				
						
		}
	else {printf ("NO month");
		}
	return 0;
}

