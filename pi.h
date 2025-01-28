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
    for (int j = 0; j < ((rank < bibis) ? n / p + 1 : n / p); j++) 
    {
        srand(time(NULL) + rank);
        long double x = (1.0 * rand()) / RAND_MAX;
        long double y = (1.0 * rand()) / RAND_MAX;
        if (x * x + y * y - 1.0 <= 0.0) {
            sum++;
        }
    }
    std::cerr << sum << '\n';
    long int global_sum = 0;
    MPI_Reduce(&sum, &global_sum, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // Only rank 0 calculates the final Pi value
    if (rank == 0) 
    {
        return 4.0 * global_sum / n;
    }

    ////////////////////////////////////////
    return 0.0;
}
