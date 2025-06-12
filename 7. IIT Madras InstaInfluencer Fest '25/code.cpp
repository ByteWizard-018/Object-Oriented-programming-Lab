#include <bits/stdc++.h>

using namespace std;

class customsort
{
    public:
        bool operator()(pair<int, int> a, pair<int, int> b)
        {
            return a.second > b.second; // custom sort for sorting
        }
};


class GraphAlgorithm
{   
    // private:
    public:

    int no_of_events;
    int no_of_edges;
    vector<int> hypescores;
    vector<set<int>> AdjList;
    vector<set<int>> reverse_adjlist;
    int time;

    GraphAlgorithm(){};
    GraphAlgorithm(int n, int m) : no_of_events(n), no_of_edges(m)
    {
        AdjList.resize(n);
        reverse_adjlist.resize(n);
    }
    virtual void Query(){};

    void addhype(int h)
    {
        hypescores.push_back(h); // add hypescore of the event to hypescores[event-1];
    }

    void addedge(int u, int v)
    {
        AdjList[u].insert(v); // add edge to adjlist
        reverse_adjlist[v].insert(u); // add edge to reverse adjlist
    }

    vector<int> gethypescores()
    {
        return hypescores; // gethypescores
    }

    int getno_of_events()
    {
        return no_of_events; // get no of events
    }

    int getedges()
    {
        return no_of_edges; // get no of edges
    }

    pair<bool,vector<pair<int,int>>> DFS()
    {
        vector<int> color(no_of_events, 0);
        vector<int> predecessor(no_of_events, -1);
        vector<int> discovery_time(no_of_events, 0);
        vector<int> finish_time(no_of_events, 0);
        time = 0;
        bool flag1 =false;
        
        for (int i = 0; i < no_of_events; i++)
        {
            if (color[i] == 0)
            {
               bool flag = DFS_visit(i, color, predecessor, discovery_time, finish_time);
               if(flag)
               {
                flag1 =true;
               }
            }
        }

        vector<pair<int, int>> result(no_of_events);
        for (int i = 0; i < no_of_events; i++)
        {
            result[i].first = i;
            result[i].second = finish_time[i];
        }
        return {flag1,result};
    }

    bool DFS_visit(int u, vector<int> &c, vector<int> &p, vector<int> &d, vector<int> &f)
    {
        time++;
        d[u] = time;
        c[u] = 1;
        bool flag = false;

        for (auto it : AdjList[u])
        {
            if (c[it] == 0)
            {
                p[it] = u;
                if (DFS_visit(it, c, p, d, f))
                {
                    flag =true;
                }
            }
            else if(c[it] == 1)
            {
                // Back edge detected (cycle)
                flag = true;
            }
        }
        time++;
        f[u] = time;
        c[u] = 2;
        return flag;
    }
    

};

// is cycle
class isCycle:public GraphAlgorithm
{   
    private:

    bool flag;

    public:

    isCycle(int n, int m) : GraphAlgorithm(n, m), flag(false){};

    void Query()
    {
        pair<bool , vector<pair<int,int>>> result = DFS();
        flag = result.first;
    }

    bool gets()
    {
        return flag;
    }
};

class indepComponent:public GraphAlgorithm
{   
    public:

    indepComponent(int n, int m):GraphAlgorithm(n, m){};

    vector<vector<int>> scc;
    void Query()
    {
        pair<bool , vector<pair<int,int>>> result = DFS();
        vector<pair<int,int>> finish_times = result.second;

        sort(finish_times.begin(), finish_times.end(), customsort());

        vector<int> order;
        for(auto it : finish_times)
        {
            order.push_back(it.first);
        }
        vector<int> color(no_of_events, 0);
        for(int u : order)
        {
            if(color[u] == 0)
            {   
                vector<int> component;
                DFS_SCC(u, color, component);
                scc.push_back(component);
            }
        }
    }

    void DFS_SCC(int u, vector<int> &color, vector<int> &component)
    {
        color[u] = 1;
        component.push_back(u);
        for(auto it: reverse_adjlist[u])
        {   
            if(color[it]==0)
            {
                DFS_SCC(it,color,component);
            }
        }
    }

    vector<vector<int>> getSCC()
    {
        return scc;
    }

    int getMaximalGroupSize()
    {
        int max_size = 0;
        for(auto component : scc)
        {
            if(component.size() > max_size)
            {
                max_size = component.size();
            }
        }
        return max_size;
    }
};

class validOrder:public GraphAlgorithm
{
    public:

    vector<int> topo_sort;

    validOrder(int n, int m) : GraphAlgorithm(n, m){};

    void Query()
    {
        vector<int> indegree(no_of_events,0);

        for(int i=0;i<no_of_events;i++)
        {
            for(auto it: AdjList[i])
            {
                indegree[it]++;
            }
        }

        priority_queue<int,vector<int>, greater<int>>pq;

        for(int i=0;i<no_of_events;i++)
        {
            if(indegree[i]==0)
            {
                pq.push(i);
            }
        }

        while(!pq.empty())
        {
            int s = pq.top();pq.pop();
            for(auto it: AdjList[s])
            {
                indegree[it]--;
                if(indegree[it]==0)
                {
                    pq.push(it);
                }
            }
            topo_sort.push_back(s);
        }
    }
};

class maxHype:public GraphAlgorithm
{
    public:

    int max_hype_score;
    vector<vector<int>> scc; 

    maxHype(int n, int m) : GraphAlgorithm(n, m), max_hype_score(0){};

    void setSCC(vector<vector<int>> scc_data)
    {
        scc = scc_data; // Set SCCs from indepComponent
    }

    void Query()
    {

        vector<int> condensed_score(scc.size(), 0);
        vector<int> component_id(no_of_events, -1);
        for(int i=0; i<scc.size(); i++)
        {
            for(int event : scc[i])
            {
                component_id[event] = i;
                condensed_score[i] += hypescores[event];
            }
        }

        vector<set<int>> condensed_graph(scc.size());
        for(int u=0; u<no_of_events; u++)
        {
            for(int v: AdjList[u])
            {
                if(component_id[u] != component_id[v])
                {
                    condensed_graph[component_id[u]].insert(component_id[v]);
                }
            }
        }
        vector<int> visited(scc.size(),0);
        for(int u=0; u<scc.size(); u++)
        {
            if(!visited[u])
            {
                DFS_maxHype(u, condensed_graph, condensed_score, visited, 0);
            }
        }
    }

    void DFS_maxHype(int u, vector<set<int>> &condensed_graph, vector<int> &condensed_score, vector<int> &visited, int cur_score)
    {
        visited[u] = 1;
        cur_score += condensed_score[u];
        max_hype_score = max(max_hype_score, cur_score);

        for(int v : condensed_graph[u])
        {
            if(!visited[v])
            {
                DFS_maxHype(v, condensed_graph, condensed_score, visited, cur_score);
            }
        }
        visited[u] = 0;
    }

    int getMaxHypeScore()
    {
        return max_hype_score; 
    }
};



int main()
{
    int N,M;

    cin >> N >> M;

    GraphAlgorithm g(N, M);
    isCycle *C = new isCycle(N, M);
    indepComponent *indcomp = new indepComponent(N, M);
    validOrder *valid = new validOrder(N, M);
    maxHype *max = new maxHype(N, M);   


    for( int i = 0; i < N; i++)
    {
        int h;
        cin >> h;
        g.addhype(h);
        C->addhype(h);
        valid->addhype(h);
        indcomp->addhype(h);
        max->addhype(h);
    }

    for( int i = 0; i < M; i++)
    {
        int u,v;

        cin >> u >> v;
        u--;v--;
        g.addedge(u, v);
        C->addedge(u, v);
        valid->addedge(u, v);
        indcomp->addedge(u, v);
        max->addedge(u, v);
    }

    C->Query();         // precompute 
    indcomp->Query();   // precompute
    valid->Query();  // precompute
    max->setSCC(indcomp->getSCC());   
    max->Query();       // precompute

    int queries;

    cin >> queries;

    while ( queries-- )
    {
        int a;

        cin >> a;

        if(a == 1)
        {
            if(C->gets())
            {
                cout << "YES" << '\n';
            }
            else
            {
                cout << "NO" << '\n';
            }
        }
        else if( a == 2)
        {
            vector<vector<int>> scc = indcomp->getSCC();
            int max_size = indcomp->getMaximalGroupSize();
            cout << scc.size() << " " << max_size << '\n';
        }
        else if( a == 3)
        {
            if(!C->gets())
            {
                vector<int> topo_sorting = valid->topo_sort;
                for (auto it : topo_sorting) {
                    cout << it +1 << " ";
                }
                cout << '\n';
            }
            else
            {
                cout << "NO" <<'\n';
            }
        }
        else
        {
            cout << max->getMaxHypeScore() << '\n';
        }
    }



}

