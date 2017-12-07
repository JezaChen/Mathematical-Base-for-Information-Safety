#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

bool isPrime(int x)
{
    int ed = static_cast<int>(sqrt(x));
    for (int i = 2; i <= ed; i++)
    {
        if (x % i == 0) return false;
    }
    return true;
}

void DivideNumber(int num, vector<int> &V)
{
    int i = 2;
    bool isOnly = true;
    while (num > 1)
    {
        if (num % i == 0)
        {
            if (isOnly)
                V.push_back(i);
            isOnly = false;
            num /= i;
        }
        else
        {
            i++;
            isOnly = true;
        }
    }
}

int EulerFunction(int k)
{
    vector<int> V;
    DivideNumber(k, V);
    double ans = k;
    for (int i = 0; i < V.size(); i++)
    {
        ans *= (1 - 1 / (double) V[i]);
    }
    return static_cast<int>(ans);
}

int gcd(int a, int b)
{
    if (a % b == 0) return b;
    return gcd(b, a % b);
}

int selectE(int num)
{
    srand(time(NULL));
    while (true)
    {
        int temp = rand() % num;
        if (temp > 1 && gcd(temp, num) == 1)
            return temp;
    }
}

int extgcd(int a, int b, int &x, int &y)
{
    int d = a;
    if (b != 0)
    {
        //数学公式
        // x1 = y2
        // y1 = x2 - (a / b) * y2
        d = extgcd(b, a % b, y, x); //注意参数中x和y的位置调换了
        y -= (a / b) * x;
    }
    else
        x = 1, y = 0; //递归基
    return d;
}

int solveInverse(int num, int mod)
{
    int x, y;
    extgcd(num, mod, x, y);
    return x;
}

int charToInt(string x)
{
    //不用课本的方法
    //用ASCII码就行了
    int d = 26;
    int ans = 0;
    for (int i = 0; i < x.size(); i++)
    {
        ans *= d;
        ans += static_cast<int>(x[i] - 'a');
    }
    return ans;
}

string intToChar(int x, int numInGroup)
{
    int d = 26;
    string ans;
    while (x)
    {
        int tmp = x % d;
        ans.push_back(static_cast<char>(tmp + 'a'));
        x /= d;
        numInGroup--;
    }
    while (numInGroup > 0)
    {
        ans.push_back('a');
        numInGroup--;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int pow(int m, int e, int n)
{
    int ans = 1;
    for (int i = 0; i < e; i++)
    {
        ans *= m;
        ans %= n;
    }
    return ans;
}

int lock(int m, int e, int n)
{
    return pow(m, e, n);
}

int unlock(int c, int d, int n)
{
    return pow(c, d, n);
}


vector<string> RSA_Lock(string str, int numInGroup)
{
    int numOfGroups = str.size() / numInGroup;
    if (str.size() % numInGroup) numOfGroups++;

    string strs[numOfGroups];
    int nums[numOfGroups];

    cout << "可分为" << numOfGroups << "组。" << endl;

    for (int i = 0; i < numOfGroups; i++)
        strs[i] = str.substr(i * numInGroup, numInGroup);

    for (int i = 0; i < numOfGroups; i++)
        nums[i] = charToInt(strs[i]);

    int p, q;
    while (true)
    {
        cout << "请输入两个素数" << endl;

        cin >> p >> q;
        if (isPrime(p) && isPrime(q))
            break;
        else
        {
            cout << "其中一个不是素数" << endl;
        }
    }

    int n = p * q;
    int phy = (p - 1) * (q - 1);

    int e = selectE(phy);
    cout << "选择e为 " << e << endl;

    int d = solveInverse(e, phy);
    if (d < 0)
        d += phy;
    cout << "公钥为 (" << n << ", " << e << ")" << endl;
    cout << "私钥为 (" << n << ", " << d << ")" << endl;

    int lockNums[numOfGroups];
    for (int i = 0; i < numOfGroups; i++)
        lockNums[i] = lock(nums[i], e, n);
    vector<string> ans;
    for (int i = 0; i < numOfGroups; i++)
        ans.push_back(intToChar(lockNums[i], numInGroup));

    for (int i = 0; i < numOfGroups; i++)
        cout << "字符串" << strs[i] << "加密后形成的密文是" << ans[i] << endl;
    return ans;
}

string RSA_Unlock(vector<string> x, int numInGroup)
{
    int numOfGroups = x.size();
    int nums[numOfGroups];
    for (int i = 0; i < numOfGroups; i++)
        nums[i] = charToInt(x[i]);

    int ans[numOfGroups];
    cout << "请输入私钥d和n" << endl;
    int d;
    cin >> d;
    int n;
    cin >> n;
    for (int i = 0; i < numOfGroups; i++)
        ans[i] = unlock(nums[i], d, n);
    string result;
    for (int i = 0; i < numOfGroups; i++)
        if (i != numOfGroups - 1)
            result += intToChar(ans[i], numInGroup);
        else
            result += intToChar(ans[i], 1);

    cout << "解密成功。对应的字符串为" << result << endl;
}

int main()
{
    string s;
    cout << "输入需要加密的字符串" << endl;
    cin >> s;
    cout << "以多少个字符为一组? " << endl;
    int k;
    cin >> k;
    vector<string> ans = RSA_Lock(s, k);
    cout << "以多少个字符为一组?" << endl;
    int num;
    cin >> num;
    RSA_Unlock(ans, num);

}
