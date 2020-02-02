#include <stdio.h> 
#include <stdlib.h> 


int main(){

    int dimension_1 = 3;
    int dimension_2 = 3;

    int** x; //x[3][3]

    x = (int **)malloc(dimension_1 * sizeof(*x));
    for(int i=0; i< dimension_1; i++){
        x[i] = (int *)malloc(dimension_2 * sizeof(x[0]));
    }

    int cols = 3;
    int rows = 3;
    int arr[2][3] = {
                        {1,2, 3},
                        {4,5, 6}
                        
                    };

    int j = 1;
    int i = 1; 

    printf("(%d, %d)", 0, 0);

    while(j < (rows-1) * (cols-1)){
        printf("(%d, %d)", i, j % cols);

        if(j % cols == 0)
            i ++; 

        j ++;
    }

    return 0;
}