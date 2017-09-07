#include <iostream>
#include <cmath>

using namespace std;

bool is_prime(int x)  //���x�Ƿ�Ϊ����
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
        bool prime[n+1]; //��bool������ʡһ���Ĵ洢�ռ�
        for(int i=2;i<=n;i++) prime[i]=true;  //��ʼ��
        prime[1]=false; //��1ȥ��
        int k= sqrt(n);
        for(int i=2;i<=k;i++)
        {
            if(prime[i]==false) continue; //���������������������ζ����֮ǰ�ļ�����Ѿ���ȥ��������
            if(is_prime(i)) //�����Ƿ�������
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
        cout<<"\b "<<endl; //�������Ķ���
    }
}