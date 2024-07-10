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
#include <math.h>

/*Read and Write heads for the process.*/
#define READ 0
#define WRITE 1

/*facilitate for loops*/
#define FOR(i,n) for(i = 0; i < n; i++)

/* Struct that stores the output from child processes and is passed to parent process.*/
typedef struct {
    char file[101]; //filename
    double sum; //sum
    double diff; //difference
    double min; //minimum
    double max; //maximum
} FileArray;
    
FileArray *array; //declare array

/*Verify whether the pipe is created and working,*/
void err_sys(const char* x) {
    perror(x);
    exit(-1);
}

//main functions starts
int main(int argc, char *argv[]) {
    
    /*Only enter the while loop (process creation) if dataset files provided.*/
    if (argc < 2) {
        fprintf(stderr, "Enter a file!\n");
        exit(-1);
    }
    
    else {
        /*Variable count for traversing through each of the databases.*/
        int count = 1;
        
        /* "File_array" stores file name as well as the sum, mean, max,
         * and difference in entire data set of the the file.
         */
        array = (FileArray*) malloc(sizeof(FileArray)*argc);
        
        /*The pipe is a 2D array in order to keep track of reading for the parent.*/
        int fd[argc-1][2];
        
        /*Loop until the last argument.*/
        while (count < argc) {
            /*Assign filename to current argument.*/
            char *filename = argv[count];
            
            FILE *file1 = fopen(filename, "r");
            
            if (file1 == NULL) {
                fprintf(stderr, "Invalid File!\n");
                exit(-1);
            }
            
            /*Assign pid for the pipe tracking.*/
            int pid;
            
            /*Exit if pipe error.*/
            if (pipe (fd[count-1]) < 0) {
                err_sys("Pipe Error!");
            }
            
            /**"Fork" starts here.*/
            if ((pid = fork()) < 0) {
                err_sys("Fork Error!");
            }
            //Child Process
            if (pid == 0) {
                
                /*Close read pipe for child. It doesn't receive anything.*/
                close(fd[count-1][READ]);
                
                /*Local variables for the child process/*/
                char str[101];
                int q = 0;
                double sum = 0.0;
                double diff = 0.0;
                double min = INFINITY;
                double max = -INFINITY;
                
                /*Reading file until End Of File.*/
                while ((fscanf (file1, "%s", str)) != EOF) {
                    
                    /* This part of child process reads each of the
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
                /*calcualte difference and sum of max and min*/
                diff = max - min;
                sum = max + min;
                
                /*set `array' diff, sum, max and mean to calculated from file*/
                array[count-1].diff = diff;
                array[count-1].sum = sum;
                array[count-1].max = max;
                array[count-1].min = min;
                
                strcpy(array[count-1].file, argv[count]); //Copy filename
                
                /*The child is writing to the parent.*/
                write(fd[count-1][WRITE], &array[count-1], sizeof(FileArray));
                
                /*Pipe write closed. No more writing to parent.*/
                close(fd[count-1][WRITE]);
                
                /*Close file.*/
                fclose(file1);
                
                /*Successful termination.*/
                exit(0);
                
            } //child process end
            //Parent Process
            else {
                
                /*Close write pipe for parent.*/
                close(fd[count-1][WRITE]);
                
                /* The idea is to spawn of processes until we're at the last argument (file) and
                 * only after that the parent starts to read from the child.
                 */
                if (count+1 == argc) {
                    
                    //set local variables for parent process
                    int print_pos = 0;
                    double min = INFINITY;
                    double max = -INFINITY;
                    
                    /* From index zero to argument count, wait for the child process to finish
                     * and then copy the information to the parent array.
                     */
                    FOR(print_pos, argc-1) {
                        
                        /*wait for 1 process at a time, and then enter it in current `array'. Then print.*/
                        wait(NULL);
                        read(fd[print_pos][READ], &array[print_pos], sizeof(FileArray));
                        close(fd[print_pos][READ]); //close pipe
                        printf("%s\tSUM = %f       DIF = %f      MIN = %f      MIX = %f\n", array[print_pos].file, array[print_pos].sum, array[print_pos].diff, array[print_pos].min, array[print_pos].max);
                        
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
                
            }// parent end
            count++;
        } //While count < argc end
        
        /*Reset memory of arrays.*/
        free(array);
        
    } //File Count > 2
} //int main
