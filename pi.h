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
    MPI_Comm_size(MPI_COMM_WORLD, &p); //get size (number of processors)
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //get rank (unique id of the current processor doing this job)
    
    srand(time(NULL) + rank); //choosing random seed, taken from pa1.pdf

    long int sum = 0; //number of points inside the circle counted by this processor
    int upper_bound = (rank < n % p) ? n / p + 1 : n / p; //how many iterations this processor will do total (each processor gets n/p and the rest n%p are uniformly redistributed between the first n%p)
    long double x, y; //pre-created x, y variables for the point (optimization, no time wasted re-creating them for every point)

    for (int j = 0; j < upper_bound; ++j) 
    {
        x = (1.0 * rand()) / RAND_MAX; //calculate random x,y between 0 and 1
        y = (1.0 * rand()) / RAND_MAX;
        sum += (x * x + y * y - 1.0 <= 0.0); //if (x,y) is inside the circle, sum is incremented
    }

    long int global_sum = 0; //variable to gather all sums from different processors
    MPI_Reduce(&sum, &global_sum, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD); //variables called &sum (1 variable) are gathered in the variable &global_sum, of type MPI_LONG (long int)
                                                                            //using the MPI_SUM(addition) operation on processor with rank=0, using the MPI_COMM_WORLD channel.


    //only rank 0 calculates the final pi value
    if (rank == 0) 
    {
        return 4.0 * global_sum / n;
    }

    ////////////////////////////////////////
    return 0.0;
}
