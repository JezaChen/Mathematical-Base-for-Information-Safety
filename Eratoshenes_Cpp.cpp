#include <iostream>
#include <cmath>

using namespace std;

bool is_prime(int x)  //检测x是否为素数
{
    int h=sqrt(x);
    for(int i=2;i<=h;i++)
        if(x%i==0) return false;
    return true;
}

int main()
{
    int n;
    while(cin>>n)
    {
        bool prime[n+1]; //用bool数组能省一定的存储空间
        for(int i=2;i<=n;i++) prime[i]=true;  //初始化
        prime[1]=false; //把1去掉
        int k= sqrt(n);
        for(int i=2;i<=k;i++)
        {
            if(prime[i]==false) continue; //如果该数不是素数，即意味着在之前的检测中已经被去掉，跳过
            if(is_prime(i)) //检验是否是素数
            {
                prime[i]=true;
                for(int j=2;i*j<=n;j++)
                    prime[i*j]=false;
            }
        }
        //print
        for(int i=1;i<=n;i++)
            if(prime[i])
                cout<<i<<',';
        cout<<"\b "<<endl; //擦除最后的逗号
    }
}