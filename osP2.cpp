#include <iostream>
#include <fstream>

#include <vector>
#include <random>

#include <algorithm>
#include <cstdlib>
#include <cstddef>

#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <pthread.h>       

// Global Conditional and Mutex Section: 
pthread_mutex_t deckAccessMutex = PTHREAD_MUTEX_INITIALIZER; 

    // Turn Sync
pthread_cond_t thread_






