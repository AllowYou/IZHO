#include <bits/stdc++.h>
using namespace std;

#define fs first
#define ss second
#define endl '\n'
#define all(a) a.begin(), a.end()
#define print(a)      \
    for (auto &x : a) \
        cout << x << ' '; \
    cout << endl;

#define printmp(a)                           \
    for (auto &x : a)                        \
        cout << x.fs << ' ' << x.ss << endl; \
    cout << endl;

vector<int> a, b;
vector<pair<int, int>> ans;
map<vector<int>, bool> mp;

bool dfs(vector<int> &a){
    mp[a] = true;
    vector<int> c;
    for(int i = 0; i < a.size(); i ++){
        int cnt1 = 0, cnt2 = 0;
        c = a;
        for(int j = i + 1; j < a.size(); j ++){
            if(a[i] > a[j])
                cnt1 ++;
            else
                cnt2 ++;
            swap(c[j], c[j - 1]);
            if(cnt1 == cnt2){
                if(c == b){
                    ans.push_back({i + 1, j - i});
                    return true;
                }
                if(!mp[c] and dfs(c)){
                    ans.push_back({i + 1, (j - i)});
                    return true;
                }
            }
        }
    }
    for(int i = 0; i < a.size(); i ++){
        int cnt1 = 0, cnt2 = 0;
        c = a;
        for(int j = i - 1; j >= 0; j --){
            if(a[i] > a[j])
                cnt1 ++;
            else
                cnt2 ++;
            swap(c[j], c[j + 1]);
            if(cnt1 == cnt2){
                if(c == b){
                    ans.push_back({i + 1, j - i});
                    return true;
                }
                if(!mp[c] and dfs(c)){
                    ans.push_back({i + 1, j - i});
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    // Partial results: 16 points

    int n, t;
    cin >> n >> t;
    a.resize(n);
    b.resize(n);
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
                    printmp(ans)
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
                printmp(ans)
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
                    printmp(ans)
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
                printmp(ans)
            }
            return 0;
        }
        cout << "NO";
    }
    else
    {
        if(dfs(a))
            cout << "YES";
        else
            cout << "NO";
        cout << endl;
        if(t == 2){
            cout << ans.size() << endl;
            reverse(all(ans));
            printmp(ans)
        }
    }
}
