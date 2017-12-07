#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class CST
{
private:
    vector<long long> b;
    vector<long long> m;

    long long extgcd(long long _a, long long _b, long long &_x, long long &_y)
    {
        long long d = _a;
        if (_b != 0)
        {
            //数学公式
            // x1 = y2
            // y1 = x2 - (a / b) * y2
            d = extgcd(_b, _a % _b, _y, _x); //注意参数中x和y的位置调换了
            _y -= (_a / _b) * _x;
        }
        else
            _x = 1, _y = 0; //递归基
        return d;
    }

    long long solveInverse(const long long &num, const long long &mod)
    {
        long long x, y;
        extgcd(num, mod, x, y);
        return x;
    }

    long long cal(int i, long long N)
    {
        if (i < 0) return 0;
        N /= m[i];
        long long x_f = cal(i - 1, N);
        return x_f + (((b[i] - x_f) * solveInverse(N, m[i])) % m[i]) * N;
    }

public:
    CST(vector<long long> b, vector<long long> m) : b(std::move(b)), m(std::move(m))
    {}

    long long getAns()
    {
        long long N = 1;
        for (int i = 0; i < m.size(); i++)
            N *= m[i];
        long long ans = cal(b.size() - 1, N);
        if (ans < 0) ans += N;
        cout << "结果是 x = " << ans << " (mod " << N << ")" << endl;
    }
};

int main()
{
    long long b, m;
    vector<long long> B, M;
    while (cin >> b >> m)
    {
        B.push_back(b);
        M.push_back(m);
    }
    CST cst(B, M);
    cst.getAns();
}
