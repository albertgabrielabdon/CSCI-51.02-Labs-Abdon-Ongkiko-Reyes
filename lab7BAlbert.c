#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

int N;            
long double X; 
long double *sum;

long double factorial(int n) {
    long double output = 1;
    for (int i = 1; i <= n; ++i) {
        output *= i;
    }
    return output;
}

void *sine(void *ptr) {
    int thread = *(int*)ptr;  
    long double sin_sums = 0.0;
    
    for (int i = thread; ; i += N) {
        int exponent = 2 * i + 1;
        long double term = powl(X, exponent)/factorial(exponent);
        
        if (i % 2 == 1) {
            term = -term;
        }

        sin_sums += term;
        if (fabsl(term) < 1e-16) {
            break;
        }

        sleep(1);  
        printf("Thread %d, added term %d: %Lf\n", thread, i, term);
    }
    
    sum[thread] = sin_sums;  
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    
    N = atoi(argv[1]);          
    X = strtold(argv[2], NULL);  
    sum = (long double*) malloc(sizeof(long double) * N); 
    printf("N = %d, X = %Lf\n", N, X);

    pthread_t threads[N];
    int iret[N];

    for (int i = 0; i < N; ++i) {
        iret[i] = i;
        int ret = pthread_create(&threads[i], NULL, sine, &iret[i]);
        if (ret != 0) {
            fprintf(stderr, "error: %d\n", i);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
    }

    long double total_sum = 0.0;
    for (int i = 0; i < N; ++i) {
        total_sum += sum[i];
    }

    long double sinl_sum = sinl(X); 
    printf("sin(X) threads: %.15Lf\n", total_sum);
    printf("sinl(X) math.h: %.15Lf\n", sinl_sum);

    free(sum);
    return 0;
}
