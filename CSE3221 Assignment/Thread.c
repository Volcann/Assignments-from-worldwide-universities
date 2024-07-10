/*
==================================================================================================================
This C program processes several data sets and calculates certain values based on their content.
Each data sample is a floating-point number. Each data set consists of many data samples and each
data set is stored in a file. The file format is that all data samples in this data set are separated
by whitespace in the file.

Output:
    Filenamei  SUM=sumi DIF=difi MIN=mini MAX=maxi
    Filenamej  SUM=sumj DIF=difj MIN=minj MAX=maxj
    …
    MINIMUM=minimum  MIXIMUM=maximum
==================================================================================================================
*/

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

//for loops simplified
#define FOR(i,n) for(i = 0; i < n; i++)
#define FOR2(i, a, n) for(i = (a); i < n; i++)

/*The second struct that stores the output from child processes and is passed to parent process.*/
typedef struct {
    char file[101]; //filename
    double sum; //sum
    double diff; //diff
    double min; //min
    double max; //max
} FileArray;

//initialize `array'
FileArray *array;

/* mutex lock*/
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/* threadCount variable keeps track of assigning values to a specific thread */
static int threadCount = 0;

/* A thread run the below function in order to compute the sum and differences of the dataset.
 * It uses `threadCount' variable to keep track of thread number.
 */
void *file_count (void *filename){
    
    /*Local file varaiable for the process.*/
    FILE *file1 = fopen(filename, "r");
    if (file1 == NULL) {
        fprintf(stderr, "Invalid File!\n");
        exit(-1);
    }
    
    if (array == NULL) {
        fprintf(stderr, "Error! Could not allocate memory!\n");
        exit(-1);
    }
    
    /*Local variables for the child threads/*/
    char str[101];
    double sum = 0.0;
    double diff = 0.0;
    double max = -INFINITY;
    double min = INFINITY;
    
    /*Reading file until End Of File.*/
    while ((fscanf (file1, "%s", str)) != EOF) {
        
        /* This part of child thread reads each of the
         * provided file and determines maximumn as well
         * minimum floating-point number.
         */
        double temp = atof(str);
        
        if (temp < min)
            min = temp;
        
        if (temp > max)
            max = temp;
        
        /*Reset array str.*/
        memset(str, '\0', 101);
    }
    
    //set diff and sum
    diff = max - min;
    sum = max + min;
    
    //lock prior to saving at position `threadCount' (make sure no context switch before threadCount incremented)
    pthread_mutex_lock(&lock);
    
    /*set `array' diff, sum, max and mean to calculated from file*/
    array[threadCount].diff = diff;
    array[threadCount].sum = sum;
    array[threadCount].max = max;
    array[threadCount].min = min;
    strcpy(array[threadCount].file, filename);
    
    /*Increment threadCount variable for other threads.*/
    threadCount++;
    
    //unlock after saving at position `threadCount' (made sure no context switch before threadCount incremented)
    pthread_mutex_unlock(&lock);
    
    /*Close file.*/
    fclose(file1);
    
    /*Successful termination.*/
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    
    /*Only enter the while loop if files provided.*/
    if (argc < 2) {
        fprintf(stderr, "Enter a file!\n");
    }
    else {
        
        /*The int i is an array in order to keep track of "i" in different files.*/
        int i[argc-1];
        
        //set array to right size
        array = (FileArray*) malloc(sizeof(FileArray) * argc);
        
        /*initialize array*/
        int traversal;
        for (traversal = 0; traversal < argc-1; traversal++) {
            i[traversal] = 0;
        }
        
        /* the thread identifier */
        pthread_t tid[argc-1];
        
        /* set of attributes for the thread */
        pthread_attr_t attr;
        
        int count = 1;
        /*Loop until the last argument.*/
        while (count < argc) {
            
            /*Assign filename variable to argument.*/
            char *filename = argv[count];
            
            /* get the default attributes */
            pthread_attr_init(&attr);
            
            /* create the thread */
            pthread_create(&tid[count-1], NULL, file_count, filename);
            
            /*Only enter this loop when the count variable is at last argument. So create all threads before waiting or "joining" the threads.*/
            if (count+1 == argc) {
                
                /* now wait for the thread to exit.*/
                int travel = 0;
                FOR(travel, argc-1) {
                    pthread_join(tid[travel], NULL);
                }
                //local variable for parent process
                double min = INFINITY;
                double max = -INFINITY;
                
                /*Print*/
                int print_pos = 0;
                FOR(print_pos, argc-1) {
                    printf("%s\tSUM = %f       DIF = %f      MIN = %f      MAX = %f\n", array[print_pos].file, array[print_pos].sum, array[print_pos].diff, array[print_pos].min, array[print_pos].max);
                    
                    //reset min if less than current min
                    if (array[print_pos].min < min)
                        min = array[print_pos].min;
                    
                    //reset max if greater than current max
                    if (array[print_pos].max > max)
                        max = array[print_pos].max;
                    
                    //print max and min of entire file sets
                    if (print_pos == argc-2)
                        printf("MINIMUN = %f\tMAXIMUM = %f\n", min, max);
                }
            }
            
            count++;
        } //While count < argc end
        
        /*Reset array.*/
        free(array);
        
    } //File Count > 2
    return 0;
} //int main
