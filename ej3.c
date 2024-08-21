#include <stdio.h>
#include <omp.h>

//función1, para calcular el factorial de un numero
long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

//función2, para generar la serie de Fibonacci hasta un n numero de términos
void fibonacci(int n) {
    long long first = 0, second = 1, next;
    printf("Serie de Fibonacci: ");
    for (int i = 0; i < n; i++) {
        if (i <= 1) {
            next = i;
        } else {
            next = first + second;
            first = second;
            second = next;
        }
        printf("%lld ", next);
    }
    printf("\n");
}

//función3, para encontrar el maximo en un arreglo
int max_in_array(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int number = 10;
    int fib_terms = 10;
    int arr[] = {1, 7, 3, 9, 2, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    //las tres funciones en paralelo usando OpenMP sections, cada una independiente de la otra
    #pragma omp parallel sections
    {
        //sección 1: funcion factorial
        #pragma omp section
        {
            long long fact = factorial(number);
            printf("El factorial de %d es: %lld\n", number, fact);
        }

        //sección 2: funcion Fibonacci
        #pragma omp section
        {
            printf("Generando la serie de Fibonacci con %d terminos:\n", fib_terms);
            fibonacci(fib_terms);
        }

        //sección 3: funcion arreglo
        #pragma omp section
        {
            int max = max_in_array(arr, arr_size);
            printf("El valor maximo en el arreglo es: %d\n", max);
        }
    }

    return 0;
}

