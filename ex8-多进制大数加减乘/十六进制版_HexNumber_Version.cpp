#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

class HexNumber
{
private:
    string value;

    //因为需要大量在字符和数字转来转去，不妨弄个函数，编译器优化的时候会将其内联
    //注意的是，在ASCII码中字符和数字是没有连在一起的，这是个坑
    static int Char2Int(char k)
    {
        int kInt;
        if ('0' <= k && k <= '9')
            kInt = k - '0';
        else
            kInt = (k - 'A') + 10; //记得加10
        return kInt;
    }

    static char Int2Char(int k)
    {
        char c;
        if (k < 10)
            return static_cast<char>('0' + k);
        else
            return static_cast<char>('A' + k - 10);
    }

    static string singleMultiplication(const string &a, char k)
    {
        if (k == '0')
            return "0";
        int kInt = Char2Int(k);
        //十六进制的单位乘更不得了

        string value = a;
        reverse(value.begin(), value.end());
        string ans;
        int c;
        int c_in = 0;
        for (int i = 0; i < value.size(); i++)
        {
            int valueInt;
            c = (Char2Int(value[i])) * kInt + c_in;
            //不用 c >= 8
            c_in = c / 16;
            c %= 16;
            ans.push_back(Int2Char(c));
        }
        if (c_in) //记得处理多出来的位
            ans.push_back(Int2Char(c_in));
        reverse(ans.begin(), ans.end());
        return ans;
    }

    //往后面塞零
    static string putZero(const string &a, int k)
    {
        if (a == "0")
            return a;
        string res = a;
        for (int i = 0; i < k; i++)
            res.push_back('0');
        return res;
    }

public:
    explicit HexNumber(string _value) : value(std::move(_value))
    {}

    string getValue() const
    { return value; }

    bool operator<(const HexNumber &a)
    {
        if (value.size() < a.getValue().size())
            return true;
        if (value.size() > a.getValue().size())
            return false;
        for (int i = 0; i < value.size(); i++)
        {
            if (Char2Int(value[i]) < Char2Int(a.getValue().at(i))) return true;
            if (Char2Int(value[i]) > Char2Int(a.getValue().at(i))) return false;
        }

        return false; //相等
    }


    HexNumber operator+(const HexNumber &a)
    {
        string valueTemp = value;
        string aTemp = a.getValue();
        string res;

        reverse(valueTemp.begin(), valueTemp.end());
        reverse(aTemp.begin(), aTemp.end());

        int minSize = static_cast<int>(min(valueTemp.size(), aTemp.size()));
        int c; //一位相加产生的结果
        bool c_in = false; //进位标记
        for (int i = 0; i < minSize; i++)
        {
            c = ((c_in) ? (Char2Int(valueTemp[i]) + Char2Int(aTemp[i]) + 1) : (Char2Int(valueTemp[i]) +
                                                                               Char2Int(aTemp[i])));
            if (c >= 16)
            {
                c_in = true;
                c -= 16;
            }
            else
                c_in = false;
            res.push_back(Int2Char(c));
        }
        for (int i = minSize; i < valueTemp.size(); i++)
        {
            c = ((c_in) ? (Char2Int(valueTemp[i]) + 1) : (Char2Int(valueTemp[i]))); //注意这时候不应该减'0'了！
            if (c >= 16)
            {
                c_in = true;
                c -= 16;
            }
            else
                c_in = false;
            res.push_back(Int2Char(c));
        }
        for (int i = minSize; i < aTemp.size(); i++)
        {
            c = ((c_in) ? (Char2Int(aTemp[i]) + 1) : (Char2Int(aTemp[i]))); //注意这时候不应该减'0'了！
            if (c >= 16)
            {
                c_in = true;
                c -= 16;
            }
            else
                c_in = false;
            res.push_back(Int2Char(c));
        }

        if (c_in)
        {
            res.push_back('1'); //注意也要进上多余的位
        }
        reverse(res.begin(), res.end());
        return HexNumber(res);
    }

    HexNumber operator-(const HexNumber &a)
    {
        string minValue, maxValue;
        bool isMinus = false; //结果是否是负数
        if (*this < a)
        {
            minValue = value;
            maxValue = a.getValue();
            isMinus = true;
        }
        else
        {
            minValue = a.getValue();
            maxValue = value;
        }
        string res;

        int minSize = static_cast<int> (minValue.size());
        reverse(minValue.begin(), minValue.end());
        reverse(maxValue.begin(), maxValue.end());

        int c;
        bool c_out = false; //是否需要借位;
        for (int i = 0; i < minSize; i++)
        {
            c = ((c_out) ? (Char2Int(maxValue[i]) - Char2Int(minValue[i])) - 1 : (Char2Int(maxValue[i]) -
                                                                                  Char2Int(minValue[i])));
            if (c < 0)
            {
                c_out = true;
                c += 16;
            }
            else
                c_out = false;
            res.push_back(Int2Char(c));
        }

        for (int i = minSize; i < maxValue.size(); i++)
        {
            c = ((c_out) ? (Char2Int(maxValue[i]) - 1) : (Char2Int(maxValue[i]))); //注意这时候不应该减'0'了！
            if (c < 0)
            {
                c_out = true;
                c += 16;
            }
            else
                c_out = false;
            res.push_back(Int2Char(c));
        }

        //去掉多余的0前缀
        for (int i = res.size() - 1; i >= 0; i--)
        {
            if (res[i] == '0') res.pop_back();
            else
                break;
        }

        if (isMinus)
            res.push_back('-');

        reverse(res.begin(), res.end());
        return HexNumber(res);
    }

    HexNumber operator*(const HexNumber &a)
    {
        string numbers[a.getValue().size()];

        for (int i = a.getValue().size() - 1, j = 0; i >= 0; i--, j++)
        {
            numbers[j] = singleMultiplication(value, a.getValue().at(i));
            numbers[j] = putZero(numbers[j], j);
        }

        HexNumber res("0");
        for (int i = 0; i < a.getValue().size(); i++)
            res = res + HexNumber(numbers[i]);

        return res;
    }
};

int main()
{
    string str;
    cin >> str;
    HexNumber a(str);
    cin >> str;
    HexNumber b(str);
    string ans = (a * b).getValue();
    cout << ans << endl;
}
