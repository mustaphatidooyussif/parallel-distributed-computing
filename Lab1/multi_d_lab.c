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

    /*= {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int n0 = -1; int n1 = -1; int n2 = -1; int n3 = -1; 
    int n4 = -1; int n5 = -1; int n6 = -1; int n7 = -1;
    int n8 = -1; int n9 = -1; int n10 = -1; int n11 = -1;
    int n12 = -1; int n13 = -1; int n14 = -1; int n15 = -1; */
};

int main(int argc, char *argv[]){
    //int array one 
    printf("---------------------Array One--------------------\n");
    int k_2 = 2;
    int arr1_bounds[2] = {100, 100}; 
    int *arr1 = create_array(k_2, arr1_bounds);
    int **dope_vec1 = single_index_to_cordinate(arr1_bounds);
    procedure_one(arr1, arr1_bounds);
    procedure_two(arr1, arr1_bounds);
    procedure_three(arr1, arr1_bounds);


    //array two 
    printf("---------------------Array Two--------------------\n");
    int k_3 = 3;
    int arr2_bounds[3] = {100, 100, 100};
    int *arr2 = create_array(k_3, arr2_bounds);
    int **dope_vec2 = single_index_to_cordinate(arr2_bounds);
    procedure_one(arr2, arr2_bounds);
    procedure_two(arr2, arr2_bounds);
    procedure_three(arr2, arr2_bounds);


    //array three 
    printf("---------------------Array Three--------------------\n");
    int k_4 = 4;
    int arr3_bounds[4] = {50, 50, 50, 50};
    int *arr3 = create_array(k_4, arr3_bounds);
    int **dope_vec3 = single_index_to_cordinate(arr3_bounds);
    procedure_one(arr3, arr3_bounds);
    procedure_two(arr3, arr3_bounds);
    procedure_three(arr3, arr3_bounds);


    //array four 
    printf("---------------------Array Four--------------------\n");
    int k_5 = 5; 
    int arr4_bounds[5] = {20, 20, 20, 20, 20};
    int *arr4 = create_array(k_5, arr4_bounds);
    int **dope_vec4 = single_index_to_cordinate(arr4_bounds);
    procedure_one(arr4, arr4_bounds);
    procedure_two(arr4, arr4_bounds);
    procedure_three(arr4, arr4_bounds);

    
    //Free memories 
    free(arr1);  free(dope_vec1);
    free(arr2);  free(dope_vec2);
    free(arr3);  free(dope_vec3);
    free(arr4);  free(dope_vec4);

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

    //////////////////////////////////////////////////


    //////////////////////////////////////////////////
    free(d);
}

int *single_index_to_cordinate(int index, int dimentionSizes[])
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
    
}

/*
*single_index_to_cordinate(int index, int dimentionSizes[]): it generates the cordinates given
a single array index. 
*/
int *single_index_to_cordinate(int index, int dimentionSizes[])
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
        int *ans = single_index_to_cordinate(k, bounds);
        result[k] = ans;
    }

    return result; 
}
