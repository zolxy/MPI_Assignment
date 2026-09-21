#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int token;
    int next = (rank + 1) % size;
    int prev = (rank - 1 + size) % size;

    if (rank == 0) {
        token = 1000;
        printf("Rank %d starting ring with token = %d\n", rank, token);
        MPI_Send(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        MPI_Recv(&token, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank %d received final token = %d from rank %d\n", rank, token, prev);
    } else {
        MPI_Recv(&token, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        token += 1;
        printf("Rank %d received token = %d from rank %d, passing to rank %d\n", rank, token, prev, next);
        MPI_Send(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
