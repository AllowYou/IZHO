#include <bits/stdc++.h>
using namespace std;

#define int long long
#define all(a) a.begin(), a.end()
#define endl '\n'
#define print(a)          \
    for (auto &x : a)     \
        cout << x << ' '; \
    cout << endl;

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    // Partial result: 40 points
    // I could solve 1, 2, 3, 4 subtasks

    int n, s, t;
    cin >> n >> s >> t;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    if (s == t)
    {
        cout << 0;
        return 0;
    }
    if (s > t)
    {
        t = n - t + 1;
        s = n - s + 1;
        reverse(all(a));
    }
    vector<int> index, p, cost, def;
    int s1 = 1, s2 = 1, s3 = 1;
    t--;
    s--;
    p.push_back(a[s]);
    index.push_back(s);
    cost.push_back(0);
    def.push_back(0);
    int x = 0;
    for (int i = s + 1; i <= t; i++)
    {
        cost[s1 - 1] += p[s2 - 1];
        x += p[s2 - 1];
        if (i < t and p[s2 - 1] > a[i])
            p.push_back(a[i]), cost.push_back(0), index.push_back(i), def.push_back(x + (i - s) * a[i]), s1++, s2++, s3++;
    }
    int sum = 0;
    for (int i = s1 - 1; i >= 0; i--)
    {
        sum += cost[i];
        cost[i] = sum;
    }
    int ans = sum, u = 0, mn = 0;
    x = a[s];
    for (int i = s - 1; i >= 0; i--)
    {
        u += x;
        x = min(x, a[i]);
        if (p[s2 - 1] > x)
        {
            ans = min(ans, u + x * (t - i));
            continue;
        }
        int l = 0, r = s2 - 1;
        while (l < r)
        {
            int m = (l + r + 1) >> 1;
            if (p[m] >= x)
                l = m;
            else
                r = m - 1;
        }
        ans = min(ans, u + x * (index[l + 1] - i) + cost[l + 1]);
    }
    reverse(all(cost));
    reverse(all(p));
    reverse(all(index));
    reverse(all(def));
    x = a[s];
    for (int i = s - 1; i >= 0; i--)
    {
        mn += x;
        x = min(x, a[i]);
        while (def.size() >= 2 and def[def.size() - 2] + (s - i) * p[p.size() - 2] <= mn)
        {
            def.pop_back();
            p.pop_back();
            cost.pop_back();
            index.pop_back();
            mn = def[def.size() - 1] + (s - i) * p[p.size() - 1];
        }
        while (def.size() >= 2 and p[p.size() - 1] > a[i] and p[p.size() - 2] >= a[i])
        {
            p[p.size() - 2] = p[p.size() - 1];
            def[p.size() - 2] = def[p.size() - 1];
            cost[p.size() - 2] += cost[p.size() - 1];
            index[p.size() - 2] = index[p.size() - 1];
            def.pop_back();
            p.pop_back();
            cost.pop_back();
            index.pop_back();
        }
        if (p[0] > x)
        {
            ans = min(ans, mn + x * (t - i));
            continue;
        }
        int l = 0, r = p.size() - 1;
        while (l < r)
        {
            int m = (l + r) >> 1;
            if (p[m] < x)
                l = m + 1;
            else
                r = m;
        }
        ans = min(ans, mn + x * (index[l] - i) + cost[l]);
    }
    cout << ans;
}