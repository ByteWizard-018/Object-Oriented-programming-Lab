#include <bits/stdc++.h>
using namespace std;

template < typename T>
class Multiplication
{   
    private:
    long long degree;
    public:

    vector<T> coefficients;

    Multiplication(){}; // default constructor
    Multiplication(long long d,vector<T> v)
    {
        degree = d;
        coefficients =v;
    };
    // constructor
    Multiplication(long long d)
    {
        degree = d;
        coefficients.resize(d);
    }

    Multiplication operator*(const Multiplication &other)
    {   
        long long size1  = degree;
        long long size2  = other.degree;
        long long max_size = max(size1,size2);
        int k=1;
        while(k<max_size)k*=2;
        vector<T> poly1 = coefficients;
        vector<T> poly2 = other.coefficients;


        poly1.resize(k,0);
        poly2.resize(k,0);
        vector<T> result = Multiply(poly1,poly2);
        result.resize(degree+other.degree-1);
        return Multiplication(result.size(), result);
    }

    vector<T> Multiply(vector<T> &v1, vector<T> &v2)
    {
        long long max_size = v1.size();
        if(max_size <= 2) // Base case: use naive multiplication for small sizes
        {   
            vector<T> result(2*max_size-1, 0);
            for(long long i = 0; i < max_size; i++)
            {
                for(long long j = 0; j < max_size; j++)
                {
                    result[i+j] += v1[i]*v2[j];
                }
            }
            return result;
        }
        
        long long half_size = max_size/2;

        vector<T> a1(v1.begin(), v1.begin() + half_size);
        vector<T> a2(v1.begin() + half_size, v1.end());
        vector<T> b1(v2.begin(), v2.begin() + half_size);
        vector<T> b2(v2.begin() + half_size, v2.end());

        vector<T> e = Multiply(a1,b1);          
        vector<T> f = Multiply(a2,b2);         
        
        vector<T> a1_plus_a2(half_size);
        vector<T> b1_plus_b2(half_size);
        for(long long i = 0; i < half_size; i++)
        {
            a1_plus_a2[i] = a1[i] + a2[i];
            b1_plus_b2[i] = b1[i] + b2[i];
        }

        vector<T> g = Multiply(a1_plus_a2, b1_plus_b2);
        
        vector<T> result(2*max_size-1, 0);
        
        for(long long i = 0; i < e.size(); i++)
        {
            result[i] += e[i];
        }
        
        for(long long i = 0; i < f.size(); i++)
        {
            result[i+2*half_size] += f[i];
        }

        for(long long i = 0; i < g.size(); i++)
        {
            result[i+half_size] += g[i] - e[i] -f[i];
        }
        
        return result;
    }
};

class Complex
{
private:
    long long degree;
    
public:
    vector<pair<long long, long long>> coefficients;

    Complex() {};
    Complex(long long deg, vector<pair<long long, long long>> coeffs) 
    {
        degree = deg;
        coefficients = coeffs;
    };

    Complex operator*(const Complex &other)
    {
        vector<pair<long long, long long >> poly1 = coefficients;
        vector<pair<long long, long long >> poly2 = other.coefficients;
        long long max_size = max(degree,other.degree);
        int k=1;
        while(k<max_size)k*=2;
        poly1.resize(k, {0,0});
        poly2.resize(k, {0,0});
        vector<pair <long long ,long long>> result = multiply_complex(poly1,poly2);
        result.resize(degree+other.degree-1);
        return Complex(result.size(),result);
    }

    vector<pair<long long,long long>> multiply_complex(vector<pair<long long , long long>> &v1, vector<pair<long long ,long long>> &v2)
    {
        long long max_size = v1.size();

        if(max_size <= 2)
        {
            vector<pair<long long ,long long>> result(2*max_size -1, {0,0});
            
            for(long long i=0;i< max_size;i++)
            {
                for(long long j=0;j< max_size;j++)
                {
                    long long real = v1[i].first* v2[j].first - v1[i].second*v2[j].second;
                    long long imaginary = v1[i].first * v2[j].second + v1[i].second*v2[j].first;

                    result[i+j].first += real;
                    result[i+j].second += imaginary;
                }
            }

            return result;
        }

        long long half_size = max_size/2;


        vector<pair<long long, long long>> a1(v1.begin(), v1.begin() + half_size);
        vector<pair<long long, long long>> a2(v1.begin() + half_size, v1.end());
        vector<pair<long long, long long>> b1(v2.begin(), v2.begin() + half_size);
        vector<pair<long long, long long>> b2(v2.begin() + half_size, v2.end());

        // Recursive calls
        vector<pair<long long ,long long>> e = multiply_complex(a1, b1);          
        vector<pair<long long ,long long>> f = multiply_complex(a2, b2);            

        vector<pair<long long ,long long>> a1_plus_a2(half_size);
        vector<pair<long long ,long long>> b1_plus_b2(half_size);

        for(long long i = 0; i < half_size; i++) 
        {
            a1_plus_a2[i] = {a1[i].first + a2[i].first, a1[i].second + a2[i].second};
            b1_plus_b2[i] = {b1[i].first + b2[i].first, b1[i].second + b2[i].second};
        }

        vector<pair<long long, long long>> g = multiply_complex(a1_plus_a2,b1_plus_b2);

        vector<pair<long long ,long long>> result(2*max_size-1,{0,0});

        for(long long i =0 ; i < e.size() ;i++ )
        {
            result[i].first += e[i].first;
            result[i].second += e[i].second;
        }

        for(long long i =0 ; i < f.size(); i++)
        {
            result[i+2*half_size].first += f[i].first;
            result[i+2*half_size].second += f[i].second;
        }

        for(long long i = 0; i < g.size(); i++) 
        {
            result[i + half_size].first += g[i].first - e[i].first - f[i].first;
            result[i + half_size].second += g[i].second - e[i].second - f[i].second;
        }

        return result;

    }
};

template< typename T2>
class evaluation
{   
    private:
    long long degree;
    public:

    vector<T2> coefficients;

    evaluation(){};
    evaluation(long long degree, vector<T2> v): degree(degree),coefficients(v){}

    T2 evaluation_int_and_float(int x)
    {   
        T2 count = 0;


        for(long long i = degree -1;i >= 0; i--)
        {
            // count += coefficients[i]*pow(x,i);
            count = count*x  + coefficients[i];
        }

        return count;
    }

    T2 evaluation_string(long long x)
    {
        string str2;
        long long y =1;
        for(long long i=0; i < degree ; i++)
        {
            string str;
            // long long k = pow(x,i);
            long long k =y;
            while(k--)
            {
                str += coefficients[i];
            }
            str2 =  str + str2;
            y = y*x;
        }
        return str2;
    }
};

template <typename T3>
class Differentiation
{   
    private:
    long long degree;
    public:

    vector<T3> coefficients;

    Differentiation(){};

    Differentiation(long long d, vector<T3> coeff)
    {  
        degree = d ;
        coefficients = coeff;
    };


    vector< T3 > differentiation()
    {
        vector < T3 > result;

        for ( long long i=1 ; i< degree; i++)
        {
            result.push_back(coefficients[i]*i);
        }
        return result;
    }
};


int main()
{   
    cout << fixed << setprecision(6);
    long long queries;
    cin >> queries;

    while ( queries-- )
    {
        long long op;
        cin >> op;

        if ( op == 1 )
        {
            string str;
            cin >> str;

            if ( str == "integer")
            {
                long long deg1,deg2;
                cin >> deg1;

                vector<long long> v1(deg1);
                for(long long i= 0 ;i < deg1;i++)
                {
                    cin >> v1[i];
                }

                cin >> deg2;
                vector<long long> v2(deg2);
                for(long long i= 0 ;i < deg2;i++)
                {
                    cin >> v2[i];
                }

                Multiplication<long long> p1(deg1, v1);
                Multiplication<long long> p2(deg2, v2);
                Multiplication<long long> result = p1 * p2;

                for (auto it : result.coefficients)
                {
                    cout << it << " ";
                }cout << '\n';

            }
            else if( str == "float")
            {
                long long deg1, deg2;
                cin >> deg1;
                vector<long double> v1(deg1);
                for(long long i = 0; i < deg1; i++)
                {
                    cin >> v1[i];
                }
                cin >> deg2;
                vector<long double> v2(deg2);
                for(long long i = 0; i < deg2; i++)
                {
                    cin >> v2[i];
                }
                Multiplication<long double> p1(deg1, v1);
                Multiplication<long double> p2(deg2, v2);
                Multiplication<long double> result = p1 * p2;
                for(auto it : result.coefficients)
                {
                    cout << it << " ";
                }
                cout << '\n';
            }
            else
            {
                long long deg1, deg2;
                cin >> deg1;
                vector<pair<long long, long long>> v1(deg1);
                for(long long i = 0; i < deg1; i++)
                {
                    cin >> v1[i].first >> v1[i].second;
                }
                cin >> deg2;
                vector<pair<long long, long long>> v2(deg2);
                for(long long i = 0; i < deg2; i++)
                {
                    cin >> v2[i].first >> v2[i].second;
                }
                Complex p1(deg1, v1);
                Complex p2(deg2, v2);
                Complex result = p1 * p2;
                for(auto it : result.coefficients)
                {
                    cout << it.first << " " << it.second << " ";
                }
                cout << '\n';
            }

        }
        else if ( op == 2 )
        {
            string str;
            cin >> str;

            long long degree;
            cin >> degree;

            if ( str == "integer")
            {   
                vector<long long> v(degree);
                for ( long long i =0; i < degree ; i++)
                {
                    cin >> v[i];
                }
                evaluation<long long> e(degree, v);
                long long m;
                cin >> m;
                cout << e.evaluation_int_and_float(m) << '\n';
            }
            else if ( str == "float")
            {
                vector <long double> v(degree);
                for ( long long i=0; i < degree ; i++)
                {
                    cin >> v[i];
                }
                evaluation<long double> d(degree, v);
                long long m;
                cin >> m;
                cout<< d.evaluation_int_and_float(m) << '\n';
            }
            else
            {
                vector < string > v(degree);
                for( long long i =0 ; i < degree; i++)
                {
                    cin >> v[i];
                }
                evaluation <string> str_eval(degree, v);
                long long m;
                cin >> m;
                cout << str_eval.evaluation_string(m) << '\n';
            }
        }
        else
        {
            string str;
            cin >> str;

            long long degree;
            cin >> degree;

            if ( str == "integer")
            {
                vector < long long > v(degree);
                for ( long long  i=0 ; i < degree ; i++)
                {
                    cin >> v[i];
                }

                Differentiation<long long> d1(degree,v);
                vector<long long > result = d1.differentiation();
                for ( auto it : result)
                {
                    cout << it << " ";
                }cout <<'\n';
            }
            else
            {
                vector <long double> v(degree);
                for ( long long i =0; i < degree ; i++)
                {
                    cin >> v[i];
                }

                Differentiation<long double> d2(degree,v);
                vector < long double > result = d2.differentiation();
                for ( auto it : result) 
                {
                    cout<< it << " ";
                }cout << '\n';
            }

           
        }
    }
    return 0;
}