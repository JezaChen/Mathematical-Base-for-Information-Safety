#include <iostream>

using namespace std;

void EuclidDivide(int a, int b)
{
    cout << a << " = " << a / b << " * " << b << " + " << a % b << endl;
    if (a % b == 0) return;
    return EuclidDivide(b, a % b);
}

int main()
{
    int a, b;
    cout << "输入被除数: ";
    cin >> a;
    cout << "输入除数: ";
    cin >> b;
    EuclidDivide(a, b);
}
