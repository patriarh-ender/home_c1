#include <stdio.h>

#define SIZE 5 
int input (int arr[], int n)
{	
int i;
	for (i=0; i<n; i++)
	{
		scanf ("%d", &arr[i]);
	}
	return i;
	
}
void Print(int arr[],int n)
{
	int min=arr[0];
 for (int i = 0; i < n; i++)
	{
		min= min<arr[i]?min:arr[i];
	}
	printf ("%d", min);
 //~ return a; 
}


int main()
{ 
	int arr[SIZE]={0};
	input (arr, SIZE);
	Print (arr, SIZE);
	//~ printf("%.3f", Print (arr, SIZE)/SIZE);
	//~ int n = SIZE;
	return 0;
}
