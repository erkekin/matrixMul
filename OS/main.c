/* ERK EKİN 44845434354 eekin@anadolu.edu.tr www.erkekin.com*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int size=0;   // size matters
int num_thrd;   // number of threads

#define SIZE 100  // Size by SIZE matrices

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
    
      int** array = (int**)malloc(size*sizeof(int));
    
    num_thrd = atoi(argv[2]);
    
    printf("size: %lu \n", sizeof(**array));
    
    if(array == NULL)
    {
		fprintf(stderr, "out of memory\n");
		
    }
	for(i = 0; i < size; i++)
    {
		array[i] = malloc(size * sizeof(int));
		if(array[i] == NULL)
        {
			fprintf(stderr, "out of memory\n");
		
    }

    
    }
    
    
    
    
    
    
//    readMatrix((char*)argv[3],size);
//    readMatrix((char*)argv[4],size);
//    
//    rowCount =size/num_thrd;
//    
//    gettimeofday(&t0, 0);
//
//    for (i=0; i<num_thrd; i++) {
//        
//        pthread_t tid;       //Thread ID
//        pthread_attr_t attr; //Set of thread attributes
//        //Get the default attributes
//        pthread_attr_init(&attr);
//        //Create the thread
//        pthread_create(&tid,&attr,multiply,(void*)i);
//        pthread_join(tid, NULL);
//        
//    }
//    
//    gettimeofday(&t1, 0);
//    long elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
//    printf("\n\nTotal execution time using threads is %ld microseconds\n",elapsed);
//
////        C[0][0] = 1;   C[0][1] = 2;    C[0][2] = 3;   C[0][3] = 4;   C[0][4] = 5;   C[0][5] = 6;
////        C[1][0] = 7;   C[1][1] = 8;    C[1][2] = 9;   C[1][3] = 10;   C[1][4] = 11;   C[1][5] = 12;
////        C[2][0] = 1;   C[2][1] = 2;    C[2][2] = 3;   C[2][3] = 4;   C[2][4] = 5;   C[2][5] = 6;
////        C[3][0] = 1;   C[3][1] = 2;    C[3][2] = 3;   C[3][3] = 4;   C[3][4] = 5;   C[3][5] = 6;
////        C[4][0] = 1;   C[4][1] = 2;    C[4][2] = 3;   C[4][3] = 4;   C[4][4] = 5;   C[4][5] = 6;
////        C[5][0] = 1;   C[5][1] = 2;    C[5][2] = 3;   C[5][3] = 4;   C[5][4] = 5;   C[5][5] = 6;
//
//   // writeMatrix((char*)argv[5],size);
//    
//    printMatrixes(size);
    
    return 0;
    
} //end-main


