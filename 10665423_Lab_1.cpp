#include "mpi.h"
#include <iostream>

int main( int argc, char *argv[] )
{

int process_rank, process_size;

MPI::Init(argc, argv);

    process_rank = MPI::COMM_WORLD.Get_rank();
    process_size = MPI::COMM_WORLD.Get_size();
    std::cout << "I am " << process_rank << " of " << process_size <<"\n";

MPI::Finalize();

return 0;

}
