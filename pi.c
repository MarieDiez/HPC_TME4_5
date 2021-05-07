#include <stdlib.h>
#include <stdio.h>  
#include <sys/time.h>

# define N 1000000000
double my_gettimeofday()
{
	struct timeval tmp_time;
	gettimeofday(&tmp_time, NULL);
	return tmp_time.tv_sec + (tmp_time.tv_usec * 1.0e-6L);
}

int main(){
	double start = my_gettimeofday();

    double pi=0;
    double x; 
    /*#pragma omp parallel for private(x)
    for (int i =0; i < N; i++){
        //double x;
        x = (double) i/N;
         #pragma omp atomic 
        //#pragma omp critical
        //{
            pi+=4.0/(1+ x*x);
        //}
    }*/
    #pragma omp parallel for reduction(+:pi) private(x) schedule(static,100)
    for (int i=0; i < N; i++){
        x = (double) i/N;
        pi+=4.0/(1+ x*x);
    }
    pi/=N;
    printf("%f\n",pi);

	double stop = my_gettimeofday();
	printf("Temps total de calcul : %g sec\n", stop - start);
}
