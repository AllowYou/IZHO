#include <bits/stdc++.h>
using namespace std;

#define print(a)          \
    for (auto x : a)      \
        cout << x << ' '; \
    cout << endl;

vector<vector<int>> graph1, graph2;
vector<int> sub1, sub2, parent1, parent2, news1, news2;
vector<bool> used1, used2;
set<int> ps;

struct SegTree
{
    int size = 1;
    vector<int> t;

    SegTree(int n)
    {
        while (size < n)
            size <<= 1;
        t.resize(size << 1);
    }

    void add(int l, int r, int x, int lx, int rx)
    {
        if (l <= lx and rx <= r)
        {
            t[x]++;
            return;
        }
        if (rx <= l or r <= lx)
            return;
        int m = (lx + rx) >> 1;
        add(l, r, (x << 1) + 1, lx, m);
        add(l, r, (x << 1) + 2, m, rx);
    }

    void add(int l, int r)
    {
        add(l, r, 0, 0, size);
    }

    int sum(int i, int x, int lx, int rx)
    {
        if (rx == lx + 1)
            return t[x];
        int m = (lx + rx) >> 1;
        if (i < m)
            return sum(i, (x << 1) + 1, lx, m) + t[x];
        else
            return sum(i, (x << 1) + 2, m, rx) + t[x];
    }

    int sum(int i)
    {
        return sum(i, 0, 0, size);
    }

    void clear()
    {
        t.clear();
        t.resize(size << 1);
    }
};

void dfs1(int i)
{
    used1[i] = true;
    int s = 1;
    for (int n : graph1[i])
    {
        if (!used1[n])
        {
            parent1[n] = i;
            dfs1(n);
            s += sub1[n];
        }
    }
    sub1[i] = s;
}

void dfs2(int i)
{
    used2[i] = true;
    int s = 1;
    for (int n : graph2[i])
    {
        if (!used2[n])
        {
            parent2[n] = i;
            dfs2(n);
            s += sub2[n];
        }
    }
    sub2[i] = s;
}

void dfs1(int node, int u)
{
    if (parent1[node] == 0)
    {
        news1[node] = (node == u ? sub1[node] : sub1[node] / 2);
        return;
    }

    dfs1(parent1[node], u);

    news1[node] = (node == u ? sub1[node] : (sub1[node] + 1) / 2) + news1[parent1[node]];
    ps.insert(node);
}

void dfs2(int node, int u)
{
    if (parent2[node] == 0)
    {
        news2[node] = (node == u ? sub2[node] : (sub2[node] + 1) / 2);
        return;
    }

    dfs2(parent2[node], u);

    news2[node] = (node == u ? sub2[node] : (sub2[node] + 1) / 2) + news2[parent2[node]];
    ps.insert(node);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // Partial results: 52 points

    int n;
    cin >> n;
    graph1.resize(n + 1);
    vector<int> cnt1(n + 1), cnt2(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        cnt1[a]++;
        cnt1[b]++;
        graph1[a].push_back(b);
        graph1[b].push_back(a);
    }
    graph2.resize(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        cnt2[a]++;
        cnt2[b]++;
        graph2[a].push_back(b);
        graph2[b].push_back(a);
    }
    bool sub3 = true;
    for (int i = 1; i <= n; i++)
    {
        if (cnt1[i] > 2 or cnt2[i] > 2)
        {
            sub3 = false;
            break;
        }
    }
    if (n <= 2000)
    {
        for (int i = 0; i < n; i++)
        {
            sub1.resize(n + 1);
            sub2.resize(n + 1);
            used1.resize(n + 1);
            used2.resize(n + 1);
            parent1.resize(n + 1);
            parent2.resize(n + 1);
            dfs1(i + 1);
            dfs2(i + 1);
            int ans = 0;
            for (int j = 1; j <= n; j++)
                ans += sub1[j] > sub2[j];
            sub1.clear();
            sub2.clear();
            used1.clear();
            used2.clear();
            cout << ans << ' ';
        }
    }
    else if (sub3)
    {
        int root1 = 1, root2 = 1;
        used1.resize(n + 1);
        used2.resize(n + 1);
        vector<int> line1, line2;
        for (int i = 1; i <= n; i++)
        {
            if (cnt1[i] == 1)
            {
                root1 = i;
                break;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (cnt2[i] == 1)
            {
                root2 = i;
                break;
            }
        }
        queue<int> q;
        q.push(root1);
        line1.push_back(root1 - 1);
        used1[root1] = 1;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();

            for (auto neighbour : graph1[x])
            {
                if (!used1[neighbour])
                {
                    q.push(neighbour);
                    used1[neighbour] = 1;
                    line1.push_back(neighbour - 1);
                }
            }
        }
        q.push(root2);
        line2.push_back(root2 - 1);
        used2[root2] = 1;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();

            for (auto neighbour : graph2[x])
            {
                if (!used2[neighbour])
                {
                    q.push(neighbour);
                    used2[neighbour] = 1;
                    line2.push_back(neighbour - 1);
                }
            }
        }
        vector<int> index(n), ans(n);
        for (int i = 0; i < n; i++)
            index[line1[i]] = i;
        SegTree s(n);
        for (int i = 0; i < n; i++)
        {
            if (index[line2[i]] > i)
                s.add(index[line2[i]] + 1, n);
            if (n - index[line2[i]] > i + 1)
                s.add(0, index[line2[i]]);
            ans[line2[i]] += s.sum(index[line2[i]]);
        }
        s.clear();
        for (int i = n - 1; i >= 0; i--)
        {
            if (index[line2[i]] + 1 > n - i)
                s.add(index[line2[i]] + 1, n);
            if (n - index[line2[i]] > n - i)
                s.add(0, index[line2[i]]);
            ans[line2[i]] += s.sum(index[line2[i]]);
        }
        print(ans)
    }
    else
    {
        if (n == 1)
        {
            cout << 0;
            return 0;
        }
        int root1 = 1, root2 = 1;
        for (int i = 0; i < n; i++)
        {
            if (graph1[i + 1].size() == 2)
            {
                root1 = i + 1;
                break;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (graph2[i + 1].size() == 2)
            {
                root2 = i + 1;
                break;
            }
        }
        sub1.resize(n + 1);
        sub2.resize(n + 1);
        used1.resize(n + 1);
        used2.resize(n + 1);
        parent1.resize(n + 1);
        parent2.resize(n + 1);
        news1.resize(n + 1);
        news2.resize(n + 1);
        dfs1(root1);
        dfs2(root2);
        vector<int> comp(n + 1);
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            comp[i] = (sub1[i] > sub2[i]);
            ans += comp[i];
        }
        for (int i = 1; i <= n; i++)
        {
            int curans = ans;
            dfs1(i, i);
            dfs2(i, i);
            for (int x : ps)
            {
                if (news1[x] == 0)
                    news1[x] = sub1[x];
                if (news2[x] == 0)
                    news2[x] = sub2[x];

                curans = curans - comp[x] + (news1[x] > news2[x]);

                news1[x] = 0;
                news2[x] = 0;
            }

            ps.clear();
            cout << curans << ' ';
        }
    }
}
