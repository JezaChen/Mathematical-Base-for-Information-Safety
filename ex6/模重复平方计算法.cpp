#include <iostream>

using namespace std;

//计算b ^n (mod m)
long long calc(long long _b, long long _n, long long _m)
{
    long long a = 1, b = _b;
    long long mask = 1;

    int picks = 0;
    long long temp = _n;
    while (temp)
    {
        picks++;
        temp /= 2;
    }

    for (int i = 0; i < picks; i++)
    {
        long long n = mask & _n;
        if (n)
            a = (a * b) % _m;
        b = (b * b) % _m;
        mask <<= 1;
    }

    return a;
}

int main()
{
    int b, n, m;
    cout << "输入底数:";
    cin >> b;
    cout << "输入幂:";
    cin >> n;
    cout<<"输入模:";
    cin>>m;
    cout<<"结果是:"<<calc(b,n,m)<<endl;
}
