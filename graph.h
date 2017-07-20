#pragma once
#include <vector>
#include <queue>

using namespace std;

// This value is treated as infinity (e.g. infinite distance ~ unreachable)
const int oo = 0x3f3f3f3f;

class Graph
{
    public:
    // connectivity matrix
    vector< vector<int> > c;

    Graph(int n = 0) : c(n) {}
    Graph(const Graph &g) : c(g.c) {}
    Graph(const vector< vector<int> > &c) : c(c) {}

    void connect(int from, int to) { c[from].push_back(to); }

    int size() { return c.size(); }
    void resize(int newSize) { c.resize(newSize); }

    int countEdges()
    {
        int res = 0;
        for(int i = 0; i < size(); i++) res += c[i].size();
        return res;
    }

    int countUndirectedEdges()
    {
        int res = 0;
        for(int i = 0; i < size(); i++)
            for(int j = 0; j < c[i].size(); j++) if (i <= c[i][j]) res++;
        return res;
    }

    // Auxiliary data-structures for various algorithms:
    vector<int> distance;
    vector<int> visited;
    vector<int> pre;
    vector<int> post;

    int counter;
    int currentColour;

    // Depth-First Search
    void runDFS(int src, int colour = 1)
    {
        pre    .assign(size(), 0);
        post   .assign(size(), 0);
        visited.assign(size(), 0);
        counter = 0;
        currentColour = colour;
        dfs(src);
    }
    // Repeated DFS, returns the number of times DFS was run
    int runRepeatedDFS()
    {
        pre    .assign(size(), 0);
        post   .assign(size(), 0);
        visited.assign(size(), 0);
        counter = 0;
        currentColour = 0;
        for(int i = 0; i < size(); i++)
        if (!visited[i])
        {
            currentColour++;
            dfs(i);
        }
        return currentColour;
    }
    void dfs(int v)
    {
        if (visited[v]) return;
        visited[v] = currentColour;
        pre[v] = counter++;
        for(int i = 0; i < c[v].size(); i++) dfs(c[v][i]);
        post[v] = counter++;
    }
    // Breadth-First Search, returns the eccentricity of the source vertex
    int runBFS(int src, int colour = 1)
    {
        visited.assign(size(), 0);
        distance.assign(size(), oo);
        currentColour = colour;
        return bfs(src);
    }
    // Repeated BFS, returns the number of times BFS was run
    int runRepeatedBFS(int src, int colour = 1)
    {
        visited.assign(size(), 0);
        distance.assign(size(), oo);
        currentColour = 0;
        for(int i = 0; i < size(); i++)
        if (!visited[i])
        {
            currentColour++;
            bfs(i);
        }
        return currentColour;
    }
    int bfs(int v)
    {
        queue<int> Q;
        Q.push(v);
        counter = distance[v] = 0;
        visited[v] = currentColour;
        while(!Q.empty())
        {
            v = Q.front(); Q.pop();
            for(int i = 0; i < c[v].size(); i++)
            {
                int u = c[v][i];
                if (distance[u] == oo)
                {
                    visited[u] = currentColour;
                    counter = distance[u] = distance[v] + 1;
                    Q.push(u);
                }
            }
        }
        return counter;
    }
    // Find all bridges
    void findBridges(vector< pair<int, int> > &result)
    {
        result.clear();
        pre .assign(size(), 0);
        post.assign(size(), 0); // here: the earliest seen vertex
        counter = 1;
        for(int i = 0; i < size(); i++) if (!pre[i]) bridgesDFS(i, -1, result);
    }
    void bridgesDFS(int v, int parent, vector< pair<int, int> > &result)
    {
        post[v] = pre[v] = counter++;
        for(int i = 0; i < c[v].size(); i++)
        {
            int to = c[v][i];
            if (to == parent) continue;
            if (pre[to]) post[v] = min(post[v], pre[to]);
            else
            {
                bridgesDFS(to, v, result);
                post[v] = min(post[v], post[to]);
                if (post[to] > pre[v]) result.push_back(make_pair(v, to));
            }
        }
    }
};
