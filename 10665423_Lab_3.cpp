#include <iostream>
#include <chrono>
#include <time.h>
#include "mpi.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]){

    srand(time(0));
//Declaration of variables 
    int process_rank, process_size, sum = 10;
    MPI::Status status;

//Parallel program starts here
    MPI::Init(argc, argv);
        process_size = MPI::COMM_WORLD.Get_size();
        process_rank = MPI::COMM_WORLD.Get_rank();
        if(process_rank != 0)
        {
            MPI_Recv(&sum, 1, MPI::INT, process_rank-1, 0, MPI::COMM_WORLD, MPI_STATUS_IGNORE);
            cout<<"Process "<<process_rank - 1<<" Received "<<sum <<" from process " << process_rank<< endl;

        }
        else{
            sum += 2;
        }
        MPI_Send(&sum, 1, MPI::INT, (process_rank+1)%process_size, 0, MPI::COMM_WORLD);
        if(process_rank==0)
        { 
            MPI_Recv(&sum, 1, MPI::INT, process_size-1, 0, MPI::COMM_WORLD, MPI_STATUS_IGNORE);
            cout<<"Process "<<process_rank - 1<<" Received "<<sum <<" from process " <<process_size - 1<< endl;

        }

    MPI::Finalize();


    return 0;
}