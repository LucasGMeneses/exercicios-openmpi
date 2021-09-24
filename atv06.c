#include <mpi.h>
#include <math.h>
#include <stdio.h>

void broadcast(int d, int my_id, int source, int data, MPI_Datatype type){
    int my_virtual_id = my_id ^ source;
    int mask = pow(2,d) - 1 ; 
    for (int i = d-1; i >= 0; i--){
        int nos = pow(2,i); // qtd de nos
        mask = mask ^ nos;
        if ((my_virtual_id & mask) == 0){
            if ((my_virtual_id & nos) == 0){
                int virtual_dest = my_virtual_id ^ nos;
                MPI_Send(&data, 1, type, virtual_dest ^ source, 0, MPI_COMM_WORLD);
            }
            else{
                int virtual_source = my_virtual_id ^ nos;
                MPI_Recv(&data, 1, type, virtual_source ^ source, 0, MPI_COMM_WORLD, NULL);
            }
        }
    }
    printf("data: %d\trank: %d\n", data, my_id);
}
int main(int argc, char *argv[]){
    int npes, myrank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        //d = 3 para np = 8
        broadcast(2, myrank, 0, 10, MPI_INT);
        
    MPI_Finalize();
    return 0;
}
