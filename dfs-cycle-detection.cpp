#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;

int visited[N];
vector<int> adj_list[N];

bool dfs(int node)
{
    visited[node] = 1;

    for (int adj_node : adj_list[node])
    {
        if (visited[adj_node])
        {
            bool is_cycle = dfs(adj_node);
            if (is_cycle)
            {
                return true;
            }
        }
        else if (visited[adj_node] == 1)
        {
            return true;
        }
    }
    visited[node] = 2;
    return false;
}

int main()
{
    int nodes, edges;
    cin >> nodes >> edges;
    for (int i = 0; i < edges; i++)
    {
        int from, to;
        cin >> from >> to;
        adj_list[from].push_back(to);
    }
    bool is_cycle = false;
    for (int i = 1; i <= nodes; i++)
    {
        if (visited[i] == 0)
        {
            bool ok = dfs(i);
            if (ok)
            {
                is_cycle = true;
                break;
            }
        }
    }

    if (is_cycle)
    {
    }
    else
    {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}