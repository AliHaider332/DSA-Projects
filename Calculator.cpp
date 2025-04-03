#include<iostream>
using namespace std;
int main()
{
    int a,b;
    char x;
    cout<<" Enter the first number: "<<endl;
    cin>>a;
    cout<<" Enter the second number: "<<endl;
    cin>>b;
    cout<<"Enter the operation you want to perform(+,-,*,/)"<<endl;
    cin>>x;
    switch (x)
    {
    case '+':
    {
        cout<<"The sum of given numbers is: "<<a+b<<endl;
        break;
    }
    case '-':
    {
        cout<<"The subtraction of numbers is: "<<a-b<<endl;
        break;
    }
    case '*':
    {
        cout<<"The product of the numbers is: "<<a*b;
        break;
    }
    case '/':
    {
        if(b==0)
        {
            int x=0;
            while(x==0)
            {
                cout<<"Enter a correct divisor: "<<endl;
                cin>>b;
                if(b!=0)
                {
                    x=1;
                }
            }
        }
        cout<<"The division of numbers is: "<<a/b;
        break;
    }
    default:
    {
        cout<<"You enter a incorrect operation: "<<endl;
        break;
    }
    }
    return 0;
}
