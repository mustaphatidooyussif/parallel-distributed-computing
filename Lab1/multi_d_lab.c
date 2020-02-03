/*
Authors: Mustapha Tidoo Yussif
              & 
        Jones Dari
*/

#include <stdlib.h> 
#include <stdio.h> 

//Function prototypes. 
void procedure_one(int *, int []);
void procedure_two(int *, int []);
void procedure_three(int *, int []);
int *create_array(int, int[]);

struct cordinates{
    int num_filled;
    int n[16];
    /*= {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
    int n0 = -1; int n1 = -1; int n2 = -1; int n3 = -1; 
    int n4 = -1; int n5 = -1; int n6 = -1; int n7 = -1;
    int n8 = -1; int n9 = -1; int n10 = -1; int n11 = -1;
    int n12 = -1; int n13 = -1; int n14 = -1; int n15 = -1; */
};

int main(int argc, char *argv[]){
    //int array one 
    int arr1_bounds[2] = {10, 10}; 
    int *arr1 = create_array(2, arr1_bounds);
    procedure_one(arr1, arr1_bounds);
    procedure_two(arr1, arr1_bounds);
    procedure_three(arr1, arr1_bounds);

   /* int arr1_dims[2] = {3, 3}; 
    int *arr1 = (int *)malloc(arr1_dims[0] * arr1_dims[1] * sizeof(int));
    int *dope_vector_1 = (int *)malloc(arr1_dims[0] * arr1_dims[1] * sizeof(int));
    procedure_one(arr1, arr1_dims);


    //array two 
    int arr2_dims[3] = {100, 100, 100};
    int *arr2 = (int *)malloc(arr2_dims[0] * arr2_dims[1] * arr2_dims[2] * sizeof(int));
    int *dope_vector_2 = (int *)malloc(arr2_dims[0] * arr2_dims[1] * arr2_dims[2] * sizeof(int));
    
    //array three 
    int arr3_dims[4] = {50, 50, 50, 50};
    int *arr3 = (int *)malloc(arr3_dims[0] * arr3_dims[1] * arr3_dims[2] * arr3_dims[3] * sizeof(int));
    int *dope_vector_3 = (int *)malloc(arr3_dims[0] * arr3_dims[1] * arr3_dims[2] * arr3_dims[3] * sizeof(int));

    //array four 
    int arr4_dims[5] = {20, 20, 20, 20, 20};
    int *arr4 = (int *)malloc(arr4_dims[0] * arr4_dims[1] * arr4_dims[2] * arr4_dims[3] * arr4_dims[4] * sizeof(int));
    int *dope_vector_4 = (int *)malloc(arr4_dims[0] * arr4_dims[1] * arr4_dims[2] * arr4_dims[3] * arr4_dims[4] * sizeof(int));


    //Free memories 
    free(arr1); free(dope_vector_1); 
    free(arr2); free(dope_vector_2); 
    free(arr3); free(dope_vector_3);
    free(arr4); free(dope_vector_4);*/

    return 0; 
}

/*
create_array(int K, int bounds[]): dynamically creates K-dimension array of any size.  
*/
int *create_array(int K, int bounds[]){

    //calculate size needed for memory allocation. 
    int N = 1; 
    for(int i = 0; i< K; i++){
        N *= bounds[i];
    }

    //allocate space. 
    return malloc(N * sizeof(int)); 
}

/*
procedure_one(int * arr, int dim[]): initializes the element of the array to zeroes. 
*/
void procedure_one(int * arr, int bounds[]){
    //Find number of arr bounds. 
    int num_bounds = sizeof(bounds)/sizeof(bounds[0]); 
    int* d = (int *)calloc((num_bounds), sizeof(int));

    //Find arr capacity. 
    int N = 1; 
    for (int i =0; i < num_bounds; i++){
        N = N * bounds[i];
    }

    //Fill arr with zeroes. 
    int k = 0;
    while(k < N){
        arr[k] = 0;
        k ++;
    }
}


/*
procedure_two(int * arr, int dim[]): sets 10% of the elements uniformly to 1s. 
*/
void procedure_two(int * arr, int bounds[]){

    //find 10 percent of the elements of the array
    int num_bounds = sizeof(bounds)/sizeof(bounds[0]);
    int N = 1; 
    for (int i =0; i < num_bounds; i++){
        N = N * bounds[i];
    }

    int portion = 0.1 * N; //10 percent of N (total array size)

    //Uniformly set 10 percent of array to zero. 
    int k = 0;
    while (k < N){
        if(k % portion == 0){
            arr[k] = 1; 
        }
        k++;
    }
}


/*
procedure_three(int * arr, int dim[]): chooses 5% elements of the array and
prints cordinate indices of the elemts and the values in a uniform random 
fashion. 
*/
void procedure_three(int * arr, int bounds[]){

    int num_bounds = sizeof(bounds)/sizeof(bounds[0]);
    int N = 1; 
    for (int i =0; i < num_bounds; i++){
        N = N * bounds[i];
    }

    int portion = 0.05 * N; //5 percent of the element of the array. 

    //Generate random numbers equal to 'portion'

    int lower = 0;
    int upper = N; 
    int k = 0;
    int count = 0; 
    int prev_randint = 0;


    while(k < portion){
        int num = (rand() % (upper - lower)) + lower;
        printf("The value = %d, Index = %d\n", arr[num], num);
        k++;
    }
    
    printf("Hello world, procedure three");    
}
