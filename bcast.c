#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data = 0;
    if (rank == 0) {
        data = 42;
        printf("Rank 0 broadcasting data = %d\n", data);
    }

    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Rank %d received data = %d via broadcast\n", rank, data);

    MPI_Finalize();
    return 0;
}
