#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
int main()
{
    srand(time(0));
    int number=rand()%100+1;
    int x;
    int iteration=0;
    cout<<" Welcome to the Number Guessing Game! "<<endl;
    cout<<"|\n|\n|\n"<<"Guess a number between 1 and 1000: \n"<<"|\n|\n|\n"<<endl;

    while(true)
    {
        cout<<"Enter your guess: ";
        cin>>x;
        iteration++;
        if(x==0)
        {
            cout<<"OOP'S you failed to guess the number: "<<endl;
            break;
        }
        if(x==number)
        {
            cout<<"Congratulations! You guessed the number in "<<iteration<<" attempts.";
            break;
        }
        else if(x>number)
        {
            cout<<"Too Long! try again: "<<endl;
        }
        else if (x<number)
        {
            cout<<"Too Short! try again: "<<endl;
        }
        cout<<"If you want to quit enter 0 in guess: "<<endl;
    }
    return 0;
}