#include <stdio.h>
#include <omp.h>

#define N 1000000  //a) define el valor de N como una constante grande

int main() {
    int sum = 0;
    double start_time, end_time;

    // b) medicion de tiempo
    start_time = omp_get_wtime();

    // Suma de los primeros N numeros naturales utilizando el ciclo for paralelo
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= N; i++) {
        sum += i;
    }

    // Finalizacion la medicion de tiempo
    end_time = omp_get_wtime();

    printf("La suma de los primeros %d numeros naturales es: %d\n", N, sum);
    printf("Tiempo de ejecucion: %f segundos\n", end_time - start_time);

    return 0;
}