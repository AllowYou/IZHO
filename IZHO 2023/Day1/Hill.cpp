#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define print(a)          \
    for (auto x : a)      \
        cout << x << ' '; \
    cout << endl;

int main()
{
    int n, m;
    cin >> n >> m;

    // Partial results: 66 points

    vector<vector<char>> v(n, vector<char>(m));
    bool flag2 = true;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> v[i][j];
            if (v[i][j] == 'X')
            {
                flag2 = false;
            }
        }
    }
    if (flag2)
    {
        int s = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                s += v[i][j] - '0';
            }
        }
        cout << s;
        return 0;
    }
    int ans = 0;
    vector<vector<int>> maxs(m, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int l = 0; l < m; l++)
        {
            int s = 0, u = l;
            for (int j = l; j < m; j++)
            {
                if (v[i][j] == 'X')
                {
                    s = 0, u = j + 1;
                    maxs[l][j] = 0;
                    if (j > 0)
                        maxs[l][j] = maxs[l][j - 1];
                }
                else
                {
                    s += v[i][j] - '0';
                    maxs[l][j] = s + maxs[u][j];
                    if (j != l)
                        maxs[l][j] = max(maxs[l][j - 1], maxs[l][j]);
                }
                ans = max(ans, maxs[l][j]);
            }
        }
    }
    cout << ans;
}
