#include <bits/stdc++.h>
using namespace std;

#define fs first
#define ss second
#define endl '\n'
#define print(a)      \
    for (auto &x : a) \
        cout << x.fs << ' ' << x.ss << endl;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    // Partial results: 9 points

    int n, t;
    cin >> n >> t;
    vector<int> a(n), b(n);
    bool flag = false;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    if (n == 1)
    {
        cout << "YES" << endl;
        if (t == 2)
            cout << 0 << endl;
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        if (i < n - 1 and a[i] == i + 2 and a[i + 1] == i + 1)
        {
            flag = true;
            for (int j = i + 2; j < n; j++)
                if (a[j] != j + 1)
                {
                    flag = false;
                    break;
                }
            break;
        }
        else if (a[i] == i + 1)
            continue;
        else
        {
            flag = false;
            break;
        }
    }
    if (flag)
    {
        int k = 1;
        for (int i = 0; i < n; i++)
            if (a[i] == i + 2)
                k = i;
        vector<pair<int, int>> ans;
        vector<int> c = a;
        for (int i = k + 1; i >= 2; i--)
        {
            if (a == b)
            {
                cout << "YES" << endl;
                if (t == 2)
                {
                    cout << ans.size() << endl;
                    print(ans)
                }
                return 0;
            }
            ans.push_back({i + 1, -2});
            swap(a[i], a[i - 2]);
            swap(a[i], a[i - 1]);
        }
        if (a == b)
        {
            cout << "YES" << endl;
            if (t == 2)
            {
                cout << ans.size() << endl;
                print(ans)
            }
            return 0;
        }
        a = c;
        ans.clear();
        for (int i = k; i < n - 2; i++)
        {
            if (a == b)
            {
                cout << "YES" << endl;
                if (t == 2)
                {
                    cout << ans.size() << endl;
                    print(ans)
                }
                return 0;
            }
            ans.push_back({i + 1, 2});
            swap(a[i], a[i + 2]);
            swap(a[i], a[i + 1]);
        }
        if (a == b)
        {
            cout << "YES" << endl;
            if (t == 2)
            {
                cout << ans.size() << endl;
                print(ans)
            }
            return 0;
        }
        cout << "NO";
    }
    else
    {
        if (a == b)
        {
            cout << "YES" << endl;
            if (t == 2)
            {
                cout << 0 << endl;
            }
            return 0;
        }
        cout << "NO";
    }
}
