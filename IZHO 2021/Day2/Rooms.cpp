#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define print(a)          \
    for (auto x : a)      \
        cout << x << ' '; \
    cout << endl;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // Partial results: 40 points

    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    bool sub3 = true, sub4 = true;
    for (int i = 0; i < n; i++)
        cin >> a[i], sub3 &= (a[i] == 0);
    for (int i = 0; i <= n; i++)
        cin >> b[i], sub4 &= (i == 0 ? 1 : (b[i - 1] <= b[i]));
    if (n <= 5000)
    {
        for (int i = 0; i < n; i++)
        {
            int l = i, r = i + 1, p = 0, exp = a[i];
            while (l >= 0 and r <= n)
            {
                if (b[l] <= exp)
                {
                    l--;
                    exp += a[l];
                }
                else if (b[r] <= exp)
                {
                    r++;
                    if (r <= n)
                        exp += a[r - 1];
                }
                else
                {
                    if (b[l] >= b[r])
                    {
                        p += b[r] - exp;
                        exp += b[r] - exp;
                        r++;
                        if (r <= n)
                            exp += a[r - 1];
                    }
                    else
                    {
                        p += b[l] - exp;
                        exp += b[l] - exp;
                        l--;
                        exp += a[l];
                    }
                }
            }
            cout << p << ' ';
        }
    }
    else if (sub3)
    {
        vector<int> ans(n);
        for (int i = 0; i < n; i++)
            ans[i] = max((i == 0 ? 0 : ans[i - 1]), b[i]);
        for (int i = n - 1; i >= 0; i--)
            ans[i] = min(ans[i], max(i == n - 1 ? 0 : ans[i + 1], b[i + 1]));
        print(ans)
    }
    else if (sub4)
    {
        for (int i = 0; i < n; i++)
        {
            cout << max(0, b[i] - a[i]) << ' ';
        }
    }
}
