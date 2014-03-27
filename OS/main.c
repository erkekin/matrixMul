/* ERK EKİN 44845434354 eekin@anadolu.edu.tr www.erkekin.com*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int size=0;   // size matters
int num_thrd;   // number of threads

#define SIZE 100   // Size by SIZE matrices

/* minimum required number of parameters */

#define MIN_REQUIRED 6

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

int help() {
    
    printf("Usage: matrixMul <N> <p> <filenameA> <filenameB> <filenameC>\n");
    printf("Example: matrixMul 100 10 matrixa.dat matrixb.dat result.dat\n");
    
    return 1;
}

void writeMatrix(char*  filename,int N){
    
    FILE *matrixFile;
    matrixFile=fopen(filename, "wb");
    
    fwrite(C, sizeof(int), N*N, matrixFile);
    
    fclose(matrixFile);
    
    
} //end-writeMatrix


void readMatrix(char*  filename, int N){
    
    FILE * matrixFile;
    
    if ((matrixFile = fopen(filename, "rb")) == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    
    fread(strcmp(filename,"matrixa.dat")?A:B, sizeof(int),  N*N, matrixFile);
    
    
    fclose(matrixFile);
    
} //end-readMatrix


void printMatrixes(int N) {
    
    int j;
    int i;
    
    for (i=0; i<N; i++) {
        
        for (j=0; j<N; j++) {
            
            printf("%d ",A[i][j]);
            
        }    printf("\n");
    }
    printf("\n");
    for (i=0; i<N; i++) {
        
        for (j=0; j<N; j++) {
            
            printf("%d ",B[i][j]);
            
        } printf("\n");
    }
    printf("\n");
    for (i=0; i<N; i++) {
        
        for (j=0; j<N; j++) {
            
            printf("%d ",C[i][j]);
            
        } printf("\n");
    }
    
}

void* multiply(void* slice)
{
    int s = (int)slice;   // retrive the slice info
    int from = (s * size)/num_thrd; // note that this 'slicing' works fine
    int to = ((s+1) * size)/num_thrd; // even if SIZE is not divisible by num_thrd
    int i,j,k;
    
    for (i = from; i < to; i++)
    {
        for (j = 0; j < size; j++)
        {
            C[i][j] = 0;
            for ( k = 0; k < size; k++)
                C[i][j] += A[i][k]*B[k][j];
        }
    }
    
    return 0;
}


#pragma mark Main Function

int main(int argc, char* argv[]){
    
    int i =0;
    int rowCount =0;
    struct timeval t0,t1;
    
    if (argc < MIN_REQUIRED)  return help();
    
    size = atoi (argv[1]);
    num_thrd = atoi(argv[2]);
    
    readMatrix((char*)argv[3],size);
    readMatrix((char*)argv[4],size);
    
    rowCount =size/num_thrd;
    
    gettimeofday(&t0, 0);

    for (i=0; i<num_thrd; i++) {
        
        pthread_t tid;       //Thread ID
        pthread_attr_t attr; //Set of thread attributes
        //Get the default attributes
        pthread_attr_init(&attr);
        //Create the thread
        pthread_create(&tid,&attr,multiply,(void*)i);
        pthread_join(tid, NULL);
        
    }
    
    gettimeofday(&t1, 0);
    long elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
    printf("\n\nTotal execution time using threads is %ld microseconds\n",elapsed);


    writeMatrix((char*)argv[5],size);
    
    printMatrixes(size);
    
    return 0;
    
} //end-main


