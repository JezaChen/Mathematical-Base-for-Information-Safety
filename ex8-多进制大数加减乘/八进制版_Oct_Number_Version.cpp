#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

class OctNumber
{
private:
    string value;

    static string singleMultiplication(const string &a, char k)
    {
        if (k == '0')
            return "0";
        int kInt = k - '0';
        //八进制的单位乘可不得了
        string value = a;
        reverse(value.begin(), value.end());
        string ans;
        int c;
        int c_in = 0;
        for (int i = 0; i < value.size(); i++)
        {
            c = (value[i] - '0') * kInt + c_in;
            //不用 c >= 8
            c_in = c / 8;
            c %= 8;
            ans.push_back(c + '0');
        }
        if (c_in) //记得处理多出来的位
            ans.push_back(c_in + '0');
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
    explicit OctNumber(string _value) : value(std::move(_value))
    {}

    string getValue() const
    { return value; }

    bool operator<(const OctNumber &a)
    {
        if (value.size() < a.getValue().size())
            return true;
        if (value.size() > a.getValue().size())
            return false;
        for (int i = 0; i < value.size(); i++)
        {
            if (value[i] < a.getValue().at(i)) return true;
            if (value[i] > a.getValue().at(i)) return false;
        }

        return false; //相等
    }


    OctNumber operator+(const OctNumber &a)
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
            if (c >= '8')
            {
                c_in = true;
                c -= 8;
            }
            else
                c_in = false;
            res.push_back(c);
        }
        for (int i = minSize; i < valueTemp.size(); i++)
        {
            c = ((c_in) ? (valueTemp[i] + 1) : (valueTemp[i])); //注意这时候不应该减'0'了！
            if (c >= '8')
            {
                c_in = true;
                c -= 8;
            }
            else
                c_in = false;
            res.push_back(c);
        }
        for (int i = minSize; i < aTemp.size(); i++)
        {
            c = ((c_in) ? (aTemp[i] + 1) : (aTemp[i])); //注意这时候不应该减'0'了！
            if (c >= '8')
            {
                c_in = true;
                c -= 8;
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
        return OctNumber(res);
    }

    OctNumber operator-(const OctNumber &a)
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
                c += 8;
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
                c += 8;
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
        return OctNumber(res);
    }

    OctNumber operator*(const OctNumber &a)
    {
        string numbers[a.getValue().size()];

        for (int i = a.getValue().size() - 1, j = 0; i >= 0; i--, j++)
        {
            numbers[j] = singleMultiplication(value, a.getValue().at(i));
            numbers[j] = putZero(numbers[j], j);
        }

        OctNumber res("0");
        for (int i = 0; i < a.getValue().size(); i++)
            res = res + OctNumber(numbers[i]);

        return res;
    }
};

int main()
{
    cout << "请选择运算类型： 1.加法 2.减法 3.乘法" << endl;
    int choice;
    while (cin >> choice)
    {
        switch (choice)
        {
            case 1:
            {
                cout << "输入被加数: ";
                string str;
                cin >> str;
                OctNumber a(str);
                cout << "输入加数: ";
                cin >> str;
                OctNumber b(str);
                cout << "结果是:";
                cout << (a + b).getValue() << endl;
                break;
            }
            case 2:
            {
                cout << "输入被减数: ";
                string str;
                cin >> str;
                OctNumber a(str);
                cout << "输入减数: ";
                cin >> str;
                OctNumber b(str);
                cout << "结果是:";
                cout << (a - b).getValue() << endl;
                break;
            }
            case 3:
            {
                cout << "输入被乘数: ";
                string str;
                cin >> str;
                OctNumber a(str);
                cout << "输入乘数: ";
                cin >> str;
                OctNumber b(str);
                cout << "结果是:";
                cout << (a * b).getValue() << endl;
                break;
            }
            default:
                cout<<"输入错误，请重新输入!"<<endl;
        }
    }
}
