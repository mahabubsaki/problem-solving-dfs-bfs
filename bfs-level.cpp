#include <bits/stdc++.h>
using namespace std;
const int N = 1e5;
vector<int> adj_list[N];
int visited[N];
int level[N];
void bfs(int src)
{
    queue<int> q;
    q.push(src);
    visited[src] = 1;
    level[src] = 0;
    while (!q.empty())
    {
        int head = q.front();
        q.pop();

        for (int adj_node : adj_list[head])
        {
            if (visited[adj_node] == 0)
            {
                visited[adj_node] = 1;
                level[adj_node] = level[head] + 1;
                q.push(adj_node);
            }
        }
    }
};
int main()
{
    int nodes, edges;
    cin >> nodes >> edges;
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    int src = 0;
    bfs(src);
    for (int i = 0; i < nodes; i++)
    {
        cout << "Node :" << i << " -> level : " << level[i] << endl;
    }

    return 0;
}