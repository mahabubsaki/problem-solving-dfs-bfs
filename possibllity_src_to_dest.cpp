#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
vector<int> adj_list[N];
int visited[N];

void bfs(int src)
{
    visited[src] = 1;
    queue<int> q;
    q.push(src);
    while (!q.empty())
    {
        int head = q.front();
        q.pop();
        for (int adj_node : adj_list[head])
        {
            if (visited[adj_node] == 0)
            {
                visited[adj_node] = 1;
                q.push(adj_node);
            }
        }
    }
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
    int src = 1;
    bfs(src);
    if (visited[nodes])
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }
    return 0;
}