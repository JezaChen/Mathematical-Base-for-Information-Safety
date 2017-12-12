#include <iostream>
#include <cmath>
#include <ctime>
#include <random>

using namespace std;


unsigned gcd(const unsigned &a, const unsigned &b)
{
    if (a % b == 0) return b;
    return gcd(b, a % b);
}

unsigned selectNum(unsigned num)
{
    srand(static_cast<unsigned>(time(NULL)));
    return rand() % num;
}

unsigned pow(unsigned m, unsigned e, unsigned n) //幂运算直接采用最暴力的方法
{
    unsigned ans = 1;
    for (int i = 0; i < e; i++)
    {
        ans *= m;
        ans %= n;
    }
    return ans;
}

bool fermatCheck(unsigned num, int k)
{
    for (int i = 0; i < k; i++)
    {
        unsigned b = selectNum(num); //先选取一个数
        unsigned d = gcd(num, b); //计算最大公因数
        if (d > 1)
        {
            cout << "该数并不是素数！" << endl;
            return false;
        }
        unsigned r = pow(b, num - 1, num); //计算
        if (r != 1)
        {
            cout << "该数并不是素数！" << endl;
            return false;
        }
    }
    cout << num << "为素数的可能性大于 " << 1 - 1 / pow(2, k) << endl;
    return true;
}

int main()
{
    while(true)
    {
        cout << "请输入一个数: ";
        unsigned num;
        if(!(cin >> num)) break;
        cout << "输入测试的次数: ";
        int k;
        cin >> k;
        fermatCheck(num, k);
    }
}
