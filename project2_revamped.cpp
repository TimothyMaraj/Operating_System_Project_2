/*

stuck on threads one and two for some reason, idk why its stukSS



*/






#include <iostream>
#include <pthread.h> 
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       

// Global Conditional and Mutex Section: 
pthread_mutex_t deckAccessMutex; 

pthread_cond_t thread_one_turn_cv = PTHREAD_COND_INITIALIZER; 

pthread_cond_t threadOneToTwo_awk = PTHREAD_COND_INITIALIZER; 
pthread_cond_t threadOneToTwo_signal = PTHREAD_COND_INITIALIZER; 

pthread_cond_t threadTwoToThree_awk = PTHREAD_COND_INITIALIZER;


pthread_cond_t thread_two_turn_cv = PTHREAD_COND_INITIALIZER;
pthread_cond_t thread_three_turn_cv = PTHREAD_COND_INITIALIZER;

pthread_cond_t startOfRound_cv = PTHREAD_COND_INITIALIZER; 
pthread_cond_t endOfRound_cv = PTHREAD_COND_INITIALIZER;
pthread_cond_t endOfGame_cv = PTHREAD_COND_INITIALIZER; 



// Global Variables

std::vector<int> deck {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

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
    while(!endGame)
    {
        if(thread_id == 1)
        {
            // mutex lock * 
            // bool var is True now * 
            // signal start of thread one by cond_var
            // wait until thread one signals end of round 

            // note: if thread_id == 6 then endGame = True after 
            // that round finishes

            std::cout << "Agent Function" << std::endl; 

            pthread_mutex_lock(&deckAccessMutex);
            oneIsAgent = true; 

            pthread_cond_signal(&thread_one_turn_cv); 

            pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
            std::cout<<"Agent End of Round"<<std::endl;
            pthread_mutex_unlock(&deckAccessMutex);

            // stops loops
            endGame = true; 
        }
    }
    return NULL; 
}

// Thread 1 Function 

void* playerOne(void* arg)
{
    

    while(!endGame)
    {
        pthread_mutex_lock(&deckAccessMutex);
        pthread_cond_wait(&thread_one_turn_cv,&deckAccessMutex);
        pthread_mutex_unlock(&deckAccessMutex);

        if(oneIsAgent)
        {
            // grab the mutext *
            // wait to be called * 
            // shuffle deck * 
            // draw a target card * 
            // give thread two a card* 

            // start thread two: signal it 
            // wait until signal back 


            //notes
            // two singals back to Thread one that round is done
            // signale back to agent thread round is done

            // unlock the mutext 

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
            std::cout << "Houston Com ein" << std::endl;

            std::cout << "P1 Starts Wait" << std::endl;

            
            pthread_cond_wait(&threadOneToTwo_awk,&deckAccessMutex);
            std::cout << "Thread One AWK by Thread Two" << std::endl;
            pthread_cond_signal(&threadOneToTwo_awk);
            
            // the wait for round to end 
            pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
            std::cout<<"P1 End of Round"<<std::endl;
            pthread_mutex_unlock(&deckAccessMutex);
            oneIsAgent = false; 

        }
        else
        {
            std::cout << "Shouldn't Happen" << std::endl; 
        }

    }

    return NULL; 

}

void* playerTwo(void* arg)
{
    
// removed while loop and if statement 

            pthread_mutex_lock(&deckAccessMutex);
            pthread_cond_wait(&thread_two_turn_cv,&deckAccessMutex);
            std::cout << "two is starting" << std::endl;
            pthread_mutex_unlock(&deckAccessMutex);

            pthread_mutex_lock(&deckAccessMutex);
            std::cout << "TWo Is signalling " << std::endl; 
            pthread_cond_signal(&threadOneToTwo_awk); // Signal to playerOne to start the round
            pthread_cond_wait(&threadOneToTwo_awk,&deckAccessMutex);

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
            std::cout << "End of Game" << std::endl;
            pthread_mutex_unlock(&deckAccessMutex);

            pthread_cond_broadcast(&endOfRound_cv);
            
            
    

    return NULL; 
}









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