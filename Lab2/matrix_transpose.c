
/*
Author: Mustapha TIdoo Yussif.

Lab two. 
The main purpose of this laboratory exercise is to learn to use shared
memory programming libraries, Pthread and OpenMP, for simple scientific applications of manip-
ulating very large matrices that are maintained in memory.
*/

#include <stdlib.h> 
#include <stdio.h> 
#include <omp.h>
#include <pthread.h> 
#define NUM_THREADS 4

/*Define functions prototypes. */
void initializeMatrix(int **, int);
void displayMatrix(int **, int);
void naiveOMPTranspose(int **, int);
void *diagonalThreadingTranspose(void *);
void blockPthreadTranspose(int **); 
void blockOMPTranspose(int **);
int **allocate2DMatrixMemory(int);
void swap(int **, int, int);



struct thread_data threadDataArray[NUM_THREADS];

int main(int argc, char *argv[]){

    /*N=128 or N = 1024 or N= 2048 or N = 4096*/
    int N = 8; 
    //int N = 1024;  
    //int N = 2048; 
    //int N = 4096; 

    /*Create matrix, initiliaze and print it.*/
    int **matrix = allocate2DMatrixMemory(N);
    initializeMatrix(matrix, N);
    printf("Matrix = \n");
    displayMatrix(matrix, N);

    /*1. OpenMP naive threaded algoirthm*/
    /*naiveOMPTranspose(matrix, N);
    printf("\nTranspose\n");
    displayMatrix(matrix, N);*/

    /*2. diagonal threading algorithm*/
    pthread_t threads[NUM_THREADS];
    int rc, t; 

    for(t = 0; t < NUM_THREADS; t++){

        /*
        Parameter for the function to be run by 
        the threads. 
        */
        threadDataArray[t].threadId = t;
        threadDataArray[t].matrix = matrix;
        threadDataArray[t].matrixSize = N;
        threadDataArray[t].start = t * (N/NUM_THREADS);
        threadDataArray[t].end = (t + 1) * (N/NUM_THREADS) - 1;

        /*
        create the threads. 
        */
        rc = pthread_create(&threads[t], NULL, diagonalThreadingTranspose, 
                (void *) &threadDataArray[t]);
            
        if(rc){
            fprintf(stderr, "Error: connot create threads\n");
            exit(-1);
        }

    }

    pthread_exit(NULL);

    return (EXIT_SUCCESS);
}

/*
allocate2DMatrixMemory(int K, int bounds[]): dynamically creates 
K-dimension array of any size.  
*/
int **allocate2DMatrixMemory(int bound){

    //allocate space. 
    int **matrix; 
    matrix =  malloc(bound * sizeof(int*)); 
    for(int i=0; i < bound; i++){
        matrix[i]= malloc(bound * sizeof(int));
    }

    /*if allocation not successful*/
    if(matrix == NULL){
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    /*if successful.*/
    return matrix; 
}

/*
void initializeMatrix(int **, int): intialize the matrix. 
*/
void initializeMatrix(int **matrix, int bound){
    int i, j, k = 0;
    for(i=0; i < bound; i++){
        for(j =0; j < bound; j++){
            k ++;
            matrix[i][j] = k;
        }
    }
}

/*
void displayMatrix(int **, int): this function displays the content 
of the 2d array passed a parameter. 
*/
void displayMatrix(int **matrix, int bound){
    int i, j;
    for(i =0; i < bound; i++){
        for(j =0; j< bound; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

/*
naiveOMPTranspose(int **mat, int matSize): is the naive matrix 
transposition implementation in OpenMP.
*/
void naiveOMPTranspose(int **mat, int matSize){
    int nThreads;
    #pragma omp parallel
    {
        int id, i, j;
        id =  omp_get_thread_num();

        /*Only the master thread can do this.*/
        if(id == 0){
            nThreads = omp_get_num_threads();
        }

        #pragma omp for nowait
        for(i=0; i < matSize; i++){
            for(j = i + 1; j < matSize; j++){
                swap(mat, i, j);  //swap mat[i][j] and mat[j][i]
            }
        }

    }/*End of parallel section.*/
}


/*
swap(int **mat, int i, int j): this function swaps the values of the
matrix at the given indices. 
*/
void swap(int **mat, int i, int j){
    int temp = mat[i][j]; 
    mat[i][j] = mat[j][i];
    mat[j][i] = temp; 
}

struct thread_data{
    int **matrix; 
    int start;
    int end;
    int threadId;
    int matrixSize;
};


/*
diagonalThreadingTranspose(void *): pthread diagonal threading. 
This implementation uses SPMD deign pattern. 
*/
void *diagonalThreadingTranspose(void *threadData){

    struct thread_data* data = (struct thread_data *) threadData;

    int i, j, my_start, my_end, rank, matSize;
    int **mat;

    my_start = data->start;
    my_end = data->end;
    mat = data->matrix;
    rank = data->threadId;
    matSize = data->matrixSize;

    printf("Thread =%d, start = %d, end= %d\n",rank, my_start, my_end);

    for(i=my_start; i < my_end; i++){
        for(j= i + 1; j < matSize; j ++){
            swap(mat, i, j);
        }
    }

    pthread_exit(NULL);
}