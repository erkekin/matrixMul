

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


int num_thrd;   // number of threads
#define SIZE 6   // Size by SIZE matrices

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
    int from = (s * SIZE)/num_thrd; // note that this 'slicing' works fine
    int to = ((s+1) * SIZE)/num_thrd; // even if SIZE is not divisible by num_thrd
    int i,j,k;
    
    printf("computing slice %d (from row %d to %d)\n", s, from, to-1);
    for (i = from; i < to; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            C[i][j] = 0;
            for ( k = 0; k < SIZE; k++)
                C[i][j] += A[i][k]*B[k][j];
        }
    }
    
    printf("finished slice %d\n", s);
    return 0;
}


#pragma mark Main Function



int main(int argc, char* argv[]){
    
    int size=0;
    int rowCount =0;
    
    if (argc < MIN_REQUIRED)  return help();
    
    size = atoi (argv[1]);
    num_thrd = atoi(argv[2]);
    
    readMatrix((char*)argv[3],size);
    readMatrix((char*)argv[4],size);
    
    rowCount =size/num_thrd;
    multiply(2);
    
    
    //      C[0][0] = 1;   C[0][1] = 2;    C[0][2] = 3;   C[0][3] = 4;   C[0][4] = 5;   C[0][5] = 6;
    //      C[1][0] = 7;   C[1][1] = 8;    C[1][2] = 9;   C[1][3] = 10;   C[1][4] = 11;   C[1][5] = 12;
    //      C[2][0] = 1;   C[2][1] = 2;    C[2][2] = 3;   C[2][3] = 4;   C[2][4] = 5;   C[2][5] = 6;
    //      C[3][0] = 1;   C[3][1] = 2;    C[3][2] = 3;   C[3][3] = 4;   C[3][4] = 5;   C[3][5] = 6;
    //      C[4][0] = 1;   C[4][1] = 2;    C[4][2] = 3;   C[4][3] = 4;   C[4][4] = 5;   C[4][5] = 6;
    //      C[5][0] = 1;   C[5][1] = 2;    C[5][2] = 3;   C[5][3] = 4;   C[5][4] = 5;   C[5][5] = 6;
    
    
    writeMatrix((char*)argv[5],size);
    
    printMatrixes(size);
    
    return 0;
    
} //end-main


