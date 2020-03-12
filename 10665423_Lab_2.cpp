#include <iostream>
#include <mpi.h>
#include <chrono>

using namespace std;

int main(int argc, char *argv[]){
    
    //declaring the needed variables
    int process_rank, process_size, sum, start, end, accumulator;
    MPI::Status status;

//Beginning of parallel Program

    auto init = std::chrono::high_resolution_clock::now(); //starting time
    MPI::Init(argc, argv);

        process_rank = MPI::COMM_WORLD.Get_rank();
        process_size = MPI::COMM_WORLD.Get_size();
        sum = 0;

        start = (1000*process_rank) / process_size + 1;
        end = (1000*(process_rank+1)) / process_size;

    //Main task that would be parallelized for different processes to execute
        for(int i = start; i <= end; i++)
            sum += i;
            
        if(process_rank != 0){
            MPI_Send(&sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
            cout<<"I am process "<<process_rank<<" with accumulated value of "<<sum<<endl;
        }
        else
        {
            for(int j=1; j < process_size; j++){
                MPI_Recv(&accumulator, 1, MPI_INT, j, 1, MPI_COMM_WORLD, status);
                sum += accumulator;
                //cout<<"I am "<<process_rank<<" working on "<<accumulator<<endl;
            }

        }

        if (process_rank == 0)
            cout<<"The sum from 1 to 1000 is:\t"<<sum<<endl;
        
     MPI::Finalize();
     // closing time
    auto close = std::chrono::high_resolution_clock::now();
//End of parallel Program

//Execution time
    auto exec_time = std::chrono::duration_cast<std::chrono::milliseconds>(close - init);
    std::cout<<"Node:\t" << process_size <<"\t\t";
    std::cout<<"Execution time:\t" << exec_time.count() <<" milliseconds."<<std::endl;
    
    return 0;
}
