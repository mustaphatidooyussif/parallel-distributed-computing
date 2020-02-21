#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h> 

#define N 8
#define NUM_THREADS 4
#define BLOCK_SIZE 2
#define CHUNK_SIZE 2

void initializeMatrix(int **, int);
void displayMatrix(int **, int);
int **allocate2DMatrixMemory(int);
void swap(int **, int, int);
void *diagonalThreadingTranspose(void *);
void run_with_threads(int nThreads, void *(*start_routine)(void *));
void *blockPthreadTranspose(void *); 

int **matrix;

int main(int argc, char * argv[]){
    //int N = 8; 
    matrix = allocate2DMatrixMemory(N);
    initializeMatrix(matrix, N);
    displayMatrix(matrix, N);

    //run_with_threads(NUM_THREADS, diagonalThreadingTranspose);
    run_with_threads(NUM_THREADS, blockPthreadTranspose);

    printf("\n");
    displayMatrix(matrix, N);
    return (EXIT_SUCCESS);
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

void *diagonalThreadingTranspose(void *rank){
    int start, end, i, j, my_rank;
    my_rank = (long)rank; 

    start = my_rank * (N/NUM_THREADS);
    end = (my_rank + 1) * (N/NUM_THREADS);


    for(i = start; i < end; i++){
        for(j= i + 1; j < N; j ++){
            swap(matrix, i, j);
        }
    }

    pthread_exit(NULL);
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
swap(int **mat, int i, int j): this function swaps the values of the
matrix at the given indices. 
*/
void swap(int **mat, int i, int j){
    int temp = mat[i][j]; 
    mat[i][j] = mat[j][i];
    mat[j][i] = temp; 
}


void run_with_threads(int nThreads, void *(*start_routine)(void *)){
    pthread_t threads[nThreads];
    int rc, t;

    //w_time = clock() - w_time;
    for(t = 0; t < nThreads; t++){        
        //create the threads. 
        
        rc = pthread_create(&threads[t], NULL, start_routine, 
                (void *) t);
            
        if(rc){
            fprintf(stderr, "Error: connot create threads\n");
            exit(-1);
        }

    }

    //Join all threads
    for( t =0; t < nThreads; t++){
        pthread_join(threads[t], NULL);
    } 
}


/*
void blockPthreadTranspose(void *threadData):
This implementation assumes that the matrix is a multiple of the 
block size. 
*/

void *blockPthreadTranspose(void *rank){

    int start, end, i, j, my_rank, block;
    my_rank = (int)rank; 

    start = my_rank * (N/NUM_THREADS);
    end = (my_rank + 1) * (N/NUM_THREADS);

    //check that matrix is a multiple of 
    // the block size. 

    if(N % BLOCK_SIZE != 0){
        fprintf(stderr, "Matrix must be a multiple of blocksize.\n");
        exit(-1);
    }

    for(block = start; block < end; block += BLOCK_SIZE){
        for(i = block; i<block + BLOCK_SIZE; i++){
            for(j= i+1; j<block + BLOCK_SIZE; j++){
                swap(matrix, i, j);
            }
        }

        for(i= block + BLOCK_SIZE; i< N; i++){
            for(j=block; j<block + BLOCK_SIZE; j++){
                swap(matrix, i,j);
            }
        }         
    }

    for(i=block; i< N; i++){
        for(j=i+1; j< N; j++){
           swap(matrix, i,j);
        }  
    }
    
}
