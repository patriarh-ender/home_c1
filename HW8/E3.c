#include <stdio.h>

#define SIZE 10 
int input (int arr[], int n)
{	
int i;
	for (i=0; i<n; i++)
	{
		scanf ("%d", &arr[i]);
	}
	return i;
	
}
void findMin(int arr[],int n)
{
	int min=arr[0];
	int max=arr[0];
	int minIndex=0;
	int maxIndex=0;
 for (int i = 0; i < n; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
			minIndex = i;   
		}
		if (arr[i] > max)
		{
			max = arr[i];
			maxIndex = i;   
		}
	}
	printf ("%d %d %d %d", maxIndex+1, max, minIndex+1, min);
}


int main()
{ 
	int arr[SIZE]={0};
	input (arr, SIZE);
	findMin (arr, SIZE);
	//~ findMinf("%.3f", findMin (arr, SIZE)/SIZE);
	//~ int n = SIZE;
	return 0;
}

