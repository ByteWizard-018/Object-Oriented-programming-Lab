#include <bits/stdc++.h>
using namespace std;
// typedef int long long;
template<typename T>
class min_heap
{   
    private:

    vector <T> heap_elements;
    int cursize;

    public:

    // min_heap(){};
    min_heap(int size =20): heap_elements(size), cursize(0){};

    vector<pair < int, T> > getheap()
    {
        return heap_elements; // getter
    }

    int getcursize()
    {
        return cursize; // getter
    }

    void setcursize(int x)
    {
        cursize = x; //setter
    }

    void setheap(vector<T> &h)
    {
        heap_elements = h;   //setter
    }



    size_t size()
    {
        return getcursize();
    }    

    void push(const T& t)
    {
        if(isFull())
        {
            heap_elements.resize(2*getcursize());
        }
        
        int m = cursize;
        heap_elements[m] = t;
        cursize++;
        percolateup(cursize);
    }


    void pop()
    {
       if(empty())
       {
           //do nothing
       }
       else
       { 
        heap_elements[0] = heap_elements[cursize-1];
        cursize--;
        percolateDown();
        

       }
    }

    void percolateDown()
    {
        int i = 0;
        while( 2*i+1 < cursize )
        {   
            if(2*i+2 < cursize )
            {
                if(heap_elements[2*i+1] < heap_elements[2*i+2])
                {
                    swap(heap_elements[i] , heap_elements[2*i+1]);
                    i = 2*i+1;
                }
                else
                {
                    swap(heap_elements[i] , heap_elements[2*i+2]);
                    i = 2*i+2;
                }
            }
            else
            {
                swap(heap_elements[i],heap_elements[2*i+1]);
                i = 2*i+1;
            }
        }
    }


    void percolateup(int m)
    {
        int i = m-1;
        while( heap_elements[i] < heap_elements[(i-1)/2] )
        {
            swap(heap_elements[(i-1)/2] , heap_elements[i]);
            i = (i-1)/2;
            if(i == 0)
            {
                break;
            }
        }
    }

    T& top()
    {
        return heap_elements[0];
    }
    const bool empty() const
    {
        return (cursize == 0); /// check whether its equal to zero or not!!
    }

    bool isFull()
    {
        return  cursize == heap_elements.size();  // this is usefull for resizing the heap
    }
};


class Node
{
    private:
    string roomID;
    int distance;
    int edgeCount;
    public:

    Node(){} // default constructor
    Node(string roomID, int distance, int edcount):roomID(roomID), distance(distance),edgeCount(edcount){}; // parametrized constructor

    string getroomid()
    {
        return roomID; // getroom id
    }

    int getdistance()
    {
        return distance; // getdistance
    }

    int getedgecount()
    {
    return edgeCount;
    }

    void setroomid(string id)
    {
        roomID = id;     // set the room id
    }

    void setdistance(int x)
    {
        distance = x;   // set distance
    }

    void setedgecount(int x)
    {
    edgeCount = x;
    }

    // operator overloading

    bool operator<(const Node& other)
    {
        return distance < other.distance;
    }

};

void dijkstra(unordered_map<string, vector<pair<string, int>>> &adjlist, string &source, string &destination)
{
    int  n = adjlist.size();
    unordered_map<string,array<int,2>> result;

    for(auto it : adjlist)
    {
        result[it.first][0] = INT_MAX;
        result[it.first][1] = INT_MAX;
    }

    min_heap<Node> pq;
    Node t(source,0,0);
    result[source][0] =0;
    pq.push(t);

    while(!pq.empty())
    {   
        Node n = pq.top();
        
        pq.pop();
        int dist = n.getdistance();
        int edgecount = n.getedgecount();
        string roomid = n.getroomid();
        
        for(auto &it: adjlist[roomid])
        {
            int edgeweight = it.second;
            string roomid_adj = it.first;
            int next_dist = edgeweight+dist;
            Node temp(roomid_adj,next_dist,edgecount+1);
            if(next_dist < result[roomid_adj][(edgecount+1) % 2 ])
            {

                pq.push(temp);
                result[roomid_adj][(edgecount+1) %2] = next_dist;
            }

        }
    }

    if(result[destination][0] != INT_MAX)
    {
        cout << result[destination][0] << '\n';
    }
    else
    {
        cout << "-1" << '\n';
    }
}





int main()
{
    int n,m;
    cin >> n >> m;

    unordered_map<string, vector<pair<string,int> >> adjlist;   // creating adjlist
    vector<string> rooms(n);                                       // room ids

    for(int i = 0; i < n; i++ )
    {
        cin >> rooms[i];
    }

    for(int i = 0; i < m; i++ )
    {
        string s1,s2;
        cin >> s1 >> s2;
        int weight;
        cin >> weight;
        adjlist[s1].push_back({s2,weight});
        adjlist[s2].push_back({s1,weight});
    }

    string source,destination;
    cin >> source >> destination;

    dijkstra(adjlist, source, destination);
}
