# Thread Test

This is a simple program to make sure the machine we are running on actually gives us enough cores

## Requirements

Relatively light:
 * cmake (>= 2.6.0)
 * gcc (tested and works with 4.9.2, older version may or may not work)
 * boost-thread (tested with version 1.55)


## Building

Use cmake. *Remember -DCMAKE_BUILD_TYPE=Release*

### Example build

    mkdir build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make


## Running

Run as

    ./thread_test <number of threads to spawn>

eg.

    ./thread_test 16

## Running on LSF cluster (with MPI)

This is the important test, as it usually fails

use the following command (*remember, this is only for testing or "benchmarking"):

    bsub -W 00:30 -n 16 -R "span[ptile=16]" mpirun -np 1 -pernode ./thread_test 16

or we can submit with bind to none (usually works, somehow):

     bsub -W 00:30 -n 16 -R "span[ptile=16]" mpirun --bind-to-none -np 1 -pernode ./thread_test 16


## Running on LSF cluster (without MPI):
This usually works fine:

    bsub -W 00:30 -n 16  ./thread_test 16

## Expected results

* We expect that using multiple threads will be faster than using one thread
* If NUM_THREADS > 1, we do not expect "Clock time used" and "Time used" to be equal (or close).
* We should get the same result running through MPI with a single process, and running the same single process directly.
* We expect that (very) roughly 

     Clock time used = NUM_THREADS * Time used

## Example output of working configuration 

Done on Euler cluster 2015-11-06 (*without* MPI) (we do *not* expect the sum to be equal):

16 threads:

    Using NUM_THREADS = 16
    Time used: 16
    Ticks used: 171140000
    Clock time used (s): 171
    Sum = 35.5088
   
8 threads:

    Using NUM_THREADS = 8
    Time used: 22
    Ticks used: 173140000
    Clock time used (s): 173
    Sum = 36.0766

24 threads:

    Using NUM_THREADS = 24
    Time used: 12
    Ticks used: 174010000
    Clock time used (s): 174
    Sum = 36.1827
    
## Example of INCORRECT results

Anything where the runtime is not affected by the number of threads use, eg the following is NOT CORRECT:

    Using NUM_THREADS = 12
    Time used: 153
    Ticks used: 153230000
    Clock time used (s): 153
    Sum = 36.3002


## Building and running on Euler cluster

### Checking out code

    git clone https://github.com/kjetilly/thread_test.git


### Load modules

    module load cmake
    module load gcc/4.9.2
    module load boost/1.55.0

### Building

    cd thread_test
    mkdir build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make

### Submitting:

Try first with MPI (this will not give expected results):

    bsub -W 00:30 -n 16 -R "span[ptile=16]" mpirun -np 1 -pernode ./thread_test 16

then without (will give expected results):

     bsub -W 00:30 -n 16  ./thread_test 16

we can also add the --bind-to-none option to mpirun, and things will magically work:

     bsub -W 00:30 -n 16 -R "span[ptile=16]" mpirun --bind-to-none -np 1 -pernode ./thread_test 16

  
   
## Testing with Python / mpi4py

There is also a simple python program available that closely resembles real life use of mpi4py in Python calling a C++ executable. This test more closely resemble the simulation we actually do. 

The test program uses mpi4py and executes (as a binary executable) the generated C++ program. 

To submit it, use the following comand (without --bind-to-none we do not get the expected speed up) *RUN FROM BUILD DIRECTORY*:

     bsub -W 00:30 -n <T*N> -R "span[ptile=T]" mpirun --bind-to-none -pernode -np N python2.7 ../python_mpi.py <T>

where N is the number of nodes and T is the number of threads. Eg:

     bsub -W 00:30 -n 48 -R "span[ptile=48]" mpirun --bind-to-none -pernode -np 2 python2.7 ../python_mpi.py 48

The sole purpose of this test program is to make sure we can intermingle C++ binaries and Python in this way. 



