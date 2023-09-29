#pragma GCC optimize("unroll-loops")
#pragma gcc optimize("Ofast")
#pragma GCC optimization("Ofast")
#pragma optimize(Ofast)
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define str string
#define fastio ios::sync_with_stdio(0), cin.tie(0);
#define fs first
#define ss second
#define endl '\n'
#define all(x) (x).begin(), (x).end()
#define len(x) x.size()

#define print(a)          \
    for (auto &x : a)     \
        cout << x << " "; \
    cout << endl;

#define printmp(a)    \
    for (auto &x : a) \
        cout << x.fs << " " << x.ss << endl;

const int mod = 1e9 + 7;

vector<vector<int>> dp;
ll n, x, y;

ll rec(int l, int r, int j)
{
    if (j >= dp[0].size() or dp[l][j] > r)
        return x;
    return y + rec(l, r, j + 1) + rec(l + (1 << j), r, j + 1);
}

int f(int n)
{
    int ans = 0;
    while (n)
    {
        n >>= 1;
        ans++;
    }
    return ans;
}

void solve()
{
    bool sub4 = true;
    cin >> n >> x >> y;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i], sub4 &= (a[i] <= 2);
    if (sub4)
    {
        int m = 0, k = n - 1;
        while (k)
        {
            m++;
            k >>= 1;
        }
        vector<vector<ll>> p(m, vector<ll>(n + 1));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (i + (1 << j) < n)
                    p[j][i + 1] = (a[i] == a[i + (1 << j)]);
        for (int i = 0; i < m; i++)
            for (int j = 1; j <= n; j++)
                p[i][j] += p[i][j - 1];
        int q;
        cin >> q;
        while (q--)
        {
            int l, r;
            cin >> l >> r;
            int m = 0, s = (r - l + 1);
            while (s)
            {
                s >>= 1;
                m++;
            }
            m -= 1;
            s = (r - l + 1);
            bool flag = false;
            ll ans = y * min(s - 1ll * (1 << (m - 1)) - 1, 1ll * (1 << m) - 1);
            for (int i = 0; i < 2; i++)
            {
                if (r <= l)
                    break;
                int mid = r - (1 << m);
                if (mid + 1 >= l)
                {
                    ans += (y + 2 * x) * (p[m][mid] - p[m][l - 1]) + x * (mid - l + 1 - p[m][mid] + p[m][l - 1]);
                    int t = mid - l + 1;
                    l += t;
                    r -= t;
                    m--;
                }
                else
                {
                    break;
                }
            }
            ans += max(0ll, (r - l + 1) * x);
            cout << ans << endl;
        }
        return;
    }
    dp.resize(n, vector<int>(f(n), 2 * n));
    for (int j = 0; j < dp[0].size(); j++)
    {
        int i = 0;
        while (n - i - 1 >= 0 and dp[n - i - 1][j] == 2 * n)
        {
            vector<int> cnt(n + 1, -1);
            for (int x = n - i - 1; x >= 0; x -= (1 << j))
            {
                dp[x][j] = 3 * n;
                if (cnt[a[x]] != -1)
                    dp[x][j] = cnt[a[x]];
                if (x + (1 << j) < n)
                    dp[x][j] = min(dp[x + (1 << j)][j], dp[x][j]);
                cnt[a[x]] = x;
            }
            i++;
        }
    }
    int q;
    cin >> q;
    while (q--)
    {
        int l, r, ans = 0;
        cin >> l >> r;
        cout << rec(l - 1, r - 1, 0) << endl;
    }
}

signed main()
{
    fastio

    // Partial result: 61 points
    // I could solve 1, 2, 3, 4, 5 - th subtasks

    int tests = 1;
    while (tests --)
    {
        solve();
        cout << endl;
    }
}
