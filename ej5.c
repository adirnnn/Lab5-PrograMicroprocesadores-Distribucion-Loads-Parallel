#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 131072
#define THRESHOLD 1024  //threshold para el tamaño mínimo de la tarea

long count_key_parallel(long Nlen, long *a, long key) {
    long count = 0;

    //si el tamaño de la tarea es pequeño, se hace secuencial
    if (Nlen <= THRESHOLD) {
        for (long i = 0; i < Nlen; i++)
            if (a[i] == key) count++;
    } else {
        long mid = Nlen / 2;
        long count_left = 0, count_right = 0;

        #pragma omp task shared(count_left)
        count_left = count_key_parallel(mid, a, key);

        #pragma omp task shared(count_right)
        count_right = count_key_parallel(Nlen - mid, a + mid, key);

        #pragma omp taskwait  //Para sync de tareas

        count = count_left + count_right;
    }

    return count;
}

int main() {
    long a[N], key = 42, nkey = 0;
    
    //inicializacion del arreglo con valores aleatorios
    for (long i = 0; i < N; i++) a[i] = rand() % N;
    
    //valor 'key' en tres posiciones específicas
    a[N % 43] = key; 
    a[N % 73] = key; 
    a[N % 3] = key;

    //contar de ocurrencias key utilizando la versión paralela
    #pragma omp parallel
    {
        #pragma omp single  //solo un hilo inicia la recursion
        {
            nkey = count_key_parallel(N, a, key);
        }
    }

    printf("Numero de veces que 'key' aparece paralelamente: %ld\n", nkey);

    return 0;
}
