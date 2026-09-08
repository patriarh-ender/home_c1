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
float Print(int arr[],int n)
{
	float a=0;
 for (int i = 0; i < n; i++)
 {
	
	a+=arr[i];
	//~ printf("%d ",arr[i]);
 }
 return a; 
}

//~ void Sum (int arr[],int n)
//~ {
 //~ for (int i = 0; i < n; i++)
 //~ {
	//~ arr[]
 //~ }
 //~ printf("\n");
//~ }

int main()
{ 
	int arr[SIZE]={0};
	input (arr, SIZE);
	Print (arr, SIZE);
	printf("%.3f", Print (arr, SIZE)/SIZE);
	//~ int n = SIZE;
	return 0;
}

