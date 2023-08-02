#include <bits/stdc++.h>
using namespace std;
const int N = 2002;

int maze[N][N], visited[N][N];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
int n, m;

bool is_inside(pair<int, int> coord)
{
    int x = coord.first;
    int y = coord.second;
    if (x >= 0 && x < n && y >= 0 && y < m)
    {
        return true;
    }
    return false;
}

bool is_safe(pair<int, int> coord)
{
    int x = coord.first;
    int y = coord.second;
    if (maze[x][y] == -1)
    {
        return false;
    }
    return true;
}

bool is_available(pair<int, int> coord)
{
    int x = coord.first;
    int y = coord.second;
    if (visited[x][y] == 0)
    {
        return true;
    }
    return false;
}

void bfs(pair<int, int> src)
{
    queue<pair<int, int>> q;
    visited[src.first][src.second] = 0;

    q.push(src);
    while (!q.empty())
    {
        pair<int, int> head = q.front();
        q.pop();
        int x = head.first;
        int y = head.second;
        for (int i = 0; i < 4; i++)
        {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            pair<int, int> adj_node = {new_x, new_y};
            if (is_inside(adj_node) && is_safe(adj_node) && is_available(adj_node))
            {
                visited[new_x][new_y] = 1;

                q.push(adj_node);
            }
        }
    }
}

pair<int, int> find_unvisited()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (visited[i][j] == 0 && maze[i][j] == 0)
            {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

int main()
{

    int count = 0;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        string input;
        cin >> input;
        for (int j = 0; j < m; j++)
        {
            if (input[j] == '#')
            {
                maze[i][j] = -1;
            }
        }
    }
    while (true)
    {
        pair<int, int> unvisited_cell = find_unvisited();
        if (unvisited_cell.first == -1)
        {
            break;
        }

        bfs(unvisited_cell);
        count++;
    }
    cout << count << endl;

    return 0;
}

// 5 8
// ########
// #..#...#
// ######.#
// #......#
// ########