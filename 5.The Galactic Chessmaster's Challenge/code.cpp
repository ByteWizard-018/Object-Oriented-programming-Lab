#include <bits/stdc++.h>
using namespace std;

class  Comparator_acend
{
    public:

    bool operator()(long long a, long long b)
    {
        return a<b; // ascending
    }
};

class Comparator_decend
{
    public:

    bool operator()(long long a,long long b)
    {
        return a>b; //decending
    }
};

bool comp_Xcoord(pair<long long , long long>a, pair<long long, long long>b )
{
        return (a.first < b.first);
}

bool comp_Ycoord(pair<long long, long long>a , pair<long long , long long> b)
{
        return(a.second < b.second);
}

class QuantumChess
{
    private:

    vector<vector<long long>> Board;
    long long n;

    public:

    QuantumChess(){}; //default constructor
    QuantumChess(vector<vector<long long>> v,long long n): Board(v),n(n){}; // comparator

    
    template <typename Comparator>
    void mergesort(vector<long long> &arr, long long left,long long right, Comparator comp) // use template
    {
        if(left>=right){return;}
        
        long long mid = left+((right-left)/2);

        mergesort(arr,left,mid,comp);
        mergesort(arr,mid+1,right,comp);
        merge(arr,left,mid,right,comp);
    }

    template <typename Comparator>
    void merge(vector<long long> &arr,long long left,long long mid, long long right, Comparator comp)
    {
        long long n1 = mid-left+1;
        long long n2 = right-mid;

        vector<long long> v1(n1);
        vector<long long> v2(n2);

        for(long long i=0; i<n1; i++)
        {
            v1[i] = arr[left+i];
        }

        for(long long i=0; i<n2; i++)
        {
            v2[i] = arr[mid+1+i];
        }

        long long i=0;
        long long j=0;

        long long k= left;
        while(i<n1 && j<n2)
        {
            if(comp(v1[i],v2[j]))
            {
                arr[k++] = v1[i++];
            }
            else
            {
                arr[k++] = v2[j++];
            }
        }

        while(i<n1)
        {
            arr[k++] = v1[i++];
        }

        while(j<n2)
        {
            arr[k++] = v2[j++];
        }
    }

    void sortRows(string s)
    {   
        //take which row to get in the vector

        for(long long i=0;i<n;i++){
            if(s=="ascending")
            {
                // Comparator_acend comp;
                mergesort(Board[i],0,n-1,Comparator_acend());
                    // sort(Board[i].begin(),Board[i].end(),Comparator_acend());
            }
            else if(s=="descending")
            {
                // Comparator_decend comp;
                mergesort(Board[i],0,n-1,Comparator_decend());
                // sort(Board[i].begin(),Board[i].end(),Comparator_decend());
            }
        }
    }

long long sort_and_count(vector<long long> &arr, long long l, long long r)
{
    if(l==r)
    {
        return 0;
    }

    long long m = (r+l)/2;

    long long r1 = sort_and_count(arr,l,m);
    long long r2 = sort_and_count(arr,m+1,r);

    long long r3 = merge_and_count(arr,l,m,r);
    return r1 + r2 + r3;
}

long long merge_and_count(vector<long long> &arr, long long l, long long m, long long r)
{
    long long n1 = m-l+1;
    long long n2 = r-m;
    vector<long long> L(n1), R(n2);

    for(long long i = 0; i<n1; i++)
    {
        L[i] = arr[l + i];
    }
    for(long long i = 0; i<n2; i++)
    {
        R[i] = arr[m+1+i];
    }

    long long i = 0;
    long long j = 0;
    long long k = l;
    long long count = 0;

    while(i <n1 && j <n2)
    {
        if(L[i]<=R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
            count = count + (n1 - i);
        }
    }

    while(i<n1)
    {
        arr[k++] = L[i++];
    }

    while(j<n2)
    {
        arr[k++] = R[j++];
    }

    return count;
   }

    long long countInversions()
    {
        vector<long long> flat_board;
        for(long long i=0;i<n;i++)
        {
            for(long long j= 0;j<n;j++)
            {
                flat_board.push_back(Board[i][j]);
            }
        }
        return sort_and_count(flat_board,0,flat_board.size()-1);
    }


    void display()
    {
        for(long long i=0;i<n;i++)
        {
            for(long long j=0;j<n;j++)
            {
                cout<<Board[i][j]<<" ";
            }cout<<'\n';
        }
    }

    pair<pair<long long , long long> , pair<long long , long long> >closestpair(vector<pair<long long , long long >> &Coord)
    {
        

        vector<pair<long long,long long>>Px = Coord;
        vector<pair<long long,long long>>Py = Coord;

        sort(Px.begin(),Px.end(),comp_Xcoord);
        sort(Py.begin(),Py.end(),comp_Ycoord);

        return closestpair_recur(Px,Py);

    }

    pair<pair<long long, long long>,pair<long long, long long>> closestpair_recur(vector<pair<long long, long long>> &Px, vector<pair<long long, long long>> &Py)
    {
        if((Px.size())<=3)
        {
            if(Px.size()==2)
            {
                return {Px[0],Px[1]};
            }
            else
            {
                long long a = Squared_Distance(Px[0],Px[1]);
                long long b = Squared_Distance(Px[1],Px[2]);
                long long c = Squared_Distance(Px[0],Px[2]);

                if(a<b && a<c){return {Px[0],Px[1]};}
                else if(b<a && b<c){return {Px[1],Px[2]};}
                else{return {Px[0],Px[2]};}
            }
        }

        vector<pair<long long, long long>> Qx,Qy,Rx,Ry;
        for(size_t i = 0;i<(Px.size())/2;i++)
        {
            Qx.push_back(Px[i]);
        }

        for(size_t i =(Px.size())/2;i<Px.size();i++)
        {

            Rx.push_back(Px[i]);
        }

        auto a = Qx.back().first;

        for(size_t i =0; i<Px.size();i++)
        {
            if(Px[i].first<=a)
            {
                Qy.push_back(Px[i]);
            }
            else
            {
                Ry.push_back(Px[i]);
            }
        }

        auto point_1 = closestpair_recur(Qx,Qy);
        auto point_2 = closestpair_recur(Rx,Ry);
        

        long long left = Squared_Distance(point_1.first,point_1.second);
        long long right = Squared_Distance(point_2.first, point_2.second);

        pair<pair<long long, long long>, pair<long long , long long>> min_pair;

        if(left<right)
        {
            min_pair = point_1;
        }
        else if(right<left)
        {
            min_pair = point_2;
        }
        else 
        {
            if(min(point_1.first,point_1.second)<min(point_2.first,point_2.second))
            {
                min_pair=point_1;
            }
            else
            {
                min_pair=point_2;
            }
        }

        long long delta_square = min(left, right);

        vector<pair<long long, long long>> S;

        for(size_t i=0;i<Px.size();i++)
        {
            if((Py[i].first - a)*(Py[i].first - a) <= delta_square)
            {
                S.push_back(Py[i]);
            }
        }

        for(size_t i=0;i<S.size();i++)
        {
            for(long long j=i+1;j<min(i+8,S.size());j++)
            {
                long long d =  Squared_Distance(S[i],S[j]);
                if(d < delta_square)
                {
                    delta_square=d;
                    min_pair = make_pair(S[i],S[j]);
                }
                else if(d == delta_square)
                {
                    if(min(min_pair.first,min_pair.second)>min(S[i],S[j]))
                    {
                        min_pair=make_pair(S[i],S[j]);
                    }
                }
            }
        }

        return min_pair;



    }

    long long Squared_Distance(pair<long long, long long> rs1, pair<long long , long long>rs2 )
    {
        long long X = rs1.first - rs2.first;
        long long Y = rs1.second - rs2.second;

        long long squDist = X*X + Y*Y;

        return (squDist);
    }
  

};






int main()
{
    string s;
    QuantumChess q;

    while(true)
    {
        cin>>s;
        if(s=="CREATE_2D")
        {
            long long n;
            cin>>n;
            // vector<vector<long long>>v;
            vector<vector<long long>>v(n, vector<long long>(n));
            for(long long i=0;i<n;i++)
            {
                for(long long j=0;j<n;j++)
                {
                    long long a;cin>>a;
                    v[i][j] =a;
                }
            }
            q = QuantumChess(v,n); 
        }
        else if(s=="SORT_2D")
        {
            string str;
            cin>>str;
            q.sortRows(str);
        }
        else if(s=="INVERSION_2D")
        {
            cout<<q.countInversions()<<'\n';
        }
        else if(s=="DISPLAY_2D")
        {
            q.display();
        }
        else if(s=="CLOSEST_2D")
        {
            long long a;
            cin>>a;
            vector<pair<long long,long long>> v(a);
            for(long long i=0;i<a;i++)
            {
                long long x,y;
                cin>>x>>y;
                v[i].first = x;
                v[i].second = y;
            }
            pair<pair<long long,long long>, pair<long long, long long> > r = q.closestpair(v);
            long long idx1 = -1, idx2 = -1;
            for (long long i = 0; i < a; i++)
            {
                if(v[i]== r.first && idx1 == -1)
                {
                    idx1 = i;
                }
                else if(v[i]== r.second && idx2 == -1)
                {
                    idx2 = i;
                }
            }
            if(idx1<idx2)
            {
                cout<<r.first.first<<" "<<r.first.second<<" "<<r.second.first<<" "<<r.second.second<<"\n";
            }
            else
            {
                cout<<r.second.first<<" "<<r.second.second<<" "<<r.first.first<<" "<<r.first.second << "\n";
            }
        }
        else
        {
            break;
        }
    }

}

