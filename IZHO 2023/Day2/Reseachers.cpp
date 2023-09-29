#include <bits/stdc++.h>
using namespace std;

#define fs first
#define ss second
#define endl '\n'

#define print(x)          \
    for (auto a : x)      \
        cout << a << ' '; \
    cout << endl;

struct node
{
    int a, l, r;
};

struct SegmentTree
{
    int size = 1;
    vector<int> mn, mx;
    SegmentTree(vector<int> &l, vector<int> &r)
    {
        while (size < l.size())
            size <<= 1;
        mn.resize(size << 1, 2e9);
        mx.resize(size << 1, 0);
        build(l, r, 0, 0, size);
    }

    void build(vector<int> &l, vector<int> &r, int x, int lx, int rx)
    {
        if (rx == lx + 1)
        {
            if (lx < l.size())
            {
                mn[x] = r[lx];
                mx[x] = l[lx];
            }
            else
            {
                mn[x] = 2e9;
                mx[x] = 0;
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(l, r, (x << 1) + 1, lx, m);
        build(l, r, (x << 1) + 2, m, rx);
        mn[x] = min(mn[(x << 1) + 1], mn[(x << 1) + 2]);
        mx[x] = max(mx[(x << 1) + 1], mx[(x << 1) + 2]);
    }

    int mins(int l, int r, int x, int lx, int rx)
    {
        if (l <= lx and rx <= r)
            return mn[x];
        if (rx <= l or r <= lx)
            return 2e9;
        int m = (lx + rx) >> 1;
        return min(mins(l, r, (x << 1) + 1, lx, m), mins(l, r, (x << 1) + 2, m, rx));
    }

    int mins(int l, int r)
    {
        return mins(l, r, 0, 0, size);
    }

    int maxs(int l, int r, int x, int lx, int rx)
    {
        if (l <= lx and rx <= r)
        {
            return mx[x];
        }
        if (rx <= l or r <= lx)
            return 0;
        int m = (lx + rx) >> 1;
        return max(maxs(l, r, (x << 1) + 1, lx, m), maxs(l, r, (x << 1) + 2, m, rx));
    }

    int maxs(int l, int r)
    {
        return maxs(l, r, 0, 0, size);
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // Partial results: 17 points
    
    int n, m;
    cin >> n >> m;
    vector<vector<node>> graph(n + 1);
    vector<int> l, r;
    bool flag3 = (n == m + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        l.push_back(c);
        r.push_back(d);
        flag3 &= (a == i + 1 and b == i + 2);
        graph[a].push_back({b, c, d});
        graph[b].push_back({a, c, d});
    }
    int q;
    cin >> q;
    if (flag3)
    {
        int ans = 0;
        SegmentTree s(l, r);
        while (q--)
        {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            if (b < a)
                swap(a, b);
            cout << max(0, min(d, s.mins(a - 1, b - 1)) - max(c, s.maxs(a - 1, b - 1)) + 1) << endl;
        }
        return 0;
    }
    for (int i = 0; i < q; i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int ans = 0;
        for (int i = c; i <= d; i++)
        {
            queue<int> q;
            q.push(a);
            vector<bool> used(n + 1);
            used[a] = true;
            while (!q.empty())
            {
                int x = q.front();
                q.pop();

                for (auto x : graph[x])
                {
                    if (!used[x.a] and x.l <= i and i <= x.r)
                    {
                        q.push(x.a);
                        used[x.a] = true;
                    }
                }
            }
            ans += used[b];
        }
        cout << ans << endl;
    }
}
