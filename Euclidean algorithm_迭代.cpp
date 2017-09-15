//CHEN JIANZHANG
#include <iostream>
#include <algorithm>

using namespace std;
int gcd(int a,int b)
{
    while(a%b) //使用迭代法，降低常数时间
    {
        int temp=b;  b=a%b;  a=temp;
    }
    return b;
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