#include <bits/stdc++.h>
using namespace std;
const int N = 20;

int maze[N][N], visited[N][N], level[N][N];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
pair<int, int> src, final_dest;

vector<pair<int, int>> path;
queue<pair<int, int>> safe_boundry;
int row, column;

bool is_safe(pair<int, int> coord)
{
    int x = coord.first;
    int y = coord.second;
    if (maze[x][y] == -2 || x < 0 || y < 0 || x >= row || y >= column)
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

void determine_safe_boundry()
{
    for (int i = 0; i < column; i++)
    {
        if (maze[0][i] == 1)
        {
            safe_boundry.push({0, i});
        }
    }
    for (int i = 0; i < column; i++)
    {
        if (maze[row - 1][i] == 1)
        {
            safe_boundry.push({row - 1, i});
        }
    }
    for (int i = 1; i < row - 1; i++)
    {
        if (maze[i][0] == 1)
        {
            safe_boundry.push({i, 0});
        }
    }

    for (int i = 1; i < row - 1; i++)
    {
        if (maze[i][column - 1] == 1)
        {
            safe_boundry.push({i, column - 1});
        }
    }
}

bool findPath(int r, int c)
{
    if (!is_safe({r, c}))
    {
        return false;
    }
    if (r == final_dest.first && c == final_dest.second)
    {
        path.push_back({r, c});
        return true;
    }
    int originalValue = maze[r][c];
    maze[r][c] = -2;
    if (findPath(r - 1, c) || findPath(r + 1, c) ||
        findPath(r, c - 1) || findPath(r, c + 1))
    {
        path.push_back({r, c});
        maze[r][c] = originalValue;
        return true;
    }
    return false;
}

void bfs(pair<int, int> src_node)
{
    queue<pair<int, int>> q;

    q.push(src_node);
    while (!q.empty())
    {
        pair<int, int> head = q.front();
        q.pop();
        int x = head.first;
        int y = head.second;
        visited[x][y] = 1;
        for (int i = 0; i < 4; i++)
        {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            pair<int, int> adj_node = {new_x, new_y};
            if (is_safe(adj_node) && is_available(adj_node))
            {
                visited[new_x][new_y] = 1;
                level[new_x][new_y] = level[x][y] + 1;
                q.push(adj_node);
            }
        }
    }
}

void resetLevel()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            level[i][j] = -1;
        }
    }
}

void resetVisited()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            visited[i][j] = 0;
        }
    }
}

int main()
{

    cin >> row >> column;

    resetLevel();
    for (int i = 0; i < row; i++)
    {
        string input;
        cin >> input;
        for (int j = 0; j < column; j++)
        {
            if (input[j] == '#' || input[j] == 'M')
            {
                maze[i][j] = -2;
            }
            else if (input[j] == 'A')
            {
                src = {i, j};
                maze[i][j] = 1;
            }
            else
            {
                maze[i][j] = 1;
            }
        }
    }
    determine_safe_boundry();
    while (!safe_boundry.empty())
    {
        pair<int, int> dst = safe_boundry.front();
        safe_boundry.pop();
        bfs(dst);
        if (level[src.first][src.second] == -1)
        {
            resetLevel();
            resetVisited();
            maze[dst.first][dst.second] = -2;
        }
        else
        {
            final_dest = dst;
            break;
        }
    }
    bool foundPath = findPath(src.first, src.second);
    if (foundPath)
    {
        cout << "Yes" << endl;
        cout << path.size() - 1 << endl;
        reverse(path.begin(), path.end());
        for (int i = 1; i < path.size(); i++)
        {
            if (src.first - 1 == path[i].first && src.second == path[i].second)
            {
                cout << "U";
                src = path[i];
            }
            else if (src.first + 1 == path[i].first && src.second == path[i].second)
            {
                cout << "D";
                src = path[i];
            }
            else if (src.first == path[i].first && src.second + 1 == path[i].second)
            {
                cout << "R";
                src = path[i];
            }
            else
            {
                cout << "L";
                src = path[i];
            }
        }
        cout << endl;
    }
    else
    {
        cout << "No" << endl;
    }
    return 0;
}