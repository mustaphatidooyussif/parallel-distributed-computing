#include <stdio.h> 
#include <stdlib.h> 

int *SingleIndexToMulti(int index, int dimentionSizes[]);
int **create_dope_vector(int k, int bounds[]);

int main(){
    int t[] = {2,3,4};
    int k = 3;
    int ** dope_vec1 = malloc((t[0]*t[1]*t[2]) * sizeof(int*));
    create_dope_vector(k, t);  

    return 0;
}

/*
*SingleIndexToMulti(int index, int dimentionSizes[]): it generates the cordinates given
a single array index. 
*/
int *SingleIndexToMulti(int index, int dimentionSizes[])
{
    int size = sizeof(dimentionSizes)/sizeof(dimentionSizes[0]);
    int *result = malloc(size * sizeof(int));
    for (int i = size; i >=0; i--)
    {
        result[i] = index % dimentionSizes[i];
        index = index / dimentionSizes[i];
    }

    return result;
}

/*
**create_dope_vector(int **vector, int bounds[]): this creates the node 
vector of a given array. 
*/
int **create_dope_vector(int K, int bounds[]){
    int N = 1;
    for (int i= 0; i < K; i++){
        N  *= bounds[i];
    }
    int** result =  (int **)malloc(N * sizeof(int*));

    for(int k= 0; k < N; k++){
        int *ans = SingleIndexToMulti(k, bounds);
        result[k] = ans;
    }

    return result; 
}
