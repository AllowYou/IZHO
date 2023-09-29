#include <bits/stdc++.h>
using namespace std;

#define fs first
#define ss second
#define endl '\n'
#define all(x) (x).begin(), (x).end()

#define print(x)          \
    for (auto a : x)      \
        cout << a << ' '; \
    cout << endl;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // Partial results: 36 points

    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    bool sub1 = 1, sub2 = 1;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        sub1 &= (a == 1 and b == i + 2);
        sub2 &= (a == i + 1 and b == i + 2);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    int q;
    cin >> q;
    while (q--)
    {
        int r;
        cin >> r;
        vector<int> a(r);
        for (int i = 0; i < r; i++)
            cin >> a[i];
        int l;
        cin >> l;
        vector<int> b(l);
        for (int i = 0; i < l; i++)
            cin >> b[i];
        if (sub1 and r == 1 and r == l)
        {
            if (a[0] == 1)
                cout << n - 1 << ':' << 1 << endl;
            else if (b[0] == 1)
                cout << 1 << ':' << n - 1 << endl;
            else
                cout << n << ':' << 0 << endl;
        }
        else if (sub2 and r == 1 and r == l)
        {
            if (b[0] < a[0])
            {
                swap(b[0], a[0]);
                int diff = b[0] - a[0] - 1, l1 = a[0] - 1, l2 = n - b[0];
                swap(l1, l2);
                if (diff == 0)
                {
                    cout << l1 + 1 << ':' << l2 + 1 << endl;
                    continue;
                }
                if (diff == 1)
                {
                    cout << n << ':' << 0 << endl;
                    continue;
                }
                l1 += (diff - 1) / 2;
                l2 += (diff - 2) / 2;
                if (l1 > l2)
                    l1 += 2;
                else
                    l2 += 2;
                cout << l1 + 1 << ":" << l2 + 1 << endl;
            }
            else
            {
                int diff = b[0] - a[0] - 1, l1 = a[0] - 1, l2 = n - b[0];
                if (diff == 0)
                {
                    cout << l1 + 1 << ':' << l2 + 1 << endl;
                    continue;
                }
                if (diff == 1)
                {
                    cout << n << ':' << 0 << endl;
                    continue;
                }
                l1 += (diff - 1) / 2;
                l2 += (diff - 2) / 2;
                if (l1 > l2)
                    l1 += 2;
                else
                    l2 += 2;
                cout << l1 + 1 << ":" << l2 + 1 << endl;
            }
        }
        else
        {
            vector<int> parent(n + 1);
            vector<bool> used(n + 1);
            queue<int> q;
            q.push(a[0]);
            used[a[0]] = true;

            while (!q.empty())
            {
                int x = q.front();
                q.pop();

                for (auto neighbour : graph[x])
                {
                    if (!used[neighbour])
                    {
                        used[neighbour] = true;
                        q.push(neighbour);
                        parent[neighbour] = x;
                    }
                }
            }

            vector<int> path;
            int x = parent[b[0]];
            while (x != a[0])
            {
                path.push_back(x);
                x = parent[x];
            }
            if (path.size() == 1)
                cout << n << ":" << 0 << endl;
            else if (path.size() == 0)
            {
                used.clear();
                used.resize(n + 1);
                used[b[0]] = 1;
                queue<int> q;
                q.push(a[0]);
                used[a[0]] = 1;
                int cnt = 1;
                while (!q.empty())
                {
                    int x = q.front();
                    q.pop();

                    for (auto neighbour : graph[x])
                    {
                        if (!used[neighbour])
                        {
                            q.push(neighbour);
                            used[neighbour] = 1;
                            cnt++;
                        }
                    }
                }
                cout << cnt << ':' << n - cnt << endl;
            }
            else
            {
                used.clear();
                used.resize(n + 1);
                int i = 0, j = path.size() - 1, l1 = 1, l2 = 1;
                used[a[0]] = 1;
                used[b[0]] = 1;
                queue<int> qu;
                q.push(a[0]);
                qu.push(b[0]);
                reverse(all(path));
                while (j - i > 1)
                {
                    q.push(path[i]);
                    used[path[i]] = 1;
                    l1++;
                    i++;
                    if (j - i > 1)
                    {
                        qu.push(path[j]);
                        used[path[j]] = 1;
                        l2++;
                        j--;
                    }
                }
                used[path[i]] = 1;
                used[path[i + 1]] = 1;
                while (!q.empty())
                {
                    int x = q.front();
                    q.pop();

                    for (auto neighbour : graph[x])
                    {
                        if (!used[neighbour])
                        {
                            used[neighbour] = 1;
                            q.push(neighbour);
                            l1++;
                        }
                    }
                }
                while (!qu.empty())
                {
                    int x = qu.front();
                    qu.pop();

                    for (auto neighbour : graph[x])
                    {
                        if (!used[neighbour])
                        {
                            used[neighbour] = 1;
                            qu.push(neighbour);
                            l2++;
                        }
                    }
                }
                if (l1 > l2)
                {
                    q.push(path[i]);
                    q.push(path[i + 1]);
                    l1 += 2;
                }
                else
                {
                    qu.push(path[i]);
                    qu.push(path[i + 1]);
                    l2 += 2;
                }
                while (!q.empty())
                {
                    int x = q.front();
                    q.pop();

                    for (auto neighbour : graph[x])
                    {
                        if (!used[neighbour])
                        {
                            used[neighbour] = 1;
                            q.push(neighbour);
                            l1++;
                        }
                    }
                }
                while (!qu.empty())
                {
                    int x = qu.front();
                    qu.pop();

                    for (auto neighbour : graph[x])
                    {
                        if (!used[neighbour])
                        {
                            used[neighbour] = 1;
                            qu.push(neighbour);
                            l2++;
                        }
                    }
                }
                cout << l1 << ':' << l2 << endl;
            }
        }
    }
}
