#include <bits/stdc++.h>
using namespace std;

int n;
#define fs first
#define ss second
#define endl '\n'
#define print(a)          \
    for (auto x : a)      \
        cout << x << ' '; \
    cout << endl;

vector<int> v;
int a, b, s;
vector<pair<int, int>> ans;

void rec(int node, int m)
{
    ans.push_back({0, 0});
    if (a >= (1 << (m - 1)))
    {
        if (ans[node].fs == 0)
            ans[node].fs = 1, a -= (1 << (m - 1));
        else if (ans[node].ss == 0)
            ans[node].ss = 1, a -= (1 << (m - 1));
    }
    if (b >= (1 << (m - 1)))
    {
        if (ans[node].fs == 0)
            ans[node].fs = 2, b -= (1 << (m - 1));
        else if (ans[node].ss == 0)
            ans[node].ss = 2, b -= (1 << (m - 1));
    }
    if (s >= (1 << (m - 1)))
    {
        if (ans[node].fs == 0)
            ans[node].fs = 3, s -= (1 << (m - 1));
        else if (ans[node].ss == 0)
            ans[node].ss = 3, s -= (1 << (m - 1));
    }
    if (ans[node].fs == 0)
        ans[node].fs = node + 1, ans[node].ss = node + 2, rec(node + 1, m - 1), rec(node + 2, m - 1);
    else if (ans[node].ss == 0)
        ans[node].ss = node + 1, rec(node + 1, m - 1);
}

void solve()
{
    cin >> a >> b;
    if (a == b)
    {
        cout << 3 << ' ' << 3 << endl;
        cout << 1 << ' ' << 2 << endl;
        return;
    }
    else
    {
        int m = 0, k = a + b;
        while (k)
            m++, k >>= 1;
        s = (1 << m) - a - b;
        v.resize(m);
        for (int i = 0; i < 3; i++)
            ans.push_back({0, 0});
        rec(3, m);
        cout << ans.size() - 1 << ' ' << 3 << endl;
        for (int i = 3; i < ans.size(); i++)
            cout << ans[i].fs << ' ' << ans[i].ss << endl;
        ans.clear();
        v.clear();
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // Partial results: 50 points

    int t;
    cin >> t >> n;
    while (t--)
    {
        solve();
    }
}
