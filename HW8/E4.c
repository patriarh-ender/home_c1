#include <stdio.h>

#define SIZE 10 
void input (int arr[], int n)
{	
int i;
	for (i=0; i<n; i++)
	{
		scanf ("%d", &arr[i]);
	}
	
	
}
//~ void findMe(int arr[],int n)
//~ {
	//~ int Fmax=arr[0];
	//~ int Smax=arr[0];
	int minIndex=0;
	int maxIndex=0;
 //~ for (int i = 0; i < n; i++)
	//~ {
		//~ if (arr[i] > Fmax)
		//~ {
			//~ Fmax = arr[i];
			
		//~ }
		//~ if (arr[i] < Fmax && arr[i]>Smax)
		//~ {
			//~ Smax = arr[i];
			   
		//~ }
	//~ }
	//~ printf ("%d", Fmax+Smax);
//~ }
//~ void findMe(int arr[], int n) 
//~ {
    //~ int Fmax = arr[0];
    //~ for (int i = 1; i < n; i++) 
    //~ {
        //~ if (arr[i] > Fmax) 
        //~ {
            //~ Fmax = arr[i];
        //~ }
    //~ }

    //~ int Smax;
    //~ int found = 0;
    //~ for (int i = 0; i < n; i++) 
    //~ {
        //~ if (arr[i] < Fmax) 
        //~ {
            //~ if (!found) 
            //~ {
                //~ Smax = arr[i];
                //~ found = 1;
            //~ } 
            //~ else if (arr[i] > Smax) 
            //~ {
                //~ Smax = arr[i];
            //~ }
        //~ }
    //~ }

    //~ if (!found)
        //~ printf("Второго максимума нет\n");
    //~ else
        //~ printf("%d", Fmax+ Smax);
//~ }
void findMe(int arr[], int n) 
{
    int max1 = arr[0];
    int max2 = arr[0];
    int found2 = 0;

    for (int i = 1; i < n; i++) 
    {
        if (arr[i] > max1) 
        {
            max2 = max1;
            max1 = arr[i];
            found2 = 1;
        }
        else if (arr[i] == max1) 
        {
            max2 = max1;
            found2 = 1;
        }
        else if (!found2 || arr[i] > max2) 
        {
            max2 = arr[i];
            found2 = 1;
        }
    }

    if (!found2)
        printf("Второго максимума нет\n");
    else
        printf("%d\n", max1 + max2);
}

int main()
{ 
	int arr[SIZE]={0};
	input (arr, SIZE);
	findMe (arr, SIZE);
	//~ findMinf("%.3f", findMin (arr, SIZE)/SIZE);
	//~ int n = SIZE;
	return 0;
}

