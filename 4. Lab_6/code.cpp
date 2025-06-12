#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

class CurrencySorter{

    vector<long long> serial_numbers;
    public:

    CurrencySorter(vector<long long> v):serial_numbers(v){};    //constructor

    void quickSort(int l, int h)
    {
        if(l<h)
        {
            int ind = partition(l,h);
            quickSort(l,ind - 1);
            quickSort(ind + 1,h);
        }
    }

    int partition(int l, int h)
    {
        long long piv = serial_numbers[h];
        int i= (l-1);

        for(int j=l;j<= h-1;j++)
        {
            if(serial_numbers[j]<=piv)
            {
                i++;
                swap(serial_numbers[i],serial_numbers[j]);
            }
        }
        swap(serial_numbers[i+1],serial_numbers[h]);
        return (i+1);
    }

    vector<long long> getSorted()
    {
        long long s = serial_numbers.size();
        quickSort(0,s-1);
        return serial_numbers;
    }

};

class FibonacciGenerator{

    public:
    
    //finding out nth fibnocci
    long long operator()(long long n)
    {
        return doubling(n).first;
    }

    pair<long long,long long> doubling(long long n)
    {
        if(n == 0)
        {
            return {0,1};
        }

        pair<long long, long long> res = doubling(n/2);
        long long a = res.first;
        long long b = res.second;

        long long c = (a*((2*b)-a+MOD))% MOD;
        long long d = (b*b + a*a)% MOD;

        if(n%2 == 0)
        {
            return {c,d};
        }
        else
        {
            return {d,(c+d)% MOD};
        }
    }
};

class PrimeCalculator{

    long long Left;
    long long Right;
    long long Sum;

    public:

    PrimeCalculator(long long L,long long R):Left(L),Right(R),Sum(0){}; //constructor

    vector<long long> sieve(long long n)
    {
        vector<bool> v_prime(n+1, true);
        v_prime[0] = v_prime[1] = false;

        for(long long i= 2;i*i<= n;i++)
        {
            if(v_prime[i])
            {
                for(long long j= i*i;j<= n;j+= i)
                {
                    v_prime[j] = false;
                }
            }
        }

        vector<long long> primes;
        for(long long i= 2;i<=n;i++)
        {
            if(v_prime[i])
            {
                primes.push_back(i);
            }
        }
        return primes;
    }

    // Print primes in [L, R]

    void printPrimes()
    {   
        vector<long long> Primes = findPrimes();    //returns the vector from findPrimes
        for(const auto &it : Primes)
        {
            cout<<it<<" ";
        }
        cout<<'\n';
    }

    //  geting the sum of the primes in [L,R]

    long long printPrimeSum()
    {   
        vector<long long> Primes = findPrimes();
        return Sum;
    }

    //find primes

    vector<long long> findPrimes()
    {
        vector<long long> v;
        Sum = 0;

        if(Left>Right)
        {
            return v;
        }

        long long rootR = sqrt(Right);
        vector<long long> Bprimes = sieve(rootR);

        vector<bool> v_prime(Right-Left+1, true);

        for(long long p: Bprimes)
        {
            long long s = max(p*p, Left+((p-Left% p)% p));

            for(long long j= s;j<=Right;j+= p)
            {
                v_prime[j-Left] = false;
            }
        }

        if(Left<=1)
        {
            v_prime[1-Left] = false;
        }

        for(long long i= Left;i<=Right;i++)
        {
            if(v_prime[i-Left])
            {
                v.push_back(i);
                Sum+= i;
            }
        }

        return v;
    }

};


class NumberAnalyzer{

    long long x;
    long long Sum;

    public:

    NumberAnalyzer(long long x):x(x),Sum(0){};  //constructor

    vector<long long> getPrimeFactors()
    {
        vector<long long>v;
        long long n = x;

        while(n%2 == 0)
        {
            v.push_back(2);
            n = n/2;
        }

        for(long long i= 3;i*i<= n;i+= 2)
        {
            while(n%i == 0)
            {
                v.push_back(i);
                n = n/i;
            }
        }
        if(n>2)
        {
            v.push_back(n);
        }

        return v;
    }

    // finding if the x is square free
    bool isSquareFree()
    {
        vector<long long> v = getPrimeFactors();

        for(long long i= 1;i<v.size();i++)
        {
            if(v[i] == v[i-1])
            {
                return false;
            }
        }

        return true;
    }

    //count no of divisors
    long long countDivisors()
    {
        if(x == 1)
        {
            Sum = 1;
            return 1;
        }

        vector<long long> v = getPrimeFactors();
        long long count = 1;
        Sum = 1;

        for(long long i = 0;i<v.size();)
        {
            long long p = v[i];
            long long exponent = 0;

            while(i<v.size() && v[i] == p)
            {
                exponent++;
                i++;
            }

            count = count*(exponent + 1);

            long long term = 1;
            for(int j= 0;j<=exponent;j++)
            {
                term = term*p;
            }
            Sum = Sum*(term-1)/(p-1);
        }

        return count;
    }

    //sum of divisors
    long long sumOfDivisors()
    {   
        long long count = countDivisors();
        return Sum;
    }


};

int main()
{
    int p;
    cin>>p;

    if(p==1)            //for p==1
    {
        int t;
        cin>>t;

        for(int i=0;i<t;i++)
        {
            long long n;
            vector<long long> v;

            cin>>n;
            for(long long j=0;j<n;j++)
            {
                long long m;
                cin>>m;
                v.push_back(m);
            }

            CurrencySorter CurSor(v);
            
            vector<long long> sorted_v = CurSor.getSorted();

            for (auto &it: sorted_v)
            {
                cout<<it<<" ";
            }
            cout<<'\n';

        }

    }
    else if(p==2)       //for p==2
    {
        long long t;
        cin>>t;

        for(long long i= 0;i<t;i++)
        {
            long long m;
            cin>>m;

            FibonacciGenerator fibGen;
            cout<<fibGen(m)<<endl;
        }
    }
    else if(p==3)                   //for p==3
    {
        long long t;
        cin>>t;

        for(long long i=0;i<t;i++)
        {
            string s;
            cin>>s;

            if(s=="printPrimes")
            {
                long long L,R;
                cin>>L>>R;

                PrimeCalculator p(L,R);
                p.printPrimes();
            }
            else
            {
                long long L,R;
                cin>>L>>R;

                PrimeCalculator p(L,R);
                cout<<p.printPrimeSum()<<'\n';
            }
        }
    }
    else
    {   
        // for p==4
        long long t;
        cin>>t;

        for(long long i=0;i<t;i++)
        {
            string s;
            cin>>s;

            if(s == "isSquareFree")
            {
                long long x;
                cin>>x;

                NumberAnalyzer n(x);
                
                if(n.isSquareFree())
                {
                    cout<<"yes"<<'\n';
                }
                else
                {
                    cout<<"no"<<'\n';
                }
            }
            else if(s == "countDivisors")
            {
                long long x;
                cin>>x;

                NumberAnalyzer n(x);
                cout<<n.countDivisors()<<'\n';
            }
            else
            {
                long long x;
                cin>>x;

                NumberAnalyzer n(x);
                cout<<n.sumOfDivisors()<<'\n';
            }
        }
    }

    return 0;
}