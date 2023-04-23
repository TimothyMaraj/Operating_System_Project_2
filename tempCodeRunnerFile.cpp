            else
                pthread_cond_signal(&thread_four_turn_cv); 
            deck.push_back(playerTwoHand);
            threadExit++;
            return NULL;  
            pthread_exit(NULL); 
        }
    } 


 
    if(twoIsAgent)
    {
       
        pthread_mutex_lock(&deckAccessMutex);
       
        // the game_round
        targetCard = deck.front(); 
        std::cout << "PLAYER 2: Target Card " << targetCard << std::endl;
        drawTop(); 
        deck.push_back(targetCard);

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

        // the wait for game_round to end 
        if(DEBUG){std::cout << "PLAYER 2 BEGINS WAITING AS AGENT " << std::endl; }
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        if(DEBUG){std::cout << "PLAYER 2 ENDS WAITING AS AGENT " << std::endl; }
        pthread_mutex_unlock(&deckAccessMutex);
        twoIsAgent = false; 
       
    }
    else
    {
        
        
        pthread_mutex_lock(&deckAccessMutex);    
        
        // Logger:
            // PLAYER #: hand 5
        // draw a new card
        // Logger: 
            //Player #: draws 7
            // show hand
        // discard at random 
            // push back that card onto vector
            // Logger: (which card was discard formatt below)
                // PLAYER #: discards 7 at random 
        // Logger: 
            // PLAYER #: hand 5
        //checks win 

    // logger 
        int tempCard = 0; 
        loggerOut << "PLAYER 2: hand " << playerTwoHand << std::endl;
    // draw hand and log 
        tempCard = deck.front(); 
        drawTop(); 
        loggerOut << "PLAYER 2: draws " << tempCard << std::endl;
    // show hand 
        loggerOut << "PLAYER 2: hand " << "(" << playerTwoHand << ","<< tempCard << ")" << " <> " << "Target card is " << targetCard << std::endl;
        std::cout << "PLAYER 2: hand " << "" << playerTwoHand << ","<< tempCard << "" << std::endl; 
        
    // discard and check win    
        if(probOfSwap() > 5)
        {
            // push back cards 
            deck.push_back(playerTwoHand);
            deck.push_back(tempCard); 
            //logger 
            loggerOut << "PLAYER 2: discards "<< playerTwoHand << " at random" << std::endl;
            playerTwoHand = tempCard; 
            // check now if playerHand is winner 

            // check win 
            if(playerTwoHand == targetCard)
            {
                loggerOut << "PLAYER 2: wins round "<< game_round << std::endl;
                std::cout << "PLAYER 2: WIN" << std::endl; 
                endGame = true;
            }

        }
        else
        {
            deck.push_back(tempCard); 
            deck.push_back(playerTwoHand);
            loggerOut << "PLAYER 2: discards "<< tempCard << " at random" << std::endl;
            tempCard = 0; 
            // check win 
            if(playerTwoHand == targetCard)
            {
                std::cout << "PLAYER 2: WIN" << std::endl; 
                loggerOut << "PLAYER 2: wins round "<< game_round << std::endl;
                endGame = true;
            }
        }
        
        if(!threeIsAgent)
            pthread_cond_signal(&thread_three_turn_cv);
        else
            pthread_cond_signal(&thread_four_turn_cv); 
        if(DEBUG){std::cout << "2 is waiting " << std::endl; }

        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        pthread_mutex_unlock(&deckAccessMutex);
    }
    if(endGame)
        {
            loggerOut << "PLAYER 2: lost round " << game_round << std::endl;
            if(DEBUG){std::cout << "2 Exit " << std::endl; } 
        }

        threadExit++;
        return NULL;
        pthread_exit(NULL); 
    
}

void* playerThree(void* arg)
{ 
    
    pthread_mutex_lock(&deckAccessMutex);
    // This is to make sure one goes when it needs to go 
    threads++;
    pthread_cond_wait(&thread_three_turn_cv,&deckAccessMutex);
    
    pthread_mutex_unlock(&deckAccessMutex);

    if(!threeIsAgent)
    {
        if(endGame)
        {
            loggerOut << "PLAYER 3: lost round " << game_round << std::endl;
            if(DEBUG){std::cout << "3 Exit " << std::endl; }
            if(!fourIsAgent)
                pthread_cond_signal(&thread_four_turn_cv);
            else 
                pthread_cond_signal(&thread_five_turn_cv);  
            deck.push_back(playerThreeHand);
            threadExit++;
            return NULL;  
            pthread_exit(NULL); 
        }
    } 

    if(threeIsAgent)
    {
        pthread_mutex_lock(&deckAccessMutex);
   

       
        
        
        // The game_round
        shuffle_deck(); 

        targetCard = deck.front();
        drawTop(); 
        deck.push_back(targetCard);
        std::cout << "PLAYER 3: Target Card " << targetCard << std::endl;
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

        
        // start game_round 
      
        pthread_cond_signal(&thread_one_turn_cv);
        
        


        
        // the wait for game_round to end 
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);

        if(endGame)
        {
            loggerOut << "PLAYER 3: lost round " << game_round << std::endl;
            std::cout << "3 Exit " << std::endl;  
        }

        pthread_mutex_unlock(&deckAccessMutex);
        threeIsAgent = false; 
        
    }
    else{

        
        
        pthread_mutex_lock(&deckAccessMutex);    

        // Logger:
            // PLAYER #: hand 5
        // draw a new card
        // Logger: 
            //Player #: draws 7
            // show hand
        // discard at random 
            // push back that card onto vector
            // Logger: (which card was discard formatt below)
                // PLAYER #: discards 7 at random 
        // Logger: 
            // PLAYER #: hand 5
        //checks win 

    // logger 
        int tempCard = 0; 
        loggerOut << "PLAYER 3: hand " << playerThreeHand << std::endl;
    // draw hand and log 
        tempCard = deck.front(); 
        drawTop(); 
        loggerOut << "PLAYER 3: draws " << tempCard << std::endl;
    // show hand 
        loggerOut << "PLAYER 3: hand " << "(" << playerThreeHand << ","<< tempCard << ")" << " <> " << "Target card is " << targetCard << std::endl;
        std::cout << "PLAYER 3: hand " << "" << playerThreeHand << ","<< tempCard << "" << std::endl; 
        
    // discard and check win    
        if(probOfSwap() > 5)
        {
            // push back cards 
            deck.push_back(playerThreeHand);
            deck.push_back(tempCard); 
            //logger 
            loggerOut << "PLAYER 3: discards "<< playerThreeHand << " at random" << std::endl;
            playerOneHand = tempCard; 
            // check now if playerHand is winner 

            // check win 
            if(playerThreeHand == targetCard)
            {
                loggerOut << "PLAYER 3: wins round "<< game_round << std::endl;
                std::cout << "PLAYER 3: WIN" << std::endl; 
                endGame = true;
            }

        }
        else
        {
            deck.push_back(tempCard); 
            deck.push_back(playerThreeHand);
            loggerOut << "PLAYER 3: discards "<< tempCard << " at random" << std::endl;
            tempCard = 0; 
            // check win 
            if(playerThreeHand == targetCard)
            {
                std::cout << "PLAYER 3: WIN" << std::endl; 
                loggerOut << "PLAYER 3: wins round "<< game_round << std::endl;
                endGame = true;
            }
        }

        if(!fourIsAgent)
            pthread_cond_signal(&thread_four_turn_cv);
        else 
            pthread_cond_signal(&thread_five_turn_cv); 

        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        pthread_mutex_unlock(&deckAccessMutex); 
    }
    threadExit++;
    return NULL;
    pthread_exit(NULL);
}

void* playerFour(void* arg)
{ 
    
    pthread_mutex_lock(&deckAccessMutex);
    // This is to make sure one goes when it needs to go 
    threads++;
    pthread_cond_wait(&thread_four_turn_cv,&deckAccessMutex);
   
    pthread_mutex_unlock(&deckAccessMutex);

    if(!fourIsAgent)
    {
        if(endGame)
        {
            loggerOut << "PLAYER 4: lost round " << game_round << std::endl;
            if(DEBUG){std::cout << "4 Exit " << std::endl; }
            if(!fiveIsAgent)
            {
                pthread_cond_signal(&thread_five_turn_cv);
            }
            else
            {
            
                pthread_cond_signal(&thread_six_turn_cv);
            } 
            deck.push_back(playerFourHand);
            threadExit++;
            return NULL;  
            pthread_exit(NULL); 
        }
    } 


    if(fourIsAgent)
    {
        pthread_mutex_lock(&deckAccessMutex);
       

       
        
        
        // The game_round
        shuffle_deck(); 

        targetCard = deck.front();
        deck.push_back(targetCard);
        std::cout << "PLAYER 4: Target Card " << targetCard << std::endl;
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

        
        // start game_round 
      
        pthread_cond_signal(&thread_one_turn_cv);
        
        

       

        
        // the wait for game_round to end 
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);

        if(endGame)
        {
            loggerOut << "PLAYER 4: lost round " << game_round << std::endl;
            if(DEBUG){std::cout << "4 Exit " << std::endl;  }
        }

        pthread_mutex_unlock(&deckAccessMutex);
        fourIsAgent = false; 
      
    }
    else
    {
        
        
        pthread_mutex_lock(&deckAccessMutex);
       // Logger:
            // PLAYER #: hand 5
        // draw a new card
        // Logger: 
            //Player #: draws 7
            // show hand
        // discard at random 
            // push back that card onto vector
            // Logger: (which card was discard formatt below)
                // PLAYER #: discards 7 at random 
        // Logger: 
            // PLAYER #: hand 5
        //checks win 

    // logger 
        int tempCard = 0; 
        loggerOut << "PLAYER 4: hand " << playerFourHand << std::endl;
    // draw hand and log 
        tempCard = deck.front(); 
        drawTop(); 
        loggerOut << "PLAYER 4: draws " << tempCard << std::endl;
    // show hand 
        loggerOut << "PLAYER 4: hand " << "(" << playerFourHand << ","<< tempCard << ")" << " <> " << "Target card is " << targetCard << std::endl;
        std::cout << "PLAYER 4: hand " << "" << playerFourHand << ","<< tempCard << "" << std::endl; 
        
    // discard and check win    
        if(probOfSwap() > 5)
        {
            // push back cards 
            deck.push_back(playerFourHand);
            deck.push_back(tempCard); 
            //logger 
            loggerOut << "PLAYER 4: discards "<< playerFourHand << " at random" << std::endl;
            playerOneHand = tempCard; 
            // check now if playerHand is winner 

            // check win 
            if(playerFourHand == targetCard)
            {
                loggerOut << "PLAYER 4: wins round "<< game_round << std::endl;
                std::cout << "PLAYER 4: WIN" << std::endl; 
                endGame = true;
            }

        }
        else
        {
            deck.push_back(tempCard); 
            deck.push_back(playerFourHand);
            loggerOut << "PLAYER 4: discards "<< tempCard << " at random" << std::endl;
            tempCard = 0; 
            // check win 
            if(playerFourHand == targetCard)
            {
                std::cout << "PLAYER 4: WIN" << std::endl; 
                loggerOut << "PLAYER 4: wins round "<< game_round << std::endl;
                endGame = true;
            }
        }

        if(!fiveIsAgent)
        {
           
            pthread_cond_signal(&thread_five_turn_cv);
        }
        else
        {
        
            pthread_cond_signal(&thread_six_turn_cv);
        }

            
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);
        pthread_mutex_unlock(&deckAccessMutex); 
    }
    threadExit++;
    return NULL;
    pthread_exit(NULL);    
}

void* playerFive(void* arg)
{ 
    pthread_mutex_lock(&deckAccessMutex);
    // This is to make sure one goes when it needs to go 
    threads++;
    pthread_cond_wait(&thread_five_turn_cv,&deckAccessMutex);

    pthread_mutex_unlock(&deckAccessMutex);

   if(!fiveIsAgent)
    {
        if(endGame)
        {
            loggerOut << "PLAYER 5: lost round " << game_round << std::endl;
            if(DEBUG){std::cout << "5 Exit " << std::endl;} 
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
            deck.push_back(playerFiveHand);
            threadExit++;
            return NULL;  
            pthread_exit(NULL); 
        }
    } 

    if(fiveIsAgent)
    {
        pthread_mutex_lock(&deckAccessMutex);
        

       
        
        
        // The game_round
        shuffle_deck(); 

        targetCard = deck.front();
        drawTop(); 
        std::cout <<  "PLAYER 5: Target Card " << targetCard << std::endl;
        deck.push_back(targetCard);

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

        
        // start game_round 
      
        pthread_cond_signal(&thread_one_turn_cv);
       

        
        // the wait for game_round to end 
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);

        if(endGame)
        {
            loggerOut << "PLAYER 5: lost round " << game_round << std::endl;
            if(DEBUG){std::cout << "5 Exit " << std::endl;}  
        }

        pthread_mutex_unlock(&deckAccessMutex);
        fiveIsAgent = false; 
   
    }
    else
    {
        
        
        pthread_mutex_lock(&deckAccessMutex);
       
        // logger 
        int tempCard = 0; 
        loggerOut << "PLAYER 5: hand " << playerOneHand << std::endl;
    // draw hand and log 
        tempCard = deck.front(); 
        drawTop(); 
        loggerOut << "PLAYER 5: draws " << tempCard << std::endl;
    // show hand 
        loggerOut << "PLAYER 5: hand " << "(" << playerOneHand << ","<< tempCard << ")" << " <> " << "Target card is " << targetCard << std::endl;
        std::cout << "PLAYER 5: hand " << "" << playerOneHand << ","<< tempCard << "" << std::endl; 
        
    // discard and check win    
        if(probOfSwap() > 5)
        {
            // push back cards 
            deck.push_back(playerOneHand);
            deck.push_back(tempCard); 
            //logger 
            loggerOut << "PLAYER 5: discards "<< playerOneHand << " at random" << std::endl;
            playerOneHand = tempCard; 
            // check now if playerHand is winner 

            // check win 
            if(playerOneHand == targetCard)
            {
                loggerOut << "PLAYER 5: wins round "<< game_round << std::endl;
                std::cout << "PLAYER 5: WIN" << std::endl; 
                endGame = true;
            }

        }
        else
        {
            deck.push_back(tempCard); 
            deck.push_back(playerOneHand);
            loggerOut << "PLAYER 5: discards "<< tempCard << " at random" << std::endl;
            tempCard = 0; 
            // check win 
            if(playerOneHand == targetCard)
            {
                std::cout << "PLAYER 5: WIN" << std::endl; 
                loggerOut << "PLAYER 5: wins round "<< game_round << std::endl;
                endGame = true;
            }
        }

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
            pthread_cond_broadcast(&endOfRound_cv);
        }
        

    }
    threadExit++;
    return NULL;
    pthread_exit(NULL);   
}

void* playerSix(void* arg)
{ 
   
    pthread_mutex_lock(&deckAccessMutex);
    // This is to make sure one goes when it needs to go 
    threads++;

    pthread_cond_wait(&thread_six_turn_cv,&deckAccessMutex);
    if(DEBUG){std::cout << "6 End wait " << std::endl; }
    pthread_mutex_unlock(&deckAccessMutex);

    if(!sixIsAgent)
    {
        if(endGame)
        {
            loggerOut << "PLAYER 6: lost round " << game_round << std::endl;
           if(DEBUG){ std::cout << "6 Exit " << std::endl; }
            pthread_cond_broadcast(&endOfRound_cv);
            pthread_cond_signal(&endOfRound_cv);
            deck.push_back(playerSixHand);
            threadExit++;
            return NULL;  
            pthread_exit(NULL); 
        }
    } 
    if(sixIsAgent)
    {
        pthread_mutex_lock(&deckAccessMutex);
        
        
        
        
        // The game_round
        shuffle_deck(); 
        deck.push_back(targetCard);
        targetCard = deck.front();
        drawTop(); 
        
        std::cout << "PLAYER 6: Target Card " << targetCard << std::endl;

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

       
        // start game_round 
      
        pthread_cond_signal(&thread_one_turn_cv);
       
        
        // the wait for game_round to end 
        pthread_cond_wait(&endOfRound_cv,&deckAccessMutex);

        if(endGame)
        {
            loggerOut << "PLAYER 6: lost round " << game_round << std::endl;
            if(DEBUG){std::cout << "6 Exit " << std::endl; } 
        }

        pthread_mutex_unlock(&deckAccessMutex);
        sixIsAgent = false; 
    
    }
    else{
        
        
        pthread_mutex_lock(&deckAccessMutex);
       
       // logger 
        int tempCard = 0; 
        loggerOut << "PLAYER 6: hand " << playerSixHand << std::endl;
    // draw hand and log 
        tempCard = deck.front(); 
        drawTop(); 
        loggerOut << "PLAYER 6: draws " << tempCard << std::endl;
    // show hand 
        loggerOut << "PLAYER 6: hand " << "(" << playerSixHand << ","<< tempCard << ")" << " <> " << "Target card is " << targetCard << std::endl;
        std::cout << "PLAYER 6: hand " << "" << playerSixHand << ","<< tempCard << "" << std::endl; 
        
    // discard and check win    
        if(probOfSwap() > 5)
        {
            // push back cards 
            deck.push_back(playerSixHand);
            deck.push_back(tempCard); 
            //logger 
            loggerOut << "PLAYER 6: discards "<< playerSixHand << " at random" << std::endl;
            playerSixHand = tempCard; 
            // check now if playerHand is winner 

            // check win 
            if(playerSixHand == targetCard)
            {
                loggerOut << "PLAYER 6: wins round "<< game_round << std::endl;
                std::cout << "PLAYER 6: WIN" << std::endl; 
                endGame = true;
            }

        }
        else
        {
            deck.push_back(tempCard); 
            deck.push_back(playerSixHand);
            loggerOut << "PLAYER 6: discards "<< tempCard << " at random" << std::endl;
            tempCard = 0; 
            // check win 
            if(playerOneHand == targetCard)
            {
                std::cout << "PLAYER 6: WIN" << std::endl; 
                loggerOut << "PLAYER 6: wins round "<< game_round << std::endl;
                endGame = true;
            }
        }

        pthread_mutex_unlock(&deckAccessMutex);

        // will always signal the end of the round unless 
        // six is the agent 
        pthread_cond_broadcast(&endOfRound_cv);
    }

    threadExit++;
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

    if(DEBUG)
    {
        printf("Thread exited with status %d\n", (intptr_t) result1);
        printf("Thread exited with status %d\n", (intptr_t) result2);
        printf("Thread exited with status %d\n", (intptr_t) result3);
        printf("Thread exited with status %d\n", (intptr_t) result4);
        printf("Thread exited with status %d\n", (intptr_t) result5);
        printf("Thread exited with status %d\n", (intptr_t) result6);
        printf("Thread exited with status %d\n", (intptr_t) result7);
    }
    
    //std::cout << game_round << std::endl; 
    //std::cout << std::endl; 
}

// Main


int main(int argc, char* argv[])
{

   // randomSeed = atoi(argv[1]);

    randomSeed = 9; 
    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    openAndCreateFile(); 
    for(int i = 1; i < 7; i++)
        threadCreate(); 
    closeFile(); 
    return 0; 
}