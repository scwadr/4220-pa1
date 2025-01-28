#include <stdio.h>
#include <ctime>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <mpi.h>
#include <omp.h>





double pi_calc(long int n) {
    
    // Write your code below
    ////////////////////////////////////////
    int rank, p;
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int bibis = n % p;
    long int sum = 0;
    for (int j = 0; j < (rank < bibis) ? n / p : n / p + 1; j++) {
        srand(time(NULL) + rank);
        long double x = (1.0 * rand()) / RAND_MAX;
        long double y = (1.0 * rand()) / RAND_MAX;
        if (x * x + y * y - 1.0 <= 0.0) {
            sum++;
        }
    }
    
    ////////////////////////////////////////
    return 0.0;
}
