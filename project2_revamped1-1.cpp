



#include <iostream>
#include <pthread.h> 
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       
#include <cstddef>
// Global Conditional and Mutex Section: 
pthread_mutex_t deckAccessMutex = PTHREAD_MUTEX_INITIALIZER; 



    // Turn Sync
pthread_cond_t thread_one_turn_cv = PTHREAD_COND_INITIALIZER; 
pthread_cond_t thread_two_turn_cv = PTHREAD_COND_INITIALIZER; 
pthread_cond_t thread_three_turn_cv = PTHREAD_COND_INITIALIZER;
pthread_cond_t thread_four_turn_cv = PTHREAD_COND_INITIALIZER;
pthread_cond_t thread_five_turn_cv = PTHREAD_COND_INITIALIZER;
pthread_cond_t thread_six_turn_cv = PTHREAD_COND_INITIALIZER;

    // Game synx
pthread_cond_t startOfRound_cv = PTHREAD_COND_INITIALIZER; 
pthread_cond_t endOfRound_cv = PTHREAD_COND_INITIALIZER;
pthread_cond_t endOfGame_cv = PTHREAD_COND_INITIALIZER; 



// Global Variables

std::vector<int> deck {1,2,3,4,5,6,7,8};

int randomSeed = 0; 
int targetCard = 0; 
int playerOneHand = 0; 
int playerTwoHand = 0; 

bool endGame = false; // used to loop all threads
bool oneIsAgent = false;
bool twoIsAgent = false;


// Helper Functions 

void shuffle_deck()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(deck.begin(), deck.end(), gen);
}

void drawTop()
{
    deck.erase(deck.begin()); 
}

int probOfSwap()
{
    srand(randomSeed); 
    return (rand() % 10 + 1); 
}
// Agent Thread 
void* agentThreadFunc(void* arg)
{
    int thread_id = 1;
    if(thread_id == 1)
    {

        std::cout << "Agent Function" << std::endl; 

        pthread_mutex_lock(&deckAccessMutex);
        oneIsAgent = true; 

        pthread_cond_signal(&thread_one_turn_cv); 

        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        std::cout<<"Agent End of Round"<<std::endl;
        pthread_mutex_unlock(&deckAccessMutex);

        // stops loops
         
    }
    std::cout << "Agent Exits" << std::endl;
    return NULL; 
    pthread_exit(NULL);
}

// Player Threads

void* playerOne(void* arg)
{

    pthread_mutex_lock(&deckAccessMutex);
    
    pthread_cond_wait(&thread_one_turn_cv,&deckAccessMutex);
    std::cout << "P1 Ends Waits" << std::endl;
    pthread_mutex_unlock(&deckAccessMutex);

    if(oneIsAgent)
    { 

        std::cout << "P1 Starts Turn" << std::endl;

        pthread_mutex_lock(&deckAccessMutex);
        
        
        // The round
        shuffle_deck(); 

        targetCard = deck.front();
        drawTop(); 

        playerTwoHand = deck.front(); 
        drawTop(); 

        std::cout << "P1 Starts Round" << std::endl;
        // start round 
        pthread_cond_signal(&thread_two_turn_cv);
        std::cout << "P2 Come in" << std::endl;

        std::cout << "P1 Starts Wait" << std::endl;

        
        // the wait for round to end 
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        std::cout<<"P1 End of Round"<<std::endl;
        pthread_mutex_unlock(&deckAccessMutex);
        oneIsAgent = false; 
        endGame = true;
    }
    else
    {
        std::cout << "Shouldn't Happen" << std::endl; 
    }


    std::cout << "Player One Exits" << std::endl;
    return NULL; 
    pthread_exit(NULL);
}

void* playerTwo(void* arg)
{
    pthread_mutex_lock(&deckAccessMutex);
    pthread_cond_wait(&thread_two_turn_cv,&deckAccessMutex);

    std::cout << "P1 this is P2 copy: Starting Turn" << std::endl;

    int temp = deck.front(); 
    drawTop(); 

    if(probOfSwap() > 5)
    {
        // keep hand 
        deck.push_back(temp); 
        temp = 0; 
    }
    else
    {
        // swap
        deck.push_back(playerTwoHand); 
        playerTwoHand = temp; 
    }

    if(targetCard == playerTwoHand)
    {
        std::cout << "Player Two Wins" << std::endl;
    }
    
    //pthread_cond_signal(&endOfRound_cv); // Signal the end of the round
    std::cout << "P2 Waits" << std::endl;
    pthread_cond_signal(&thread_three_turn_cv);

    pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);

    std::cout<<"P1 End of Round"<<std::endl;

    pthread_mutex_unlock(&deckAccessMutex);

    std::cout << "Player Two Exits" << std::endl;
    return NULL;
    pthread_exit(NULL); 
}

void* playerThree(void* arg)
{
    pthread_mutex_lock(&deckAccessMutex);
    pthread_cond_wait(&thread_three_turn_cv,&deckAccessMutex);



    pthread_cond_signal(&thread_four_turn_cv);
    pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
    pthread_mutex_unlock(&deckAccessMutex); 
    std::cout << "Player Three Exits" << std::endl;
    return NULL;
    pthread_exit(NULL);
}

void* playerFour(void* arg)
{
    pthread_mutex_lock(&deckAccessMutex);
    pthread_cond_wait(&thread_four_turn_cv,&deckAccessMutex);



    pthread_cond_signal(&thread_five_turn_cv);
    pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
    pthread_mutex_unlock(&deckAccessMutex); 
    std::cout << "Player Four Exits" << std::endl;
    return NULL;
    pthread_exit(NULL);    
}


void* playerFive(void* arg)
{
    pthread_mutex_lock(&deckAccessMutex);
    pthread_cond_wait(&thread_five_turn_cv,&deckAccessMutex);



    pthread_cond_signal(&thread_six_turn_cv);
    pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
    pthread_mutex_unlock(&deckAccessMutex); 
    std::cout << "Player five Exits" << std::endl;
    return NULL;
    pthread_exit(NULL);   
}

void* playerSix(void* arg)
{

    pthread_mutex_lock(&deckAccessMutex);
    pthread_cond_wait(&thread_six_turn_cv,&deckAccessMutex);

    

    std::cout << "End of Game" << std::endl;
    pthread_mutex_unlock(&deckAccessMutex);

    pthread_cond_broadcast(&endOfRound_cv);
    std::cout << "Player Six Exits" << std::endl;
    return NULL;
    pthread_exit(NULL);     
}


// Main

int main(int argc, char* argv[])
{

    randomSeed = atoi(argv[1]);

    void* result1;
    void* result2;
    void* result3;

    pthread_t agentThread,playerOneThread,playerTwoThread;

    pthread_create(&agentThread,NULL,agentThreadFunc,NULL);
    pthread_create(&playerOneThread,NULL,playerOne,NULL);
    pthread_create(&playerTwoThread,NULL,playerTwo,NULL);


    pthread_join(agentThread, &result1);
    pthread_join(playerOneThread, &result2);
    pthread_join(playerTwoThread, &result3); 


    printf("Thread exited with status %d\n", (intptr_t) result1);
    printf("Thread exited with status %d\n", (intptr_t) result2);
    printf("Thread exited with status %d\n", (intptr_t) result3);

    return 0; 
}