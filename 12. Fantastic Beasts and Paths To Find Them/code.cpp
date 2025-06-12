#include <bits/stdc++.h>
using namespace std;

double calcDistance(pair<int, int> a, pair<int, int> b)
{
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

class Island
{
public:
    virtual void takeinput() = 0;

    friend istream& operator>>(istream& inp, Island* island)
    {
        island->takeinput();
        return inp;
    }

    virtual void print() = 0;

    friend ostream& operator<<(ostream& out, Island* island)
    {
        island->print();
        return out;
    }

    virtual void findAndSetMaxLen() = 0;
    virtual void findAndSetCentroid() = 0;
    virtual string getid() = 0;
    virtual double getmaxLength() = 0;
    virtual pair<int, int> getCentroid() = 0;
};

class Rectangle : public Island
{
public:
    void takeinput()
    {
        cin >> islandId;
        cin >> coordinate_1.first >> coordinate_1.second;
        cin >> coordinate_2.first >> coordinate_2.second;
        cin >> coordinate_3.first >> coordinate_3.second;
        cin >> coordinate_4.first >> coordinate_4.second;
    }

    void print()
    {
        cout << islandId;
    }

    void findAndSetMaxLen()
    {
        findAndSetCentroid();
        double d1 = calcDistance(coordinate_1, centroid);
        double d2 = calcDistance(coordinate_2, centroid);
        double d3 = calcDistance(coordinate_3, centroid);
        double d4 = calcDistance(coordinate_4, centroid);
        maxLen = max({d1, d2, d3, d4});
    }

    void findAndSetCentroid()
    {
        int x = (coordinate_1.first + coordinate_2.first + coordinate_3.first + coordinate_4.first);
        int y = (coordinate_1.second + coordinate_2.second + coordinate_3.second + coordinate_4.second);
        centroid.first = x / 4;
        centroid.second = y / 4;
    }

    string getid()
    {
        return islandId;
    }

    double getmaxLength()
    {
        return maxLen;
    }

    pair<int, int> getCentroid()
    {
        return centroid;
    }

private:
    string islandId;
    pair<int, int> coordinate_1;
    pair<int, int> coordinate_2;
    pair<int, int> coordinate_3;
    pair<int, int> coordinate_4;
    pair<int, int> centroid;
    double maxLen;
};

class Triangle : public Island
{
public:
    void takeinput()
    {
        cin >> islandId;
        cin >> coordinate_1.first >> coordinate_1.second;
        cin >> coordinate_2.first >> coordinate_2.second;
        cin >> coordinate_3.first >> coordinate_3.second;
    }

    void print()
    {
        cout << islandId;
    }

    void findAndSetMaxLen()
    {
        findAndSetCentroid();
        double d1 = calcDistance(coordinate_1, centroid);
        double d2 = calcDistance(coordinate_2, centroid);
        double d3 = calcDistance(coordinate_3, centroid);
        maxLen = max({d1, d2, d3});
    }

    void findAndSetCentroid()
    {
        int x = (coordinate_1.first + coordinate_2.first + coordinate_3.first);
        int y = (coordinate_1.second + coordinate_2.second + coordinate_3.second);
        centroid.first = x / 3;
        centroid.second = y / 3;
    }

    string getid()
    {
        return islandId;
    }

    double getmaxLength()
    {
        return maxLen;
    }

    pair<int, int> getCentroid()
    {
        return centroid;
    }

private:
    string islandId;
    pair<int, int> coordinate_1;
    pair<int, int> coordinate_2;
    pair<int, int> coordinate_3;
    pair<int, int> centroid;
    double maxLen;
};

class Circle : public Island
{
public:
    void takeinput()
    {
        cin >> islandId;
        cin >> centerCoords.first >> centerCoords.second;
        cin >> radius;
    }

    void print()
    {
        cout << islandId;
    }

    void findAndSetMaxLen()
    {
        maxLen = radius;
    }

    void findAndSetCentroid()
    {
        centroid = centerCoords;
    }

    string getid()
    {
        return islandId;
    }

    double getmaxLength()
    {
        return maxLen;
    }

    pair<int, int> getCentroid()
    {
        return centroid;
    }

private:
    string islandId;
    pair<int, int> centerCoords;
    pair<int, int> centroid;
    int radius;
    double maxLen;
};

class PathFinder
{
public:
    PathFinder(vector<vector<bool>> adjMatrix, int n, vector<Island*> nodes) : adj(adjMatrix), n(n), nodes(nodes) {}

    vector<int> findPath()
    {
        vector<vector<int>> dp(1 << n, vector<int>(n, 0));
        vector<vector<int>> parent(1 << n, vector<int>(n, -1));

        for (int i = 0; i < n; i++)
        {
            dp[1 << i][i] = 1;
        }

        for (int bitMask = 1; bitMask < (1 << n); bitMask++)
        {
            for (int last = 0; last < n; last++)
            {
                if (dp[bitMask][last])
                {
                    for (int next = 0; next < n; next++)
                    {
                        if (!(bitMask & (1 << next)) && adj[last][next])
                        {
                            if (dp[bitMask | (1 << next)][next] < dp[bitMask][last] + 1)
                            {
                                dp[bitMask | (1 << next)][next] = dp[bitMask][last] + 1;
                                parent[bitMask | (1 << next)][next] = last;
                            }
                        }
                    }
                }
            }
        }

        int maxLen = 0, endNode = -1, finalMask = 0;
        for (int bitMask = 1; bitMask < (1 << n); bitMask++)
        {
            for (int i = 0; i < n; i++)
            {
                if (dp[bitMask][i] > maxLen)
                {
                    maxLen = dp[bitMask][i];
                    endNode = i;
                    finalMask = bitMask;
                }
            }
        }

        vector<int> path;
        int current = endNode;
        int bitMask = finalMask;
        while (current != -1)
        {
            path.push_back(current);
            int prev = parent[bitMask][current];
            if (prev == -1) break;
            bitMask ^= (1 << current);
            current = prev;
        }
        return path;
    }

private:
    vector<vector<bool>> adj;
    int n;
    vector<Island*> nodes;
};

int main()
{
    int n;
    cin >> n;
    int t = n;

    vector<Island*> nodes;

    while (t--)
    {
        string islandType;
        cin >> islandType;

        if (islandType == "RECTANGLE")
        {
            Island* rectangleShape = new Rectangle();
            cin >> rectangleShape;
            nodes.push_back(rectangleShape);
        }
        else if (islandType == "TRIANGLE")
        {
            Island* triangleShape = new Triangle();
            cin >> triangleShape;
            nodes.push_back(triangleShape);
        }
        else
        {
            Island* circleShape = new Circle();
            cin >> circleShape;
            nodes.push_back(circleShape);
        }
    }

    for (auto node : nodes)
    {
        node->findAndSetCentroid();
        node->findAndSetMaxLen();
    }

    vector<vector<bool>> adj(nodes.size(), vector<bool>(nodes.size(), false));
    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = 0; j < nodes.size(); j++)
        {
            if (i == j) continue;
            double dist = calcDistance(nodes[i]->getCentroid(), nodes[j]->getCentroid());
            if ((nodes[i]->getmaxLength() + nodes[j]->getmaxLength()) >= dist)
            {
                adj[i][j] = true;
            }
        }
    }

    PathFinder pathFinder(adj, nodes.size(), nodes);
    vector<int> path = pathFinder.findPath();
    if (path.size() == n)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
        cout << path.size() << "\n";
    }

// print path
    for (int i = 0; i < path.size(); i++)
    {
        cout << nodes[path[i]];
        if (i != path.size() - 1) cout << " ";
    }
    cout << "\n";
}