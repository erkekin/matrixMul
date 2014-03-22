

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define SIZE 2   // Size by SIZE matrices
int num_thrd;   // number of threads


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
}

    //void* multiply(void* slice)
    //{
    //    int s = (int)slice;   // retrive the slice info
    //    int from = (s * SIZE)/num_thrd; // note that this 'slicing' works fine
    //    int to = ((s+1) * SIZE)/num_thrd; // even if SIZE is not divisible by num_thrd
    //    int i,j,k;
    //
    //    printf("computing slice %d (from row %d to %d)\n", s, from, to-1);
    //    for (i = from; i < to; i++)
    //    {
    //        for (j = 0; j < SIZE; j++)
    //        {
    //            C[i][j] = 0;
    //            for ( k = 0; k < SIZE; k++)
    //                C[i][j] += A[i][k]*B[k][j];
    //        }
    //    }
    //    printf("finished slice %d\n", s);
    //    return 0;
    //}

#pragma mark Main Function

int main(int argc, char* argv[]){
    
    int size=0;
    
    
    if (argc < MIN_REQUIRED)  return help();
    
    size = atoi (argv[1]);
    
  
    readMatrix((char*)argv[3],size);
    readMatrix((char*)argv[4],size);
    
    writeMatrix((char*)argv[5],size);
    
    printMatrixes(size);
    
    return 0;
    
} //end-main


