#include <bits/stdc++.h>
using namespace std;

class Graph
{
    private:

    int vertices;
    int edges;
    vector< set<int> > adjacency_list;

    public:

    Graph(int v=0, int e=0):vertices(v),edges(e),adjacency_list(v){}; // need to know what this is??

    void add_edge( int u, int v)
    {
        adjacency_list[u].insert(v);
        adjacency_list[v].insert(u);
    }

    void remove_edge(int u, int v)
    {
        adjacency_list[u].erase(v);
        adjacency_list[v].erase(u);
    }

    Graph operator+(const Graph &other)
    {
        int v1 = vertices;
        int v2 = other.vertices;
        int v = max(v1,v2);

        Graph result(v,0);

        for(int i=0;i<v1;i++)
        {
            for(auto it: adjacency_list[i])
            {
                result.add_edge(i,it);
            }
        }
        /*learning from this is that how to push vector of set to other similar kind*/

        for(int i = 0; i<v2;i++)
        {
            for(auto it: other.adjacency_list[i])
            {
                result.add_edge(i,it);
            }
        }
        //same as before

        return result;

    }

    Graph operator-(const Graph &other)
    {
        int v1 = vertices;
        int v2 = other.vertices;

        int v = max(v1,v2);

        Graph result(v,0);

        for(int i=0 ; i< min(v1,v2);i++)
        {
            for(auto it:adjacency_list[i])
            {
                if(other.adjacency_list[i].count(it))
                {
                    result.add_edge(i,it);
                }
            }
        }

        return result;
    }

    Graph operator!()
    {
        int v = vertices;

        Graph result(v,0);

        for(int i=0;i<v;i++)
        {
            for(int j=0;j<v;j++)
            {
                if(adjacency_list[i].count(j)==0 && i!=j)
                {
                   result.add_edge(i,j);
                }
            }
        }
        return result;
    }

    bool is_reachable(int u, int v)
    {
        vector<bool> visited(vertices);

        queue<int> q;
        q.push(u);

        visited[u] =true;

       while(!q.empty())
        {   
            if(q.front()==v)
            {
                return true;
            }
            int top = q.front();
            q.pop();
            for(auto it: adjacency_list[top])
            {
                if(visited[it]!=true)
                {
                    q.push(it);
                    visited[it] =true;
                }
            }

        }return false;
        
    }
    
    friend istream& operator>>(istream& input, Graph &g)
    {
        input>>g.vertices>>g.edges;
        g.adjacency_list.resize(g.vertices);
        for(int i=0;i<g.edges;i++)
        {
            int u,v;
            input>>u>>v;
            g.add_edge(u,v);
        }
        return input;
    }

    friend ostream& operator<<(ostream& output , Graph g)
    {
        for(int i=0;i<g.vertices;i++)
        {
            output<<"Vertex "<<i<<":";
            for(auto it: g.adjacency_list[i])
            {
                output<<" "<<it;
            }output<<'\n';
        }
        return output;
    }
   
};


int main()
{
    Graph G;

    string str;

    while(true)
    {
        cin>>str;

        if(str=="end")
        {
            break;
        }
        else if(str=="Graph")
        {
            cin>>G;
        }
        else if(str=="union")
        {
            Graph other;
            string s; cin>>s;
            cin>>other;
            G = G+other;
        }
        else if(str=="intersection")
        {
            Graph other;
            string s; cin>>s;
            cin>>other;
            G = G-other;
        }
        else if(str=="complement")
        {
            G = !G;
        }
        else if(str == "isReachable")
        {
            int u,v;
            cin>>u>>v;
            if(G.is_reachable(u,v))
            {
                cout<<"Yes"<<'\n';
            }
            else
            {
                cout<<"No"<<'\n';
            };
        }
        else if(str=="add_edge")
        {
            int u,v;
            cin>>u>>v;
            G.add_edge(u,v);
        }
        else if(str=="remove_edge")
        {
            int u,v;
            cin>>u>>v;
            G.remove_edge(u,v);
        }
        else
        {
            cout<<G;
        }
    }
}