
//~ #include <stdio.h>

//~ int abs (int n)
//~ { 
	//~ return (n<0)?-n:n;
		 
//~ } 
//~ int middle (int a, int b, int i)
//~ {	
	//~ if (p==0){
		//~ return n=1; }
	
	//~ int a = n;
	//~ for (int i=1; i!=p; i++)
	//~ {
		//~ a=a*n;
	//~ }
	//~ n = a;
//~ return n;	
	
	//~ i=(a+b)/2;
	//~ return i;
	
//~ }
//~ int main (void)
//~ { 
	//~ int a, b, i=0;
	//~ scanf("%d%d", &a, &b);
	//~ if (a<0 || b<0 )
	//~ {
		//~ return 0;}
	//~ printf ("%d", middle(a, b, i));
		//~ return 0;
	
//~ }
#include <stdio.h>
int main()
{
 char c;
 int Number=0;
//спец символ новой строки
 while( (c=getchar())!='\n')
 if(c>='0' && c<='9')
 Number = Number*10+c-'0';
 printf("%d",Number);
 return 0;
}
