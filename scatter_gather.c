#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_data[4];
    int recv_val;
    int result_data[4];

    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            send_data[i] = (i + 1) * 10;
        }
        printf("Rank 0 initial array: [%d, %d, %d, %d]\n", 
               send_data[0], send_data[1], send_data[2], send_data[3]);
    }

    MPI_Scatter(send_data, 1, MPI_INT, &recv_val, 1, MPI_INT, 0, MPI_COMM_WORLD);

    recv_val *= 2;
    printf("Rank %d processed local value = %d\n", rank, recv_val);

    MPI_Gather(&recv_val, 1, MPI_INT, result_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Rank 0 gathered results: [%d, %d, %d, %d]\n", 
               result_data[0], result_data[1], result_data[2], result_data[3]);
    }

    MPI_Finalize();
    return 0;
}
