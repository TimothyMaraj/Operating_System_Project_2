#include <iostream>
#include <pthread.h> 
#include <vector>
#include <random>
#include <algorithm>

pthread_mutex_t deckAccessMutex = PTHREAD_MUTEX_INITIALIZER; 

pthread_cond_t thread_one_turn_cv = PTHREAD_COND_INITIALIZER; 
pthread_cond_t thread_two_turn_cv = PTHREAD_COND_INITIALIZER;


pthread_cond_t startOfRound; 
pthread_cond_t end_of_round_cv;
pthread_cond_t endOfGame_cv; 








void* threadOne(void* arg) {
    // Lock the deckAccessMutex
    pthread_mutex_lock(&deckAccessMutex);
    

    
    // Print a message indicating that the thread is done
    std::cout << "Thread One done" << std::endl;
    
    // Unlock the deckAccessMutex
    pthread_mutex_unlock(&deckAccessMutex);
    // Signal to the waiting thread that it's its turn
    pthread_cond_signal(&thread_two_turn_cv);
    std::cout << "mutex unlcok" << std::endl;

    
    // Exit successfully
    return NULL;
}

void* threadTwo(void* arg)
{
    

    // Lock the mutex
    pthread_mutex_lock(&deckAccessMutex);
    std::cout << "One mutex unlcok" << std::endl;
    // Wait until signaled by threadOneTurnCV
    pthread_cond_wait(&thread_two_turn_cv, &deckAccessMutex);
std::cout << "two mutex end Wait" << std::endl;
    // Print out a message to indicate that thread two is done
    std::cout << "Thread two done" << std::endl;

    // Unlock the mutex
    pthread_mutex_unlock(&deckAccessMutex);

    // Return from the thread
    return NULL; 
}


/*

learned need to create waiting threads first then the thread that signals


*/

int main()
{
void* result;

pthread_t agentThread; 

pthread_t playerOne,playerTwo; 

pthread_create(&playerTwo,NULL,threadTwo,NULL);
pthread_create(&playerOne,NULL,threadOne,NULL);



pthread_join(playerOne, &result);
pthread_join(playerTwo, &result); 

printf("Thread exited with status %d\n", (intptr_t) result);

return 0; 
}