#include <bits/stdc++.h>
using namespace std;

class Card
{
    public:

    virtual long long Area() const = 0;

    virtual bool operator<(const Card& c1) const
    {
        return this->Area() < c1.Area();
    };

    virtual void takeinput() = 0;
    virtual void print() const = 0;

    friend istream& operator>> (istream& i, Card* c)
    {
        c->takeinput();
        return i;
    }

    friend ostream& operator<< (ostream& o , const Card* c)
    {
        c->print();
        return o;
    }
};

class square : public Card
{   
    long long edge;

    public:

    square():edge(0){};
    square(long long edge): edge(edge){};

    long long Area() const
    {
        return edge * edge;
    }

    void takeinput()
    {   
        cin >> edge;
    }

    void print() const
    {
        cout << "SQUARE" << " " << edge <<'\n';
    }
};

class rectangle : public Card
{
    long long length;
    long long breadth;

    public:

    rectangle(): length(0), breadth (0){};
    rectangle(long long length, long long breadth): length(length), breadth(breadth){};

    long long Area() const
    {
        return length * breadth;
    }

    void takeinput()
    {   
        cin >> length >> breadth;
    }

    void print() const
    {
        cout << "RECTANGLE" << " " << length << " " << breadth << '\n';
    }
};

class triangle : public Card
{
    long long base;
    long long height;

    public:

    triangle(): base(0), height(0){};
    triangle(long long b, long long h): base(b), height(h){};

    long long Area() const
    {
        return (base * height) / 2;
    }

    void takeinput()
    {   
        cin >> base >> height;
    }

    void print () const
    {
        cout << "TRIANGLE" << " " << base << " " << height <<'\n';
    }
};

class CardOrganizer
{   
    vector <stack<Card*>> piles;
    vector <Card*> cards;
    
    vector<int> dp;
    vector<int> prev;

    public:

    CardOrganizer(){
        dp = vector<int>(1,-1);
    }

    void addCard(Card* c)
    {
        bool flag = false;

        for (auto &it : piles)
        {
            if (!(*it.top() < *c))
            {
                it.push(c);
                flag = true;
                break;
            }
        }

        if (!flag)
        {
            stack<Card*> s;
            s.push(c);
            piles.push_back(s);
        }

        cards.push_back(c);

        int low = 0, high = dp.size();
        int i = cards.size() - 1;
        if(i < 0){
            return;
        }
        while (low < high)
        {
            int mid = (low + high) / 2;
            if(mid == 0){
                low = 1;
                break;
            }
            if (*cards[dp[mid]] < *cards[i])
            {
                low = mid + 1;
            }
            else
            {
                high = mid;
            }
        }

        if (low < dp.size())
        {
            dp[low] = i;
        }
        else
        {
            dp.push_back(i);
        }

        if (low > 0)
        {
            prev.push_back(dp[low - 1]);
        }
    }

    size_t getPileCount() const
    {
        return piles.size();
    }

    vector<Card*> getLIS() 
    {
        int n = cards.size();
        if (n == 0) return {};
        // prev.resize(n,-1);

        // for (int i = 0; i < n; ++i)
        // {
        //     int low = 0, high = dp.size();
        //     while (low < high)
        //     {
        //         int mid = (low + high) / 2;
        //         if (*cards[dp[mid]] < *cards[i])
        //         {
        //             low = mid + 1;
        //         }
        //         else
        //         {
        //             high = mid;
        //         }
        //     }

        //     if (low < dp.size())
        //     {
        //         dp[low] = i;
        //     }
        //     else
        //     {
        //         dp.push_back(i);
        //     }

        //     if (low > 0)
        //     {
        //         prev[i] = dp[low - 1];
        //     }
        // }

        vector<Card*> result;
        for (int i = dp.back(); i != -1; i = prev[i])
        {
            result.push_back(cards[i]);
        }

        reverse(result.begin(), result.end());
        return result;
    }

};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long q;
    cin >> q;

    CardOrganizer co;

    while (q--)
    {
        long long n;
        cin >> n;

        if (n == 1)
        {
            string s;
            cin >> s;

            Card* c;

            if (s == "SQUARE")
            {   
                c = new square();
            }
            else if (s == "RECTANGLE")
            {
                c = new rectangle();
            }
            else
            {
                c = new triangle();
            }

            cin >> c;
            co.addCard(c);
        }
        else if (n == 2)
        {
            cout << co.getPileCount() <<'\n';
        }
        else
        {
            vector<Card*> lis = co.getLIS();
            cout << lis.size() <<'\n';
            for (Card* c : lis)
            {
                cout << c;
            }
        }
    }

    return 0;
}
