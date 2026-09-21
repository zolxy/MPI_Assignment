
#include <mpi.h>
#include <stdio.h>

#define N 4

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int A[N][N];
    int x[N];
    int local_row[N];
    int local_y = 0;
    int y[N];

    if (rank == 0) {
        int val = 1;
        for (int i = 0; i < N; i++) {
            x[i] = i + 1;
            for (int j = 0; j < N; j++) {
                A[i][j] = val++;
            }
        }

        printf("Matrix A:\n");
        for (int i = 0; i < N; i++) {
            printf("  [ ");
            for (int j = 0; j < N; j++) {
                printf("%2d ", A[i][j]);
            }
            printf("]\n");
        }

        printf("Vector x: [ ");
        for (int i = 0; i < N; i++) {
            printf("%d ", x[i]);
        }
        printf("]\n");
    }

    MPI_Bcast(x, N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(A, N, MPI_INT, local_row, N, MPI_INT, 0, MPI_COMM_WORLD);

    for (int j = 0; j < N; j++) {
        local_y += local_row[j] * x[j];
    }

    printf("Rank %d computed dot product = %d\n", rank, local_y);

    MPI_Gather(&local_y, 1, MPI_INT, y, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Result vector y = A * x: [ ");
        for (int i = 0; i < N; i++) {
            printf("%d ", y[i]);
        }
        printf("]\n");
    }

    MPI_Finalize();
    return 0;
}
