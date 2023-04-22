/*
- implementing the else part of the thread one function
  check photots for details


*/


#include <iostream>
#include <pthread.h> 
#include <vector>
#include <random>
#include <algorithm>



const int TRUE = 0; 
int count = 0; 
bool endThread = true; 

void* print_char(void* arg) {
    char c = *(char*)arg;
    count++; 
    if(count == 3)
        pthread_exit(NULL); 
    std::cout << c << std::endl;
    return NULL;
}


void threads()
{
    std::string str = "hello world!";
    int n = str.length();

    pthread_t threads[n];
    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, print_char, &str[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }   
}


void vector_example()
{
    std::vector<int> v; // create an empty vector
    v.push_back(10);    // add element 10 to the vector
    v.push_back(20);    // add element 20 to the vector
    v.push_back(30); 
    std::cout << v[1] << std::endl;  // prints 20
    std::cout << v.at(12) << std::endl; // also prints 20
}

void* hello_world(void* arg)
{   // lesson learned here: the parameter should still be void* (a void pointer)
    // gather the value from the varaible after
    // casting to the poiter of the apporiate type 
    // then deref
    int thread_id = *((int*) arg);
    std::cout <<"thread: "<< thread_id <<" says hello world"<<std::endl;
    pthread_exit(NULL);
    // return NULL not 'return 0'
    // will exit the program
    return NULL; 
}

void hello_threaded()
{
    pthread_t thread; 
    int return_status; 
    long thread_id =0;
    // lesson learned here: after casting as void* remeber to pass the reference not the variable
    pthread_create(&thread, NULL,hello_world,(void*)&thread_id);

    std::vector<pthread_t> v(5); 
    for(int i = 0; i < 5; i++)
    {   std::cout << i << std::endl; 
        pthread_create(&v[i],NULL,hello_world,(void*)&i);
    }
    pthread_exit(NULL);  
}





// Mutex and Condition var: 

pthread_mutex_t deckAccessMutex; 

pthread_cond_t thread_one_turn_cv; 
pthread_cond_t thread_two_turn_cv;


pthread_cond_t startOfRound; 
pthread_cond_t end_of_round_cv;
pthread_cond_t endOfGame_cv; 

// Data structures for vars 

std::vector<int> deck {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
std::vector<int> agentHand;
std::vector<int> thread_one_hand;
std::vector<int> thread_two_hand;

// global bool vars
bool one_is_agent = false; 
bool two_is_agent = false; 

bool threadOneStartsRound = false;
bool threadtwoStartsRound = false;



bool startRound = false; 
bool endRound = false; 
bool endGame = false; 


// helper functions


void shuffle_deck()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(deck.begin(), deck.end(), gen);
}




// thread functions 

void* agentFuntion(void* arg)
{
    int thread_id = *((int*) arg);
    pthread_mutex_lock(&deckAccessMutex);

    if(thread_id == 1)
    {
        one_is_agent = true; 
        startRound = true;
        
    }
    if(thread_id == 2)
    {
        two_is_agent = true; 
    }
    if(thread_id == 3)
    {
        std::cout << "Thread3"<<std::endl; 
    }
    if(thread_id == 4)
    {
        std::cout << "Thread4"<<std::endl; 
    }
    if(thread_id == 5)
    {
        std::cout << "Thread5"<<std::endl; 
    }
    if(thread_id == 6)
    {
        std::cout << "Thread6"<< std::endl; 
    }
    
    

    while(!endRound)
    {
        pthread_cond_wait(&end_of_round_cv,&deckAccessMutex);
    }
    // what needs to happen at the end of round? 
    pthread_mutex_unlock(&deckAccessMutex);
    endRound = false; 
    pthread_exit(NULL);
    return NULL;
}

void* thread_one(void* arg)
{
    while(!startRound)

    if(one_is_agent)
    {
        pthread_mutex_lock(&deckAccessMutex);

        shuffle_deck();
        agentHand.push_back(deck.front());
        //give other threads their hand
        thread_two_hand.push_back(deck.front());

        pthread_cond_signal(&startOfRound);

        while(!endRound)
        { 
            std::cout << "agent is player one" << std::endl; 
            pthread_cond_wait(&end_of_round_cv,&deckAccessMutex);}

        pthread_mutex_unlock(&deckAccessMutex);
        
    }
    else
    {
        //conditional wait until turn

        pthread_mutex_lock(&deckAccessMutex);
        while(!threadOneStartsRound)
        {std::cout << "Thread One Start0" << std::endl;
            pthread_cond_wait(&thread_one_turn_cv,&deckAccessMutex);
        }
        std::cout << "Thread One Start" << std::endl;
        pthread_cond_signal(&endOfGame_cv);
    }

    pthread_exit(NULL);
    pthread_exit(NULL);
    return NULL;
}

int main()
{

threads(); 

pthread_exit (NULL); 
return 0; 
    
}