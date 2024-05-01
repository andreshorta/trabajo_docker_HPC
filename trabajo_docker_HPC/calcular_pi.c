#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

double calcularIteraciones(long long int inicio, long long int fin) {
    double suma_local = 0;
    for (long long int i = inicio; i <= fin; i++) {
        suma_local += (i % 2 == 0) ? -1 : 1 / (2.0 * i + 1);
    }
    return suma_local;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    processor_name[name_len] = '\0'; // Agregar el carácter nulo al final de la cadena

    long long int num_iteraciones = 9000000000; // 9x10^9
    long long int iteraciones_por_proceso = num_iteraciones / size;
    long long int inicio = iteraciones_por_proceso * rank;
    long long int fin = inicio + iteraciones_por_proceso - 1;

    if (rank == size - 1) {
        // Ajuste para el último proceso
        fin += num_iteraciones % size;
    }

    double tiempo_inicio = MPI_Wtime();
    double suma_local = calcularIteraciones(inicio, fin);

    double suma_total;
    MPI_Reduce(&suma_local, &suma_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double pi = 4 * suma_total;
        printf("Valor aproximado de PI: %f\n", pi);
        double tiempo_fin = MPI_Wtime();
        double tiempo_total = tiempo_fin - tiempo_inicio;
        printf("Tiempo de ejecución: %f segundos\n", tiempo_total);
    }

    printf("host %s\n", rank, processor_name); // Mostrar el nombre del host

    MPI_Finalize();
    return 0;
}
