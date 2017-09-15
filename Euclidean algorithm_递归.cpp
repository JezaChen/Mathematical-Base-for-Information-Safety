//CHEN JIANZHANG
#include <iostream>
#include <algorithm>

using namespace std;
int gcd(int a,int b)
{
    if( a % b ==0) return b; //µÝ¹é»ù
    return gcd(b,a % b);
}
int main()
{
    int a,b;
    cout<<"Input two numbers: ";
    while(cin>>a>>b)
    {
        //assert:a and b should not be negative
        //assert: a must be larger than b
        a=( a < 0 ? -a : a ); b = ( b < 0 ? -b : b);
        if( a<b )  swap( a, b );
        cout<<gcd(a,b)<<endl;
        cout<<"Input two numbers: ";
    }
}