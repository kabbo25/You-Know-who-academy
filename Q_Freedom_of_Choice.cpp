#include <bits/stdc++.h>
using namespace std;
const int mod1 = 764285933, mod2 = 147043433;
const int base1 = 31, base2 = 37;
class Hash
{
public:
    string s;
    int n;
    vector<int> pw1, pw2, inv1, inv2, prefix_hash1, prefix_hash2;
    Hash(string _s)
    {
        s = _s;
        n = s.size();
        pw1.resize(n + 1);
        pw2.resize(n + 1);
        inv1.resize(n + 1);
        inv2.resize(n + 1);
        prefix_hash1.resize(n + 1);
        prefix_hash2.resize(n + 1);
    }
    int pw(int a, int b, int mod)
    {
        int64_t res = 1;
        while (b)
        {
            if (b & 1)
                res = 1LL * res * a % mod;
            a = 1LL * a * a % mod;
            b >>= 1;
        }
        return res;
    }
    int inv(int x, int mod) { return pw(x, mod - 2, mod); }

    void build()
    {

        pw1[0] = 1;
        for (int i = 1; i <= n; i++)
            pw1[i] = 1LL * pw1[i - 1] * base1 % mod1;
        pw2[0] = 1;
        for (int i = 1; i <= n; i++)
            pw2[i] = 1LL * pw2[i - 1] * base2 % mod2;
        inv1[0] = 1;
        inv1[1] = inv(base1, mod1);
        for (int i = 2; i <= n; i++)
            inv1[i] = 1LL * inv1[i - 1] * inv1[1] % mod1;
        inv2[0] = 1;
        inv2[1] = inv(base2, mod2);
        for (int i = 2; i <= n; i++)
            inv2[i] = 1LL * inv2[i - 1] * inv2[1] % mod2;
        prefix_hash1[0] = 0;
        for (int i = 1; i < (int)s.size(); i++)
            prefix_hash1[i] =
                (prefix_hash1[i - 1] + 1LL * pw1[i] * (s[i] - 'a' + 1)) % mod1;
        prefix_hash2[0] = 0;
        for (int i = 1; i < (int)s.size(); i++)
            prefix_hash2[i] =
                (prefix_hash2[i - 1] + 1LL * pw2[i] * (s[i] - 'a' + 1)) % mod2;
    }
    array<int, 2> range_hash(int l, int r)
    {
        int hash1 = (prefix_hash1[r] - prefix_hash1[l - 1] + mod1) % mod1;
        int hash2 = (prefix_hash2[r] - prefix_hash2[l - 1] + mod2) % mod2;

        hash1 = 1LL * hash1 * inv1[l - 1] % mod1;
        hash2 = 1LL * hash2 * inv2[l - 1] % mod2;
        return {hash1, hash2};
    }
};
void solve()
{
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;
    s1 = '#' + s1, s2 = '#' + s2;
    Hash h1(s1), h2(s2);
    h1.build();
    h2.build();
    int l(0), r(n + 1);
    string res;
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        set<array<int, 2>> st;
        for (int i = 1; i <= n - mid + 1; i++)
        {
            //
            st.insert(h1.range_hash(i, i + mid - 1));
        }
        bool ok = false;
        for (int i = 1; i <= n - mid + 1; i++)
        {

            if (st.count(h2.range_hash(i, i + mid - 1)))
            {

                res = s2.substr(i, mid);
                ok = true;
                break;
            }
        }
        if (ok)
            l = mid;
        else
            r = mid;
    }
    cout << res << endl;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}