#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

class BinNumber
{
private:
    string value;

    static string singleMultiplication(const string &a, char k)
    {
        //二进制的单位乘比较水
        if (k == '0')
            return "0";
        return a;
    }

    //往后面塞零
    static string putZero(const string &a, int k)
    {
        if(a == "0")
            return a;
        string res = a;
        for (int i = 0; i < k; i++)
            res.push_back('0');
        return res;
    }

public:
    explicit BinNumber(string _value) : value(std::move(_value))
    {}

    string getValue() const
    { return value; }

    bool operator<(const BinNumber &a)
    {
        if (value.size() < a.getValue().size())
            return true;
        if (value.size() > a.getValue().size())
            return false;
        for (int i = value.size() - 1; i >= 0; i--)
        {
            if (value[i] < a.getValue().at(i)) return true;
            if (value[i] > a.getValue().at(i)) return false;
        }

        return false; //相等
    }


    BinNumber operator+(const BinNumber &a)
    {
        string valueTemp = value;
        string aTemp = a.getValue();
        string res;

        reverse(valueTemp.begin(), valueTemp.end());
        reverse(aTemp.begin(), aTemp.end());

        int minSize = static_cast<int>(min(valueTemp.size(), aTemp.size()));
        char c; //一位相加产生的结果
        bool c_in = false; //进位标记
        for (int i = 0; i < minSize; i++)
        {
            c = ((c_in) ? (valueTemp[i] + aTemp[i] - '0' + 1) : (valueTemp[i] + aTemp[i] - '0'));
            if (c >= '2')
            {
                c_in = true;
                c -= 2;
            }
            else
                c_in = false;
            res.push_back(c);
        }
        for (int i = minSize; i < valueTemp.size(); i++)
        {
            c = ((c_in) ? (valueTemp[i] + 1) : (valueTemp[i])); //注意这时候不应该减'0'了！
            if (c >= '2')
            {
                c_in = true;
                c -= 2;
            }
            else
                c_in = false;
            res.push_back(c);
        }
        for (int i = minSize; i < aTemp.size(); i++)
        {
            c = ((c_in) ? (aTemp[i] + 1) : (aTemp[i])); //注意这时候不应该减'0'了！
            if (c >= '2')
            {
                c_in = true;
                c -= 2;
            }
            else
                c_in = false;
            res.push_back(c);
        }

        if (c_in)
        {
            res.push_back('1'); //注意也要进上多余的位
        }
        reverse(res.begin(), res.end());
        return BinNumber(res);
    }

    BinNumber operator-(const BinNumber &a)
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

        char c;
        bool c_out = false; //是否需要借位;
        for (int i = 0; i < minSize; i++)
        {
            c = ((c_out) ? (maxValue[i] - minValue[i] + '0' - 1) : (maxValue[i] - minValue[i] + '0'));
            if (c < '0')
            {
                c_out = true;
                c += 2;
            }
            else
                c_out = false;
            res.push_back(c);
        }

        for (int i = minSize; i < maxValue.size(); i++)
        {
            c = ((c_out) ? (maxValue[i] - 1) : (maxValue[i])); //注意这时候不应该减'0'了！
            if (c < '0')
            {
                c_out = true;
                c += 2;
            }
            else
                c_out = false;
            res.push_back(c);
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
        return BinNumber(res);
    }

    BinNumber operator*(const BinNumber &a)
    {
        string numbers[a.getValue().size()];

        for (int i = a.getValue().size() - 1; i >= 0; i--)
        {
            numbers[i] = singleMultiplication(value, a.getValue().at(i));
            numbers[i] = putZero(numbers[i], i);
        }

        BinNumber res("0");
        for (int i = 0; i < a.getValue().size(); i++)
            res = res + BinNumber(numbers[i]);

        return res;
    }
};

int main()
{
    string str;
    cin >> str;
    BinNumber a(str);
    cin >> str;
    BinNumber b(str);
    string ans = (a * b).getValue();
    cout << ans << endl;
}
