#include <stdio.h>

#define SIZE 10 
void input (int arr[], int n)
{	
int i;
	for (i=0; i<n; i++)
	{
		scanf ("%d", &arr[i]);
	}
	//~ return i;
	
}
void PosNumber(int arr[],int n)
{
	int sum=0;
 for (int i = 0; i < n; i++)
	{
		if (arr[i]>0)
		{
			sum+=arr[i];
		}
	}
	printf ("%d", sum);
 //~ return a; 
}


int main()
{ 
	int arr[SIZE]={0};
	input (arr, SIZE);
	PosNumber (arr, SIZE);
	//~ printf("%.3f", Print (arr, SIZE)/SIZE);
	//~ int n = SIZE;
	return 0;
}
