#include <stdio.h>
#include <stdlib.h>

void display(int array[]) {
   int i;
   printf("[ ");

   // navigate through all items
   for(i = 0;i < 8;i++) {
      printf("%d ",array[i]);
   }

   printf("]\n");
}

int partition(int array[], int low, int high){
    int temp = array[high];

    int l = low;
    int u = high;

    while(l < u){
        while(l < u && array[l] <= temp){
            l++;
        }

        if(l < u){
            array[u] = array[l];
            u--;
        }

        while(l < u && array[u] >= temp){
            u--;
        }

        if(l < u){
            array[l] = array[u];
            l++;
        }
    }

    printf("%d\n", l);
    printf("%d\n", u);

    array[l] = temp;

    return l;
}

int partition2(int a[],int l,int u)
{
	int v,i,j,temp;
	v=a[l];
	i=l;
	j=u+1;

	do
	{
		do
			i++;
		while(a[i]<v&&i<=u);

		do
			j--;
		while(v<a[j]);

		if(i<j)
		{
			temp=a[i];
			a[i]=a[j];
			a[j]=temp;
		}
	}while(i<j);

	a[l]=a[j];
	a[j]=v;

	return(j);
}

int main(void){
    int array[8] = {4,3,8,1,6,5,7,2};

    display(array);
    partition(array, 0, 7);
    display(array);
    printf("\n");

    // int arrayz[8] = {4,3,8,1,6,5,7,2};

    // display(arrayz);
    // partition2(arrayz, 0, 7);
    // display(arrayz);
}
