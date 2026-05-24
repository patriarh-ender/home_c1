#include <stdio.h>

int main()
{ 	
	int a, b, c, e, d, max;
	scanf("%d%d%d%d%d", &a, &b, &c, &e, &d);
	max = a < b ? a : b;
	max = max< c ? max: c;
	max= max<e? max: e;
	max= max<d? max: d;
	printf("%d", max);
	
	return 0;
}
