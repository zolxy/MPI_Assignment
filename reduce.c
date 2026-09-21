#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_val = (rank + 1) * 5;
    int global_sum = 0;

    printf("Rank %d has local_val = %d\n", rank, local_val);

    MPI_Reduce(&local_val, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Rank 0 computed global_sum = %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}
