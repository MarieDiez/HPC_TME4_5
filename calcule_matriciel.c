#include <stdlib.h>
#include <stdio.h> 
#include <omp.h> 
#include <stdlib.h> 
#include <sys/time.h>

// C = A * B
// matrice de N*N

#define N 750
double my_gettimeofday()
{
	struct timeval tmp_time;
	gettimeofday(&tmp_time, NULL);
	return tmp_time.tv_sec + (tmp_time.tv_usec * 1.0e-6L);
}
int main(){

    int i, j, k;
    int A[N][N], B[N][N], C[N][N];

    srand(100);

    for (i=0; i < N; i++){
        for (j=0; j < N; j++){
            C[i][j] = 0;
            A[i][j] = rand();
            B[i][j] = rand();
        }
    }    
    double start = my_gettimeofday();

    #ifdef _OPENMP
        int nb_thread = omp_get_max_threads();
        //printf("%d\n", nb_thread);
        omp_set_num_threads(nb_thread);
    #endif

    #pragma omp parallel for private(j,k) schedule(static, 1) // on parallelise la boucle la plus externe en openmp
    for (i=0; i < N; i++){
        //#pragma omp parallel for private(k)
        for (j=0; j < N; j++){
            //#pragma omp parallel for reduction(+:C[i][j])
            for (k=0; k < N; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }    
    }

	double stop = my_gettimeofday();
	printf("Temps total de calcul : %g sec\n", stop - start);
    return 0;
}
