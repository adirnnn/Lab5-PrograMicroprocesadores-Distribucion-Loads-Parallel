#include <stdio.h>
#include <omp.h>

int main() {
    int variable1 = 0; //las variables que seran modificadas de manera paralela
    int variable2 = 0;
    int N = 10;  //numero de iteraciones del ciclo for

    printf("Resultados utilizando 'shared' para variable1 y 'private' para variable2:\n");

    //ciclo for
    #pragma omp parallel for shared(variable1) private(variable2) //a) y b)
    for (int i = 0; i < N; i++) {
        //variable1 shared que es compartida entre los hilos
        variable1 += i;

        //variable2 private que es privada para cada hilo
        variable2 = i * 2;

        //c)
        printf("Iteración %d: variable1 = %d, variable2 = %d (Hilo %d)\n", i, variable1, variable2, omp_get_thread_num());
    }

    printf("\nResultado final:\nvariable1 = %d\n", variable1);
    //nota: La variable2 no se imprime fuera del ciclo for ya que al ser privada no conserva su valor.

    return 0;
}
