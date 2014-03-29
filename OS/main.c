/* ERK EKİN 44845434354 eekin@anadolu.edu.tr www.erkekin.com*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

int size=0;   // size matters
int num_thrd;   // number of threads

/* minimum required number of parameters */

#define MIN_REQUIRED 6

int * ilkmatrix,*ikincimatrix,*resulmatrix;


int help() {
    
    printf("Usage: matrixMul <N> <p> <filenameA> <filenameB> <filenameC>\n");
    printf("Example: matrixMul 100 10 matrixa.dat matrixb.dat result.dat\n");
    
    return 1;
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
            *(resulmatrix+size*i+j) = 0;
            for ( k = 0; k < size; k++)
                *(resulmatrix+size*i+j) += *(ilkmatrix+size*i+k) * *(ikincimatrix+size*k+j);
        }
    }
    
    return 0;
}


#pragma mark Main Function

void print_arrays(int *matrixa, int *matrixb, int *matrixc) {
    int j;
    int i;
    for (i = 0; i<size; i++) {
        
        for (j = 0; j<size; j++) {
            
            printf("%d ", *(matrixa+size*i+j));
        }
        printf("\n");
    }
    printf("\n");
    for (i = 0; i<size; i++) {
        
        for (j = 0; j<size; j++) {
            
            printf("%d ", *(matrixb+size*i+j));
        }
        printf("\n");
    }
    printf("\n");
    for (i = 0; i<size; i++) {
        
        for (j = 0; j<size; j++) {
            
            printf("%d ", *(matrixc+size*i+j));
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]){
    
    int rowCount =0;
    struct timeval t0,t1;
    FILE *matrixFile;
    int i =0;
    
    int* array1;
    int* matrixa;
    int* matrixb;
    int* matrixc;
    if (argc < MIN_REQUIRED)  return help();
    
    size = atoi (argv[1]); num_thrd = atoi(argv[2]);
    
    array1 = malloc (size*size*sizeof(int*));
    matrixa = malloc (size*size*sizeof(int*));
    matrixb = malloc (size*size*sizeof(int*));
    matrixc = malloc (size*size*sizeof(int*));
    
        //        //PRODUCE ARRAY
        //    for (i = 0; i<size; i++) {
        //
        //        for (j = 0; j<size; j++) {
        //
        //            *(array1+size*i+j) = i;
        //
        //        }
        //
        //    }
    
        //        //WRITE PRODUCED ARRAY
        //    matrixFile=fopen("matris1.dat", "wb");
        //
        //    fwrite(array1, sizeof(int*), size*size, matrixFile);
        //
        //    fclose(matrixFile);
 
    
        //READ FIRST ARRAY
    if ((matrixFile = fopen("matrixa.dat", "rb")) == NULL)
    {
        printf("Error opening file\n");
    }
    
    fread(matrixa, sizeof(int*), size*size, matrixFile);
    
    fclose(matrixFile);
    
        //READ SECOND ARRAY
    if ((matrixFile = fopen("matrixb.dat", "rb")) == NULL)
    {
        printf("Error opening file\n");
    }
    
    fread(matrixb, sizeof(int*), size*size, matrixFile);
    fclose(matrixFile);
    
    ilkmatrix =matrixa;
    ikincimatrix =matrixb;
    resulmatrix = matrixc;
    
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
    printf("Total execution time using threads is %ld microseconds\n",elapsed);
    
    
        //WRITE PRODUCED ARRAY
    matrixFile=fopen("result.dat", "wb");
    
    fwrite(resulmatrix, sizeof(int*), size*size, matrixFile);
    
    fclose(matrixFile);
    
        //  print_arrays(ilkmatrix, ikincimatrix, resulmatrix);
    
    return 0;
    
} //end-main


