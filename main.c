/* Aluno: Lucas Gomes Meneses */
#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void resetVetor(int v[], int n){
    for (int i = 0; i < n; i++){
        v[i] = 0;
    }
}

int main(int argc, char *argv[]){
    int npes, myrank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
   
    MPI_Finalize();
    return 0;
}
