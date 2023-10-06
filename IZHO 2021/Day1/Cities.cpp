#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define all(a) a.begin(), a.end()
#define endl '\n'
#define print(a)          \
    for (auto &x : a)     \
        cout << x << ' '; \
    cout << endl;

struct Line
{
    mutable ll k, m, p;
    bool operator<(const Line &o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>>
{
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b)
    {
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y)
    {
        if (y == end())
            return x->p = inf, 0;
        if (x->k == y->k)
            x->p = x->m > y->m ? inf : -inf;
        else
            x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m)
    {
        k = -k;
        m = -m;
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z))
            z = erase(z);
        if (x != begin() && isect(--x, y))
            isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x)
    {
        assert(!empty());
        auto l = *lower_bound(x);
        return -(l.k * x + l.m);
    }
};

void solve()
{
    int n, s, t;
    cin >> n >> s >> t;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    if (s > t)
    {
        t = n - t + 1;
        s = n - s + 1;
        reverse(all(a));
    }
    s--;
    t--;
    LineContainer c1, c2;
    c1.add(-a[s], s * a[s]);
    c2.add(a[s], -s * a[s]);
    int l = s, r = s;
    while (true)
    {
        if (r == t)
        {
            cout << c2.query(r);
            return;
        }
        int x = c1.query(l - 1), y = c2.query(r + 1);
        if (l != 0 and x < y){
            c1.add(-a[l - 1], x + (l - 1) * a[l - 1]);
            c2.add(a[l - 1], x - (l - 1) * a[l - 1]);
            l --;
        }
        else{
            c1.add(-a[r + 1], y + (r + 1) * a[r + 1]);
            c2.add(a[r + 1], y - (r + 1) * a[r + 1]);
            r++;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // Perfect result: 100 points
    
    solve();
}
