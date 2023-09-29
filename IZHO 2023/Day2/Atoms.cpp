#include <bits/stdc++.h>
using namespace std;

#define fs first
#define ss second
#define int long long

#define print(x)          \
    for (auto a : x)      \
        cout << a << ' '; \
    cout << endl;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // Partial results: 39 points

    int n;
    cin >> n;
    vector<int> b(n), k(n);
    vector<pair<int, int>> d(n), c(n);
    bool sub2 = true, sub3 = true, sub4 = true;
    for (int i = 0; i < n; i++)
        cin >> b[i];
    for (int i = 0; i < n; i++)
        cin >> k[i];
    for (int i = 0; i < n; i++)
        cin >> d[i].fs, sub2 &= (d[i].fs == d[0].fs);
    for (int i = 0; i < n; i++)
        cin >> d[i].ss, sub4 &= (d[i].ss == 1);
    sort(b.begin(), b.end());
    sort(k.begin(), k.end());
    sort(d.begin(), d.end());
    for (int i = 0; i < n; i++)
        c[i].fs = d[i].ss, c[i].ss = d[i].fs;
    sort(c.begin(), c.end());
    if (!(k[0] >= b[n - 1] and k[0] >= d[n - 1].fs))
        sub3 = false;
    if (n <= 3)
    {
        int ans = 0;
        do
        {
            do
            {
                do
                {
                    int s = 0;
                    for (int i = 0; i < n; i++)
                    {
                        if (b[i] <= d[i].fs and d[i].fs <= k[i])
                        {
                            s += d[i].ss;
                        }
                    }
                    ans = max(ans, s);
                } while (next_permutation(k.begin(), k.end()));
            } while (next_permutation(d.begin(), d.end()));
        } while (next_permutation(b.begin(), b.end()));
        cout << ans;
    }
    else if (sub2)
    {
        int mn1 = 0, mn2 = 0;
        for (int i = 0; i < n; i++)
            mn1 += b[i] <= d[i].fs, mn2 += d[i].fs <= k[i];
        int s = 0;
        for (int i = 0; i < min(mn1, mn2); i++)
            s += c[n - i - 1].fs;
        cout << s;
    }
    else if (sub3)
    {
        int ans = 0;
        multiset<int> mb;
        for (int i = 0; i < n; i++)
        {
            mb.insert(b[i]);
        }
        for (int i = 0; i < n; i++)
        {
            if (*mb.begin() <= c[n - i - 1].ss)
            {
                ans += c[n - i - 1].fs;
                auto x = mb.upper_bound(c[n - i - 1].ss);
                x--;
                mb.erase(x);
            }
        }
        cout << ans;
    }
    else if (sub4)
    {
        int x = 0, y = 0, z = 0, s = 0;
        while (x < n and y < n and z < n)
        {
            if (b[x] <= d[y].fs and d[y].fs <= k[z])
            {
                x++;
                y++;
                z++;
                s++;
            }
            else if (b[x] <= d[y].fs)
            {
                z++;
            }
            else
            {
                y++;
            }
        }
        cout << s << endl;
    }
    else
    {
        int ans = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            int mx = 0, index = -1;
            for (int j = 0; j < n; j++)
            {
                if (b[j] != -1)
                {
                    if (b[j] <= c[i].ss and mx <= b[j])
                    {
                        mx = b[j];
                        index = j;
                    }
                }
            }
            if (index == -1)
            {
                continue;
            }
            int mn = LLONG_MAX, index1 = -1;
            for (int j = 0; j < n; j++)
            {
                if (k[j] != -1)
                {
                    if (c[i].ss <= k[j] and mn >= k[j])
                    {
                        mn = k[j];
                        index1 = j;
                    }
                }
            }
            if (index == -1)
            {
                continue;
            }
            b[index] = -1;
            k[index1] = -1;
            ans += c[i].fs;
        }
        cout << ans;
    }
}
