#include <iostream>
#include <pthread.h> 
#include <vector>
#include <random>
#include <algorithm>



const int TRUE = 0; 

void* print_char(void* arg) {
    char c = *(char*)arg;
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

pthread_mutex_t deck_acess_mutex; 

pthread_cond_t thread_one_turn_cv; 
pthread_cond_t thread_two_turn_cv;

pthread_cond_t end_of_round_cv;


// Data structures for vars 

std::vector<int> deck {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
std::vector<int> thread_one_hand {0};
std::vector<int> thread_two_hand {0};

// global bool vars
bool one_is_agent = false; 
bool two_is_agent = false; 

bool endRound = false; 
bool threadOneStartsRound = false; 

// thread functions 

void* agent_function(void* arg)
{
    int thread_id = *((int*) arg);
    pthread_mutex_lock(&deck_acess_mutex);

    if(thread_id == 1)
    {
        one_is_agent = true; 
        
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
        std::cout << "Thread6"<<std::endl; 
    }
    
    

    while(!endRound)
    {
        pthread_cond_wait(&end_of_round_cv,&deck_acess_mutex);
    }
    // what needs to happen at the end of round? 
    pthread_mutex_unlock(&deck_acess_mutex);
    endRound = false; 
}

void* thread_one(void* arg)
{
    if(one_is_agent)
    {
        pthread_mutex_lock(&)

        


        pthread_mutex_ulock(&)
        
    }
    else
    {
        //conditional wait until turn
        while(!threadOneStartsRound)
        {

        }
    }
}

int main()
{



pthread_t agent_thread; 


// destroy mutexs
pthread_mutex_destroy(&deck_acess_mutex);

// destroy condition vars
pthread_cond_destroy(&thread_one_turn_cv);
pthread_cond_destroy(&thread_two_turn_cv);
pthread_cond_destroy(&end_of_round_cv);


pthread_exit (NULL); 
return 0; 
    
}