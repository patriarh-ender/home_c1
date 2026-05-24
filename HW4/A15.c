#include <stdio.h>

int main()
{
	int X1, Y1, X2, Y2;
	float k,b;
	scanf ("%d%d%d%d", &X1, &Y1, &X2, &Y2 );
	k=(float)(Y1-Y2)/(X1-X2);
	b=(float)Y2-k*X2;
	printf("%.2f %.2f", k, b);
	return 0;










}
