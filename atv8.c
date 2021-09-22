/* Aluno: Lucas Gomes Meneses */
#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* gerador de numeros aleatorios */
void numGenerator(int A[], int n){
    for (int i = 0; i < n; i++){
        A[i] = rand() % n;
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    int npes, myrank;
    int n = 100; /* tamalho do vetor */
    int A[n];
    int x = 39;
    int result; /* resultado final */
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    int n_local = (n / npes) + 1; /* tamanho do vetor local d cada processador */
    int A_local[n_local];
    if (myrank == 0){
        /* gerando numeros p/ vetor A*/
        numGenerator(A,n);
        /* dividindo o vetor entre os processadores */
        
        /* qtd de dados q cada processador deve receber */
        int counts[npes]; 
        for (int i = 0; i < npes; i++){
            counts[i] = n_local;
        }
        /* deslocamentos */
        int displ[npes];
        for (int i = 0; i < npes; i++){
            displ[i] = i*n_local;
        }
        MPI_Scatterv(A, counts, displ, MPI_INT, &A_local, n_local, MPI_INT, 0, MPI_COMM_WORLD);
         
    }else {
        MPI_Scatterv(NULL, NULL, NULL, MPI_INT, &A_local, n_local, MPI_INT, 0, MPI_COMM_WORLD);
        
    }

    //printf("A[0]:%d\tA[n]:%d\trank:%d\n",A_local[0],A_local[n_local-1], myrank);
    /* verificando a recorrencia */
    int rec = 0;  /* num recorrencia x */
    for (int i = 0; i < n_local; i++){
        if (x == A_local[i]){
            rec++;
        } 
    }
    MPI_Reduce(&rec,&result,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if (myrank == 0)
    {
        printf("O numero %d aparece no vetor A %d vez(es)!\n",x,result);
    }
    
    MPI_Finalize();
    return 0;
}
