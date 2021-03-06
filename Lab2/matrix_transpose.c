
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
#include <time.h> 
#define NUM_THREADS 4
#define BLOCK_SIZE 2
#define CHUNK_SIZE 2


/*N=128 or N = 1024 or N= 2048 or N = 4096*/
#define N 4096
#define N1  1024  
#define N2 2048
#define N3 4096

/*Define functions prototypes. */
void initializeMatrix(int **, int);
void displayMatrix(int **, int);
void naiveOMPTranspose(int **, int);
void *diagonalThreadingTranspose(void *);
void *blockPthreadTranspose(void *); 
void blockOMPTranspose(int **, int);
int **allocate2DMatrixMemory(int);
void swap(int **, int, int);
void basicTranspose(int **, int);

struct thread_data{
    int **matrix; 
    int start;
    int end;
    int threadId;
    int matrixSize;
};

struct thread_data threadDataArray[NUM_THREADS];

int **matrix;

int main(int argc, char *argv[]){
 
    time_t w_time;

    /*Create matrix, initiliaze and print it.*/
    matrix = allocate2DMatrixMemory(N);
    initializeMatrix(matrix, N);
    //printf("Matrix = \n");
    //displayMatrix(matrix, N);

    /*1. OpenMP naive threaded algoirthm*/

    w_time =  clock();
    naiveOMPTranspose(matrix, N);
    w_time = clock() - w_time;
    naiveOMPTranspose(matrix, N);
    //printf("\nTranspose\n");
    //displayMatrix(matrix, N);
    printf("Time takeb by naiveOMPTranspose(): %f s\n", 
    ((double)w_time)/CLOCKS_PER_SEC);
    

    /*2. diagonal threading algorithm*/
    /*
    w_time = clock();
    run_with_threads(NUM_THREADS, diagonalThreadingTranspose);
    w_time = clock() - w_time;

    printf("Time taken by naiveOMPTranspose(): %f s\n", 
        ((double)w_time)/CLOCKS_PER_SEC);
    */

    //printf("\n");
    //displayMatrix(matrix, N);

    /*3. Block oriented OPen MP Transposition of matrices.*/
    
    /*
    w_time = clock();
    blockOMPTranspose(matrix, N);
    w_time = clock() - w_time;
    printf("Time taken by blockOMPTranspose(): %f s\n",
     ((double)w_time)/CLOCKS_PER_SEC);
    //printf("\nTranspose\n");
    //displayMatrix(matrix, N);
    */

    /*2. block oriented pthread algorithm*/
    /*
    w_time = clock();
    run_with_threads(NUM_THREADS, blockPthreadTranspose);
    w_time = clock() - w_time;

    printf("Time taken by blockPthreadTranspose(): %f s\n", 
        ((double)w_time)/CLOCKS_PER_SEC);

    */

    /*5. Basic matrix transpose.*/
    /*
    w_time = clock();
    basicTranspose(matrix, N);
    w_time = clock() - w_time;
    printf("Time taken by basicTranspose(): %f s\n",
     ((double)w_time)/CLOCKS_PER_SEC);
    //printf("\nTranspose\n");
    //displayMatrix(matrix, N);
    */
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


/*
void blockOMPTranspose(int ** mat, int matSize):
This implementation assumes that the matrix is a multiple of the 
block size. 
*/
void blockOMPTranspose(int ** mat, int matSize){
    size_t block, i, j;

    //TODO: 1 check that matrix is a multiple of 
    // the block size. 

    if(matSize % BLOCK_SIZE != 0){
        fprintf(stderr, "Matrix must be a multiple of blocksize.\n");
        exit(-1);
    }

    #pragma omp parallel for private(i, j, block) schedule(static, CHUNK_SIZE)
    for(block = 0; block < matSize; block += BLOCK_SIZE){
        for(i = block; i<block + BLOCK_SIZE; i++){
            for(j= i+1; j<block + BLOCK_SIZE; j++){
                swap(mat, i, j);
            }
        }

        for(i= block + BLOCK_SIZE; i< matSize; i++){
            for(j=block; j<block + BLOCK_SIZE; j++){
                swap(mat, i,j);
            }
        }         
    }

    for(size_t i=block; i< matSize; i++){
        for(size_t j=i+1; j< matSize; j++){
           swap(mat, i,j);
        }  
    }
    
}


/*
void blockPthreadTranspose(void *threadData):
This implementation assumes that the matrix is a multiple of the 
block size. 
*/

/*
void *blockPthreadTranspose(void *threadData){
    size_t block, i, j;

    struct thread_data* data = (struct thread_data *) threadData;

    int my_start, my_end, rank, matSize;
    int **mat;

    my_start = data->start;
    my_end = data->end;
    mat = data->matrix;
    rank = data->threadId;
    matSize = data->matrixSize;

    //check that matrix is a multiple of 
    // the block size. 

    if(matSize % BLOCK_SIZE != 0){
        fprintf(stderr, "Matrix must be a multiple of blocksize.\n");
        exit(-1);
    }

    for(block = my_start; block < my_end; block += BLOCK_SIZE){
        for(i = block; i<block + BLOCK_SIZE; i++){
            for(j= i+1; j<block + BLOCK_SIZE; j++){
                swap(mat, i, j);
            }
        }

        for(i= block + BLOCK_SIZE; i< matSize; i++){
            for(j=block; j<block + BLOCK_SIZE; j++){
                swap(mat, i,j);
            }
        }         
    }

    for(i=block; i< matSize; i++){
        for(j=i+1; j< matSize; j++){
           swap(mat, i,j);
        }  
    }
    
}
*/

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
diagonalThreadingTranspose(void *): pthread diagonal threading. 
This implementation uses SPMD deign pattern. 
*/

void *diagonalThreadingTranspose(void *rank){
    int start, end, i, j, my_rank;
    my_rank = (int)rank; 

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
void basicPTranspose(int **mat, int matSize): Basic matrix transpose
function with no parallelism.
*/
void basicTranspose(int **mat, int matSize){
    int i, j;
    for(i=0; i < matSize; i++){
        for(j = i + 1; j < matSize; j++){
            swap(mat, i, j);  //swap mat[i][j] and mat[j][i]
        }
    }
}


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
