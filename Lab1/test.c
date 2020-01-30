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

    return 0;
}