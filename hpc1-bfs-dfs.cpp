#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

void bfs(int start, const vector<vector<int>> &adj, vector<bool> &visited)
{
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        cout << "Visited (BFS) Node: " << node << endl;

        vector<int> neighbors;

        #pragma omp parallel for
        for (int i = 0; i < adj[node].size(); ++i)
        {
            int neighbor = adj[node][i];
            int thread_id = omp_get_thread_num();

            if (!visited[neighbor])
            {
                #pragma omp critical
                {
                    if (!visited[neighbor])
                    {
                        visited[neighbor] = true;
                        neighbors.push_back(neighbor);
                        cout << "Thread " << thread_id << " processing neighbor (BFS): " << neighbor << endl;
                    }
                }
            }
        }

        for (int neighbor : neighbors)
        {
            q.push(neighbor);
        }
    }
}

void dfs(int node, const vector<vector<int>> &adj, vector<bool> &visited)
{
    visited[node] = true;
    cout << "Visited (DFS) Node: " << node << endl;

    #pragma omp parallel for
    for (int i = 0; i < adj[node].size(); ++i)
    {
        int neighbor = adj[node][i];
        int thread_id = omp_get_thread_num();

        if (!visited[neighbor])
        {
            #pragma omp critical
            {
                if (!visited[neighbor])
                {
                    cout << "Thread " << thread_id << " processing neighbor (DFS): " << neighbor << endl;
                    dfs(neighbor, adj, visited);
                }
            }
        }
    }
}

int main()
{
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<int>> adj(n);

    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(n, false);

    cout << "\nBFS starting from node 0:\n";
    bfs(0, adj, visited);

    visited.assign(n, false);

    cout << "\nDFS starting from node 0:\n";
    dfs(0, adj, visited);

    return 0;
}
