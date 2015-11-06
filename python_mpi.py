"""
Really simple mpi4py program.

This is simply a scaling test. Each rank will launch
one instance of 

    thread_test <N>

where <N> is the number of threads to use (via command line arguments specified. )
"""


from mpi4py import MPI
import os
import sys

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

if len(sys.argv) < 2:
    print ("Incorrect number of arguments given")
    print ("Program description:\n")
    print(__doc__)
    print("\nUsage:\n\tpython %s <number of threads to use per process>" % sys.argv[0])
    print("\nEg.\n\tpython %s 16" % sys.argv[0])
    sys.exit(1)

N = int(sys.argv[1])

commandToRun = "./thread_test %d" % N

print("Running command %s" % commandToRun)

os.system(commandToRun)
