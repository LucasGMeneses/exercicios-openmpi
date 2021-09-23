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
    int max; /* maior numero */
    int min; /* menor numero */
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    
    int n = 10; /* tamalho do conjunto */
    int n_local = (n / npes); /* tamanho do vetor local d cada processador */
    int S_local[n_local];
    resetVetor(S_local, n_local);
    if (myrank == 0){
        /* Dividindo o conjunto entre os processadores */
        int S[] = {5, 1, 10, 80, 9, 4, 8, 3, 6, 0}; /* conjunto */
        
        /* qtd de dados q cada processador deve receber */
        int counts[npes];
        /* deslocamentos */
        int displ[npes];
        for (int i = 0; i < npes; i++){
            counts[i] = n_local;
            displ[i] = i*n_local;
        }
        MPI_Scatterv(S, counts, displ, MPI_INT, &S_local, n_local, MPI_INT, 0, MPI_COMM_WORLD);
         
    }else {
        MPI_Scatterv(NULL, NULL, NULL, MPI_INT, &S_local, n_local, MPI_INT, 0, MPI_COMM_WORLD);
        
    }

    /* verificando o valor minimo minimo */
    int min_local = S_local[0];
    for (int i = 0; i < n_local; i++){
        if (S_local[i]< min_local){
            min_local = S_local[i];
        }
        
    }
    MPI_Reduce(&min_local,&min,1,MPI_INT, MPI_MIN, 0,MPI_COMM_WORLD);
    /* verificando o valor minimo maximo */
    int max_local = S_local[0];
    for (int i = 0; i < n_local; i++){
        if (S_local[i] > max_local){
            max_local = S_local[i];
        } 
    }
    MPI_Reduce(&max_local,&max,1,MPI_INT, MPI_MAX, 0,MPI_COMM_WORLD);
    if (myrank == 0)
    {
        printf("O valor minimo eh %d e O valor maximo eh %d !\n",min, max);
    }
    
    MPI_Finalize();
    return 0;
}
