/* 
  Modify the pthread_sum.c program to create a structure and pass the structure as argument to
the thread creation function instead of using global variables a, sum, N, and size.  
  Author: Milon Biswas

  To Compile: gcc -O first_code -Wall pthread_psum.c -lpthread
  To Run: ./first_code 4 1000
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    double *a;
    int N;
    int size;
    long tid;
} ThreadData;

double globalSum = 0.0; // Shared resource

void *compute(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int myStart, myEnd, myN, i;

    myN = data->N / data->size;
    myStart = data->tid * myN;
    myEnd = myStart + myN;
    if (data->tid == data->size - 1) myEnd = data->N;

    double mySum = 0.0;
    for (i = myStart; i < myEnd; i++) {
        mySum += data->a[i];
    }

    // Use mutex to update the global sum safely
    pthread_mutex_lock(&mutex);
    globalSum += mySum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <# of elements> <# of threads>\n", argv[0]);
        exit(-1);
    }

    int N = atoi(argv[1]);
    int size = atoi(argv[2]);
    double *a = (double *)malloc(sizeof(double) * N);
    for (long i = 0; i < N; i++) {
        a[i] = (double)(i + 1);
    }

    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * size);
    ThreadData *threadData = (ThreadData *)malloc(sizeof(ThreadData) * size);

    for (long i = 0; i < size; i++) {
        threadData[i] = (ThreadData){.a = a, .N = N, .size = size, .tid = i};
        pthread_create(&threads[i], NULL, compute, &threadData[i]);
    }

    for (int i = 0; i < size; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("The total is %g, it should be equal to %g\n", globalSum, ((double)N * (N + 1)) / 2);

    free(a);
    free(threads);
    free(threadData);
    pthread_mutex_destroy(&mutex);

    return 0;
}
