#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int visited[N];

int color[N];

vector<int> adj_list[N];

bool dfs(int node)
{
    visited[node] = 1;
    for (int adj_node : adj_list[node])
    {
        if (visited[adj_node] == 0)
        {
            if (color[node] == 1)
                color[adj_node] = 2;
            else
                color[adj_node] = 1;
            bool is_done = dfs(adj_node);
            if (!is_done)
            {
                return false;
            }
        }
        else
        {
            if (color[node] == color[adj_node])
            {
                return false;
            }
        }
    }
    return true;
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
    bool is_done = true;
    for (int i = 1; i <= nodes; i++)
    {
        if (visited[i] == 0)
        {
            color[i] = 1;
            bool ok = dfs(i);
            if (!ok)
            {
                is_done = false;
                break;
            }
        }
    }
    if (!is_done)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        for (int i = 1; i <= nodes; i++)
        {
            cout << color[i] << " ";
        }
    }
    return 0;
}