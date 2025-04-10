#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int N;             //number of threads
double X;          //argument for sin
long double* sum;  //array to store partial sums

void* computeSin(void* arg);
long double factorial(int num);

int main(int argc, char* argv[]) {
    if (argc != 3) { //check if user typed ./yourapp N X
        return 1;
    }

    N = atoi(argv[1]);   //ascii to integer
    X = atof(argv[2]);   //  ascii to double

    if (N <= 0) {
        return 1;
    }

    sum = malloc(sizeof(long double) * N);          //allocates memory for partial sums computed by threads
    pthread_t* threads = malloc(sizeof(pthread_t) * N);    //allocates memory for thread IDs
    /* malloc function allocates space for an object whose size is specified by size and whose value is indeterminate */

    for (int i = 0; i < N; i++) {
        int* index = malloc(sizeof(int));    // allocate memory to hold an integer | 
        *index = i;                          // store the current value of i into the allocated memory
        pthread_create(&threads[i], NULL, computeSin, (void*)index);   //ID, attr, entry func, args
    }

    for (int i = 0; i < N; i++) {     //wait here for all threads to finish
        pthread_join(threads[i], NULL);
    }

    long double answer = 0;             //final answer
    for (int i = 0; i < N; i++) {
        answer += sum[i];
    }

    printf("Computed sin(%f) = %.15Lf\n", X, answer);
    printf("Expected sin(%f) = %.15Lf\n", X, sinl(X));

    free(sum);
    free(threads);
    return 0;
}

long double factorial(int num) {
    long double f = 1;
    for (int i = 1; i <= num; i++) {  // start from one so it doesn't become 0 lol
        f *= i;
    }
    return f;
}

void* computeSin(void* arg) {
    int thread_index = *(int*)arg;  // cast the void* pointer into an int pointer then dereference it for the index
    free(arg);                      // free main's arg

    long double thread_sum = 0.0;
    int k = thread_index;

    while (1) {
        int sign = (k % 2 == 0) ? 1 : -1;  // if the index is even then the sign of the term is positive and vice versa
        int exponent = 2 * k + 1;
        long double numerator = sign * powl(X, exponent);
        long double denominator = factorial(exponent);
        long double term = numerator / denominator;

        printf("Thread %d adding term %d: %Lf\n", thread_index, k, term);

        if (fabsl(term) < 1e-16) {  //float absolute value long
            break;
        }

        thread_sum += term;
        k += N;
    }

    sum[thread_index] = thread_sum;
    return NULL;
}



/*
REFERENCES
https://man7.org/linux/man-pages/man3/pthread_create.3.html
https://www.w3schools.com/c/ref_stdlib_malloc.php
https://www.open-std.org/jtc1/sc22/WG14/www/docs/n1256.pdf
https://www.reddit.com/r/cprogramming/comments/ye2ghy/c_pthreads_how_to_generate_threads_in_a_loop/
https://stackoverflow.com/questions/8223742/how-to-pass-multiple-parameters-to-a-thread-in-c
https://www.w3schools.com/c/c_conditions_short_hand.php
https://en.cppreference.com/w/c/numeric/math/fabs
https://www.w3schools.com/c/c_memory_deallocate.php
https://arc.net/l/quote/igvbrzda
*/