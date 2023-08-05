#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

int visited[N];
vector<int> adj_list[N];

bool dfs(int node, int parent_node)
{
    visited[node] = 1;

    for (int adj_node : adj_list[node])
    {
        if (visited[adj_node] == 0)
        {
            bool is_cycle = dfs(adj_node, node);
            if (is_cycle)
            {
                return true;
            }
        }
        else if (visited[adj_node] == 1 && adj_node != parent_node)
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
        adj_list[to].push_back(from);
    }
    bool is_cycle = false;
    for (int i = 1; i <= nodes; i++)
    {
        if (visited[i] == 0)
        {
            bool ok = dfs(i, -1);
            if (ok)
            {
                is_cycle = true;
                break;
            }
        }
    }

    if (is_cycle)
    {
        cout << "Cycle Exist" << endl;
    }
    else
    {
        cout << "No Cycle" << endl;
    }

    return 0;
}