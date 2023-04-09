#include <iostream>
#include <pthread.h>


const int TRUE = 0; 

void* print_char(void* arg) {
    char c = *(char*)arg;
    std::cout << c << std::endl;
    return NULL;
}


int main()
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

    return 0;
}