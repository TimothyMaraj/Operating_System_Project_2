
/*

- need to implement fully all agent parts of each functions
= need to implement else part of each thread


*/


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

    // player hands
int playerOneHand = 0; 
int playerTwoHand = 0; 
int playerThreeHand = 0; 
int playerFourHand = 0;
int playerFiveHand = 0; 
int playerSixHand = 0;

    // game stats and varis
int game_round = 1; 
bool endGame = false;               // used to loop all threads
    // global bool functions
bool oneIsAgent = false;
bool twoIsAgent = false;
bool threeIsAgent = false; 
bool fourIsAgent = false; 
bool fiveIsAgent = false; 
bool sixIsAgent = false; 

std::ofstream loggerOut; 
// Helper Functions 

void openAndCreateFile()
{
    loggerOut.open("testLogger.txt", std::ios::out | std::ios::app);  
}

void closeFile()
{
    loggerOut.close();
}

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
    // use game_round to check track of whose 
    // 
    if(game_round == 1)
    {

        std::cout << "Agent Function" << std::endl; 

        pthread_mutex_lock(&deckAccessMutex);
        oneIsAgent = true; 

        std::cout << "Agent Function Selects One" << std::endl;
        pthread_cond_signal(&thread_one_turn_cv); 

        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        std::cout<<"Agent End of game_round"<<std::endl;
        pthread_mutex_unlock(&deckAccessMutex);

        // stops loops
         
    }
    else if(game_round == 2)
    {
        std::cout << "Agent Function" << std::endl; 

        pthread_mutex_lock(&deckAccessMutex);
        twoIsAgent = true; 

        std::cout << "Agent Function Selects Two" << std::endl; 
        pthread_cond_broadcast(&thread_two_turn_cv); 

        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        std::cout<<"Agent End of game_round"<<std::endl;
        pthread_mutex_unlock(&deckAccessMutex);
    }
    else if(game_round == 3)
    {
        std::cout << "Agent Function" << std::endl; 

        pthread_mutex_lock(&deckAccessMutex);
        threeIsAgent = true; 

        std::cout << "Agent Function Selects Three" << std::endl;
        pthread_cond_signal(&thread_three_turn_cv); 

        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        std::cout<<"Agent End of game_round"<<std::endl;
        pthread_mutex_unlock(&deckAccessMutex);
    }
    else if(game_round == 4)
    {
        std::cout << "Agent Function" << std::endl; 

        pthread_mutex_lock(&deckAccessMutex);
        fourIsAgent = true; 

        std::cout << "Agent Function Selects Four" << std::endl;
        pthread_cond_signal(&thread_four_turn_cv); 

        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        std::cout<<"Agent End of game_round"<<std::endl;
        pthread_mutex_unlock(&deckAccessMutex);
    }
    else if(game_round == 5)
    {
        std::cout << "Agent Function" << std::endl; 

        pthread_mutex_lock(&deckAccessMutex);
        fiveIsAgent = true; 

        std::cout << "Agent Function Selects Five" << std::endl;
        pthread_cond_signal(&thread_five_turn_cv); 

        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        std::cout<<"Agent End of game_round"<<std::endl;
        pthread_mutex_unlock(&deckAccessMutex);
    }
    else if(game_round == 6)
    {
        std::cout << "Agent Function" << std::endl; 

        pthread_mutex_lock(&deckAccessMutex);
        sixIsAgent = true; 

        std::cout << "Agent Function Selects Six" << std::endl;
        pthread_cond_signal(&thread_six_turn_cv); 

        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        std::cout<<"Agent End of game_round"<<std::endl;
        pthread_mutex_unlock(&deckAccessMutex);
    }
    else
    {
        std::cout << "Error: game_round Too Large or Too Big: " << game_round << std::endl;
    }
    

    std::cout << "Agent Exits" << std::endl;
    return NULL; 
    pthread_exit(NULL);
}

// Player Threads

void* playerOne(void* arg)
{

    pthread_mutex_lock(&deckAccessMutex);
    // This is to make sure one goes when it needs to go 
    pthread_cond_wait(&thread_one_turn_cv,&deckAccessMutex);
    std::cout << "P1 Ends Waits" << std::endl;
    pthread_mutex_unlock(&deckAccessMutex);
    
    if(oneIsAgent)
    { 

        std::cout << "P1 Starts Turn" << std::endl;
        pthread_mutex_lock(&deckAccessMutex);
        
        
        
        // The game_round
        shuffle_deck(); 

        targetCard = deck.front();
        drawTop(); 

        playerTwoHand = deck.front(); 
        drawTop(); 

        playerThreeHand = deck.front(); 
        drawTop(); 

        playerFourHand = deck.front(); 
        drawTop(); 

        playerFiveHand = deck.front(); 
        drawTop(); 

        playerSixHand = deck.front(); 
        drawTop(); 

        std::cout << "P1 Starts game_round" << std::endl;
        // start game_round 
       
        pthread_cond_signal(&thread_two_turn_cv);
        std::cout << "P2 Come in" << std::endl;
        
       
        std::cout << "P1 Starts Wait" << std::endl;

        
        // the wait for game_round to end 
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        std::cout<<"P1 End of game_round"<<std::endl;
        pthread_mutex_unlock(&deckAccessMutex);
        oneIsAgent = false; 
        game_round++; 
        
    }
    else
    {
        

        pthread_mutex_lock(&deckAccessMutex);
        std::cout << "Player One Went" << std::endl;

        if(!twoIsAgent)
            pthread_cond_signal(&thread_two_turn_cv);
        else 
            pthread_cond_signal(&thread_three_turn_cv);
        std::cout << "P1 Waits for End of Round" << std::endl;
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        pthread_mutex_unlock(&deckAccessMutex);
    }


    std::cout << "Player One Exits" << std::endl;
    return NULL; 
    pthread_exit(NULL);
}

void* playerTwo(void* arg)
{
    std::cout << "P2 Starts Turn" << std::endl;
    pthread_mutex_lock(&deckAccessMutex);
    // This is to make sure one goes when it needs to go
    std::cout << "P2 Starts Waits" << std::endl;
    pthread_cond_wait(&thread_two_turn_cv,&deckAccessMutex);
    std::cout << "P2 Ends Waits" << std::endl;
    pthread_mutex_unlock(&deckAccessMutex);

    if(twoIsAgent)
    {
        std::cout << "P2 Starts Turn" << std::endl; 
        pthread_mutex_lock(&deckAccessMutex);

        // the game_round
        targetCard = deck.front(); 
        drawTop(); 

        playerOneHand = deck.front(); 
        drawTop(); 

        playerThreeHand = deck.front(); 
        drawTop();

        playerFourHand = deck.front(); 
        drawTop();

        playerFiveHand = deck.front(); 
        drawTop(); 

        playerSixHand = deck.front(); 
        drawTop();

        pthread_cond_signal(&thread_one_turn_cv);
        std::cout << "P1 Come in" << std::endl;
       
       

        // the wait for game_round to end 
        std::cout << "P2 As Agent begins Wait" << std::endl;
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        std::cout<<"P2 End of game_round"<<std::endl;

        pthread_mutex_unlock(&deckAccessMutex);
        twoIsAgent = false; 
        game_round++;
    }
    else
    {
        
        
        pthread_mutex_lock(&deckAccessMutex);    
        std::cout << "Player Two Went" << std::endl;

        
        if(!threeIsAgent)
            pthread_cond_signal(&thread_three_turn_cv);
        else
            pthread_cond_signal(&thread_four_turn_cv); 

        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        pthread_mutex_unlock(&deckAccessMutex);
    }

        std::cout << "Player Two Exits" << std::endl;
        return NULL;
        pthread_exit(NULL); 
    
}

void* playerThree(void* arg)
{
    pthread_mutex_lock(&deckAccessMutex);
    // This is to make sure one goes when it needs to go 
    pthread_cond_wait(&thread_three_turn_cv,&deckAccessMutex);
    std::cout << "P3 Ends Waits" << std::endl;
    pthread_mutex_unlock(&deckAccessMutex);

    if(threeIsAgent)
    {
        pthread_mutex_lock(&deckAccessMutex);
        std::cout << "P3 Starts Turn" << std::endl;

       
        
        
        // The game_round
        shuffle_deck(); 

        targetCard = deck.front();
        drawTop(); 

        playerOneHand = deck.front(); 
        drawTop(); 

        playerTwoHand = deck.front(); 
        drawTop(); 

        playerFourHand = deck.front(); 
        drawTop(); 

        playerFiveHand = deck.front(); 
        drawTop(); 

        playerSixHand = deck.front(); 
        drawTop(); 

        std::cout << "P3 Starts game_round" << std::endl;
        // start game_round 
      
        pthread_cond_signal(&thread_one_turn_cv);
        std::cout << "P1 Come in" << std::endl;
        

        std::cout << "P3 Starts Wait" << std::endl;

        
        // the wait for game_round to end 
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        std::cout<<"P3 End of game_round"<<std::endl;
        pthread_mutex_unlock(&deckAccessMutex);
        threeIsAgent = false; 
        game_round++; 
    }
    else{

        
        
        pthread_mutex_lock(&deckAccessMutex);    
        std::cout << "Player Three Went" << std::endl;
        if(!fourIsAgent)
            pthread_cond_signal(&thread_four_turn_cv);
        else 
            pthread_cond_signal(&thread_five_turn_cv); 

        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        pthread_mutex_unlock(&deckAccessMutex); 
    }
    std::cout << "Player Three Exits" << std::endl;
    return NULL;
    pthread_exit(NULL);
}

void* playerFour(void* arg)
{
    pthread_mutex_lock(&deckAccessMutex);
    // This is to make sure one goes when it needs to go 
    pthread_cond_wait(&thread_four_turn_cv,&deckAccessMutex);
    std::cout << "P4 Ends Waits" << std::endl;
    pthread_mutex_unlock(&deckAccessMutex);

    if(fourIsAgent)
    {
        pthread_mutex_lock(&deckAccessMutex);
        std::cout << "P4 Starts Turn" << std::endl;

       
        
        
        // The game_round
        shuffle_deck(); 

        targetCard = deck.front();
        drawTop(); 

        playerOneHand = deck.front(); 
        drawTop(); 

        playerTwoHand = deck.front(); 
        drawTop(); 

        playerThreeHand = deck.front(); 
        drawTop(); 

        playerFiveHand = deck.front(); 
        drawTop(); 

        playerSixHand = deck.front(); 
        drawTop(); 

        std::cout << "P4 Starts game_round" << std::endl;
        // start game_round 
      
        pthread_cond_signal(&thread_one_turn_cv);
        std::cout << "P1 Come in" << std::endl;
        

        std::cout << "P4 Starts Wait" << std::endl;

        
        // the wait for game_round to end 
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        std::cout<<"P4 End of game_round"<<std::endl;
        pthread_mutex_unlock(&deckAccessMutex);
        fourIsAgent = false; 
        game_round++; 
    }
    else
    {
        
        
        pthread_mutex_lock(&deckAccessMutex);
        std::cout << "Player Four Went" << std::endl;

        if(!fiveIsAgent)
            pthread_cond_signal(&thread_five_turn_cv);
        else
            pthread_cond_signal(&thread_six_turn_cv);

            
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        pthread_mutex_unlock(&deckAccessMutex); 
    }

    std::cout << "Player Four Exits" << std::endl;
    return NULL;
    pthread_exit(NULL);    
}


void* playerFive(void* arg)
{
    pthread_mutex_lock(&deckAccessMutex);
    // This is to make sure one goes when it needs to go 
    pthread_cond_wait(&thread_five_turn_cv,&deckAccessMutex);
    std::cout << "P5 Ends Waits" << std::endl;
    pthread_mutex_unlock(&deckAccessMutex);

    if(fiveIsAgent)
    {
        pthread_mutex_lock(&deckAccessMutex);
        std::cout << "P5 Starts Turn" << std::endl;

       
        
        
        // The game_round
        shuffle_deck(); 

        targetCard = deck.front();
        drawTop(); 

        playerOneHand = deck.front(); 
        drawTop(); 

        playerTwoHand = deck.front(); 
        drawTop(); 

        playerThreeHand = deck.front(); 
        drawTop(); 

        playerFourHand = deck.front(); 
        drawTop(); 

        playerSixHand = deck.front(); 
        drawTop(); 

        std::cout << "P4 Starts game_round" << std::endl;
        // start game_round 
      
        pthread_cond_signal(&thread_one_turn_cv);
        std::cout << "P1 Come in" << std::endl;
        

        std::cout << "P4 Starts Wait" << std::endl;

        
        // the wait for game_round to end 
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        std::cout<<"P4 End of game_round"<<std::endl;
        pthread_mutex_unlock(&deckAccessMutex);
        fourIsAgent = false; 
        game_round++; 
    }
    else
    {
        
        
        pthread_mutex_lock(&deckAccessMutex);
        std::cout << "Player Five Went" << std::endl;

        if(!sixIsAgent)
        {
            pthread_cond_signal(&thread_six_turn_cv);
            pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
            pthread_mutex_unlock(&deckAccessMutex); 
        }
        else
        {
            // if six is agent then the thread signals end of round
            pthread_mutex_unlock(&deckAccessMutex);
            pthread_cond_broadcast(&endOfRound_cv);
        }
        

    }
    std::cout << "Player five Exits" << std::endl;
    return NULL;
    pthread_exit(NULL);   
}

void* playerSix(void* arg)
{
    pthread_mutex_lock(&deckAccessMutex);
    // This is to make sure one goes when it needs to go 
    pthread_cond_wait(&thread_six_turn_cv,&deckAccessMutex);
    std::cout << "P6 Ends Waits" << std::endl;
    pthread_mutex_unlock(&deckAccessMutex);

    if(sixIsAgent)
    {
        pthread_mutex_lock(&deckAccessMutex);
        std::cout << "P6 Starts Turn" << std::endl;

        
        
        
        // The game_round
        shuffle_deck(); 

        targetCard = deck.front();
        drawTop(); 

        playerOneHand = deck.front(); 
        drawTop(); 

        playerTwoHand = deck.front(); 
        drawTop(); 

        playerThreeHand = deck.front(); 
        drawTop(); 

        playerFourHand = deck.front(); 
        drawTop(); 

        playerFiveHand = deck.front(); 
        drawTop(); 

        std::cout << "P5 Starts game_round" << std::endl;
        // start game_round 
      
        pthread_cond_signal(&thread_one_turn_cv);
        std::cout << "P1 Come in" << std::endl;
        

        std::cout << "P6 Starts Wait" << std::endl;

        
        // the wait for game_round to end 
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        std::cout<<"P6 end of game_round"<<std::endl;
        pthread_mutex_unlock(&deckAccessMutex);
        fourIsAgent = false; 
        game_round++; 
    }
    else{
        
        
        pthread_mutex_lock(&deckAccessMutex);
        std::cout << "Player Six Went" << std::endl;

        std::cout << "End of Game" << std::endl;

        pthread_mutex_unlock(&deckAccessMutex);

        // will always signal the end of the round unless 
        // six is the agent 
        pthread_cond_broadcast(&endOfRound_cv);
    }
    std::cout << "Player Six Exits" << std::endl;
    return NULL;
    pthread_exit(NULL);     
}




// thread creation

void threadCreate()
{
    void* result1;
    void* result2;
    void* result3;
    void* result4;
    void* result5;
    void* result6;
    void* result7;
   

    pthread_t agentThread,playerOneThread,playerTwoThread,
              playerThreeThread,playerFourThread,
              playerFiveThread,playerSixThread;

    
    pthread_create(&playerOneThread,NULL,playerOne,NULL);
    pthread_create(&playerTwoThread,NULL,playerTwo,NULL);

    pthread_create(&playerThreeThread,NULL,playerThree,NULL);
    pthread_create(&playerFourThread,NULL,playerFour,NULL);

    pthread_create(&playerFiveThread,NULL,playerFive,NULL);
    pthread_create(&playerSixThread,NULL,playerSix,NULL);

    pthread_create(&agentThread,NULL,agentThreadFunc,NULL);

    

    pthread_join(playerOneThread, &result2);
    pthread_join(playerTwoThread, &result3); 

    pthread_join(playerThreeThread, &result4);
    pthread_join(playerFourThread, &result5); 

    pthread_join(playerFiveThread, &result6);
    pthread_join(playerSixThread, &result7); 

    pthread_join(agentThread, &result1);


    printf("Thread exited with status %d\n", (intptr_t) result1);
    printf("Thread exited with status %d\n", (intptr_t) result2);
    printf("Thread exited with status %d\n", (intptr_t) result3);
    printf("Thread exited with status %d\n", (intptr_t) result4);
    printf("Thread exited with status %d\n", (intptr_t) result5);
    printf("Thread exited with status %d\n", (intptr_t) result6);
    printf("Thread exited with status %d\n", (intptr_t) result7);
    std::cout << game_round << std::endl; 
    std::cout << std::endl; 
}

// Main


int main(int argc, char* argv[])
{

    randomSeed = atoi(argv[1]);
    for(int i = 0; i < 6; i++)
        threadCreate(); 
    

    return 0; 
}