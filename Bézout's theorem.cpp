// CHEN JIANZHANG 2017/9/15
#include <iostream>
#include <algorithm>
using namespace std;
void Bezout(int& a,int& b)
{
    int s1,s2; int t1,t2; int q; int r1,r2;
    //init
    s1=1;s2=0;t1=0;t2=1;r1=a;r2=b;
    while(r2)
    {
        //Firstly, calculate the new q
        q=(r1/r2);
        //Secondly, calculate the new s and j
        int temp=s2;  s2=(-q)*s2+s1;  s1=temp;
        temp=t2;  t2=(-q)*t2+t1;  t1=temp;
        //Finally, caculate the new r
        temp=r2;  r2=r1%r2;  r1=temp;
    }
    cout<<"s= "<<s1<<", t="<<t1<<endl;
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
        Bezout(a,b);
        cout<<"Input two numbers: " ;
    }
}