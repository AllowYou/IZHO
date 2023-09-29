#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // Partial results: 9 points

    int n, q;
    cin >> n >> q;
    vector<int> p(n);
    for (int i = 0; i < n; i++)
        cin >> p[i];
    vector<vector<int>> graph(n + 1);
    bool sub2 = true, sub3 = true;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        sub2 &= (a == i + 1 and b == i + 2);
        sub3 &= (a == 1 and b == i + 2);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    if (sub2)
    {
        vector<int> index(n + 1);
        for (int i = 0; i < n; i++)
            index[p[i]] = i + 1;
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            int mn = 1e9, mx = 0;
            for (int j = i; j < n; j++)
            {
                mx = max(mx, index[j + 1]);
                mn = min(mn, index[j + 1]);
                // cout << i << ' ' << j << ' ' <<
                ans += mx - mn + 1;
            }
        }
        cout << ans;
    }
}
