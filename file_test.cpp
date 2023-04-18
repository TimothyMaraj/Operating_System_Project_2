#include <fstream>
#include <iostream>


std::ofstream fileOut; 


void openFile()
{
    fileOut.open("testLogger2.txt", std::ios::out | std::ios::app);
}


void write1()
{
    

    fileOut << "write 1" << std::endl; 

    
}
void write2()
{
    

    fileOut << "write 2" << std::endl; 

   
}
void write3()
{
    

    fileOut << "write 3" << std::endl; 

   
}




int main()
{
    openFile();
    write1(); 
    write2(); 
    write3(); 
    fileOut.close();
    return 0; 
}