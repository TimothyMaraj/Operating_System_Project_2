

        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
       
        threads = 0; 
        pthread_mutex_unlock(&deckAccessMutex);
    }
    else if(game_round == 4)
    {
        
        std::cout << "four is Agent " << std::endl; 