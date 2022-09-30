//    Name: Mahmoud Atef Mahmoud Elsaadany
//    ID: 20195007
//    Group: N1

#include<iostream>
#include<cmath>
#include<cstdio>

using namespace std;

class RSA
{
public:

    int p,q,n;
    int euler,flag,e[100],d[100],temp[100],j,M[100],en[100],i;
    string Message;
    RSA()
    {
        p = 0;
        q = 0;
        Message = " ";
        n=p*q;
        euler=(p-1)*(q-1);
    }
    RSA(int x, int y, string s)
    {
        int i;
        p = x;
        q = y;
        Message = s;
        n=p*q;
        euler=(p-1)*(q-1);
        for(i=0;i<Message.size();i++)
        {
            M[i] = Message[i];
        }
    }

    int prime(int Prime)
    {
        int i;
        j=sqrt(Prime);
        for (i=2;i<=j;i++)
            {
                if(Prime%i==0)
                return 0;
            }
                return 1;
    }
        void compute_e()
        {
            int k;
            k=0;
            for (i=2;i<euler;i++)
            {
                if(euler%i==0)
                continue;
                flag=prime(i);
                if( flag==1 && i!=p && i!=q)
                {
                    e[k]=i;
                    flag=compute_d(e[k]);
                    if(flag>0)
                        {
                            d[k]=flag;
                            k++;
                        }
                            if(k==99)
                            break;
                }
            }

            for (i=0;i<j-1;i++)
            {
                cout<<(i+1)<<"      ("<<e[i]<<","<<d[i]<<")"<<endl;
            }
                cout<<endl;
            }
    int compute_d(int x)
    {
        // d=e^-1 mod euler
        int k=1;
        while(1)
        {
            k=k+euler;
            if(k%x==0)
            return(k/x);
        }
    }
    void encrypt(int x)
    {
        int plain_text,cipher_text,key=e[x-1],k,len,D=d[x-1];
        cout<<"Value of e used is: "<<key<<endl;
        cout<<"Value of d used is: "<<D<<endl;
        cout<<endl;
        i=0;
        len = Message.size();
        while(i!=len)
        {
            plain_text=M[i];
            plain_text=plain_text-96;
            k=1;
            for (j=0;j<key;j++)
            {
                k=k*plain_text;
                k=k%n;
            }
            temp[i]=k;
            cipher_text=k+96;
            en[i]=cipher_text;
            i++;
        }

        en[i]=-1;
        cout<<"The Encrypted Message : "<<endl;
        for (i=0;en[i]!=-1;i++)
        cout<<en[i];
        cout<<endl;
    }

    void decrypt(int x)
    {
        long int plain_text,cipher_text,key=d[x-1],k;
        i=0;
        while(en[i]!=-1)
        {
            cipher_text=temp[i];
            k=1;
            for (j=0;j<key;j++)
                {
                    k=k*cipher_text;
                    k=k%n;
                }

            plain_text=k+96;
            M[i]=plain_text;
            i++;
        }

        M[i]=-1;
        cout<<"The Decrypted Message : "<<endl;

        for (i=0;M[i]!=-1;i++)
        {
            if ((char)M[i]!='W')
            {
            cout<<(char)M[i];
            }
            else
            {
                cout<<" ";
            }

        }
        cout<<endl;
    }
};


int main()
{
RSA R1;
bool flag;
int i,n,t,p,q,x;

do
    {
        cout<<"Enter the Prime Numbers P "<<endl;
        cin>>p;
        flag = R1.prime(p);
        if (flag==0)
        {
            cout<<"Wrong Choice, The number You Entered in not a prime number"<<endl;
        }

    }
    while (flag==0);


do
    {

        cout<<"Enter the Prime Numbers Q "<<endl;
        cin>>q;
        flag = R1.prime(q);
        if (flag==0)
        {
            cout<<"Wrong Choice, The number You Entered in not a prime number"<<endl;
        }

    }
    while (flag==0);
    cout<<"The Value Of P Is : "<<p<<endl;
    cout<<"The Value Of Q Is : "<<q<<endl;
    cout<<"The Value Of n Is : "<<p*q<<endl;
    cout<<endl;
    cout<<"Enter the Message"<<endl;
    string Message;
    getchar();
    getline(cin,Message);
    RSA R2(p,q,Message);
    cout<<"Possible values of (e,d) are"<<endl;
    R2.compute_e();
    cout<<"Chose which values of (e,d) you want to use?"<<endl;
    cin>>x;
    cout<<endl;
    R2.encrypt(x);
    cout<<endl;
    R2.decrypt(x);
    return 0;
}
