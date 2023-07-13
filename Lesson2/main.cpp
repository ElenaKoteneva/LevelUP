#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    cout<<"Loading: ";
    for (int i=0; i<5; ++i)
    {
       cout<<" ."; 
       sleep(1);
    }
    
    cout<<endl<<"Loading is complete";
    return 0;
}