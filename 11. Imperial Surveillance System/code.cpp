#include <bits/stdc++.h>
using namespace std;

int count0 = 0;
int count1 = 0;
int count2 = 0;

class Sentinal
{
    public:

    virtual int getid()=0;
    virtual string getname() =0;
    virtual int getrank() =0;
    virtual int countHigherRanked()=0;
};

class Senapati :public Sentinal
{
    private:

    int id;
    string name;
    int rank;

    public:

    Senapati(int i, string n, int r): id(i), name(n), rank(r){};

    int countHigherRanked()
    {
        return 0;
    }

    int getid()
    {
        return id;  // getters
    }

    string getname()
    {
        return name; //getters
    }

    int getrank()
    {
        return rank;    //getters
    }

};

class Dandanayaka :public Sentinal
{
    private:

    int id;
    string name;
    int rank;

    public:
    Dandanayaka(int i, string n, int r): id(i), name(n), rank(r){};

    int countHigherRanked()
    {
        return count0;
    }

    int getid()
    {
        return id;  //getters
    }

    string getname()
    {
        return name;    //getters
    }

    int getrank()
    {
        return rank;    //getters
    }
};

class Chaturangini :public Sentinal
{
    private:

    int id;
    string name;
    int rank;

    public:

    Chaturangini(int i, string n, int r): id(i), name(n), rank(r){};
    int countHigherRanked()
    {
        return count0 + count1;
    }

    int getid()
    {
        return id;  //getters
    }

    string getname()
    {
        return name; //getters
    }

    int getrank()
    {
        return rank; //getters
    }
};

// custom comparator

class customcomp
{
    public:

    bool operator() (Sentinal *s1, Sentinal *s2)
    {
        if (s1->getrank() == s2->getrank())
        {
            return s1->getid() < s2->getid();
        }
        else
        {
            return s1->getrank() < s2->getrank();
        }
    }
};

//templatized class
template <typename T>
class Kingdom
{   
    private:

    T number_of_nodes;
    T no_of_edges;
    vector<unordered_set<T>> Adj_list;

    public:

    Kingdom(T n, T e): number_of_nodes(n), no_of_edges(e)
    {
        Adj_list.resize(n);
    };
    
    vector <Sentinal*> sentinals; // all sentinals of kingdom

    void addedge(T u, T v)
    {
        Adj_list[u].insert(v);
        Adj_list[v].insert(u);
    }
    

    void addsentinal(Sentinal* s)
    {
        sentinals.push_back(s);
    }

    void dfs(int u, int parent, vector<vector<int>> &dp, vector<bool> &vis)
    {
        vis[u] = true;
        dp[u][0] = 0;
        dp[u][1] = 1;

        for(auto it: Adj_list[u])
        {
            if(it == parent) continue;
            dfs(it, u, dp, vis);
            dp[u][0] += dp[it][1];
            dp[u][1] += min(dp[it][0], dp[it][1]);
        }
    }

};



int main()
{

    int n;
    cin >> n;

    Kingdom<int> k(n,n-1);
    
    for (int i = 0; i < n-1; i++)
    {
        int u,v;
        cin >> u >> v;

        k.addedge(u,v);
    }

    for (int i = 0; i < n; i++)
    {
        string name,rank;
        cin >> name >> rank;

        if (rank == "SENAPATI")
        {
            Sentinal *s = new  Senapati(i, name, 0);
            k.addsentinal(s);
            count0++;
        }
        else if (rank == "DANDANAYAKA")
        {
            Sentinal *s = new Dandanayaka(i, name, 1);
            k.addsentinal(s);
            count1++;
        }
        else
        {
            Sentinal *s = new Chaturangini(i, name, 2);
            k.addsentinal(s);
            count2++;
        }
    }

    int no_of_queries;
    cin >> no_of_queries;

    vector <Sentinal*> sortedvector;
    bool flag = false;
    vector<vector<int>> dp(n, vector<int>(2, 0));
    vector<bool> vis(n, false);    
    int min_cover =0;
    bool q1_flag = false;

    while (no_of_queries--)
    {   
        int q;
        cin >> q;
        if (q == 1)
        {   
            if(!q1_flag)
            {
                q1_flag =true;
                k.dfs(0,-1,dp,vis);
                min_cover = min(dp[0][0],dp[0][1]);
            }
            cout << min_cover <<'\n';
        }
        else if ( q == 2)
        {   
            if(!flag)
            {
                flag = true;
                vector <Sentinal*> duplicate_vector = k.sentinals;
                sort(duplicate_vector.begin(), duplicate_vector.end(), customcomp());
                sortedvector = duplicate_vector;
            }
            
            for (auto it: sortedvector)
            {
                cout << it->getid() <<" ";
            }cout <<'\n';
            
        }
        else
        {
            int m;
            cin >> m;
            
            cout << k.sentinals[m]->countHigherRanked() << '\n';
        }
    }
}
