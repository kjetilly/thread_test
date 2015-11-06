#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <boost/thread/thread.hpp>

#include <memory>
#include <algorithm>

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Wrong number of arguments supplied." << std::endl;
    std::cout << "Usage:\n\t" << argv[0] << " <number of threads to use>" << std::endl;
    std::cout << std::endl;
    std::cout << "Example:\n\t" << argv[0] << " 16" << std::endl;
    return EXIT_FAILURE;
  }

  const int NUM_THREADS = atoi(argv[1]);
  std::cout << "Using NUM_THREADS = " << NUM_THREADS << std::endl;
  srand(time(NULL));
  const int M = 32;
  std::vector<double> u(M);
  double dt = 5e-9;
  double T = 1;

  for(int i = 0; i < M; i++) {
      // Make initial data random to avoid compiler optimization.
      u[i] = double(rand())/RAND_MAX;
  }

  std::vector<std::unique_ptr<boost::thread> > threads(NUM_THREADS);
  time_t start = time(NULL);
  clock_t clockStart = clock();
  int N = 1/dt;

  int workPerThread = (M + NUM_THREADS - 1) / NUM_THREADS;
  
  // Start threads
  for(int t = 0; t < NUM_THREADS; ++t) {
    const int startM = t * workPerThread;
    const int endM = std::min(M, (t + 1)* workPerThread);

    threads[t].reset(new boost::thread([N, dt, startM, endM,&u]() {
	  for(int i = startM; i < endM; ++i) {
	    
	    double ui = u[i];
	    for(int j = 0; j < N; j++) {
	      ui = ui + dt * cos(ui);
	    }
	    u[i] = ui;
	  }
	}));
  }

  // Synchronize threads
  for(auto& t : threads) {
    t->join();
  }

  time_t end = time(NULL);
  clock_t clockEnd = clock();
  std::cout << "Time used: " << (end - start) << std::endl;
  std::cout << "Ticks used: " << (clockEnd - clockStart) << std::endl;
  std::cout << "Clock time used (s): " << (clockEnd - clockStart)/ CLOCKS_PER_SEC << std::endl;
  // Do something with the data at the end to make sure compiler doesn't
  // optimize
  double sum = 0;
  for (size_t i = 0; i < M; i++ ) {
      sum += u[i];
  }
  std::cout << "Sum = " << sum << std::endl;

  
}
