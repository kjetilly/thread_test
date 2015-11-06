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


## Building and running on Euler cluster