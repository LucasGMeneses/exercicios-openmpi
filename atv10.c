/* Aluno: Lucas Gomes Meneses */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
void resetVetor(int v[], int n){
    for (int i = 0; i < n; i++){
        v[i] = 0;
    }
}
void print(int A[], int n){
    for (int i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    int npes, myrank;
    int fat; /* resultado da fatorial */
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    
    int n = 9; /* numero */
    int n_local = (n / npes); /* tamanho do vetor local d cada processador */
    int S_local[n_local];
    resetVetor(S_local, n_local);
    if (myrank == 0){
        // gerando o fatorial de n
        int S[n];
        for ( int i = 0; i < n; i++){
            S[i] = i + 1;
        }
        print(S,n);
        /* Dividindo o vetor entre os processadores */
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

    /* realizando a fatorial */
    int fat_local = S_local[0];
    for (int i = 1; i < n_local; i++){
        fat_local = fat_local * S_local[i];
    }
    MPI_Reduce(&fat_local,&fat,1,MPI_INT, MPI_PROD, 0,MPI_COMM_WORLD);
    if (myrank == 0)
    {
        printf("O fatorial de %d eh %d !\n", n, fat);
    }
    
    MPI_Finalize();
    return 0;
}
