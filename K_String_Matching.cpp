#include <bits/stdc++.h>
using namespace std;
const int mod1 = 764285933, mod2 = 147043433;
const int base1 = 2, base2 = 3;
const int N = 1e6;
int pw1[N + 5], pw2[N + 5], prefix_hash1[N + 5], prefix_hash2[N + 5];
int inv1[N + 5], inv2[N + 5];
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
int inv(int x, int mod)
{
    return pw(x, mod - 2, mod);
}

void precalc()
{
    pw1[0] = 1;
    for (int i = 1; i <= N; i++)
        pw1[i] = 1LL * pw1[i - 1] * base1 % mod1;
    pw2[0] = 1;
    for (int i = 1; i <= N; i++)
        pw2[i] = 1LL * pw2[i - 1] * base2 % mod2;
    inv1[0] = 1;
    inv1[1] = inv(base1, mod1);
    for (int i = 2; i <= N; i++)
        inv1[i] = 1LL * inv1[i - 1] * inv1[1] % mod1;
    inv2[0] = 1;
    inv2[1] = inv(base2, mod2);
    for (int i = 2; i <= N; i++)
        inv2[i] = 1LL * inv2[i - 1] * inv2[1] % mod2;
}
void calc_hash(string &s)
{
    prefix_hash1[0] = 0;
    for (int i = 1; i < (int)s.size(); i++)
        prefix_hash1[i] = (prefix_hash1[i - 1] + 1LL * pw1[i] * (s[i] - 'a' + 1)) % mod1;
    prefix_hash2[0] = 0;
    for (int i = 1; i < (int)s.size(); i++)
        prefix_hash2[i] = (prefix_hash2[i - 1] + 1LL * pw2[i] * (s[i] - 'a' + 1)) % mod2;
}
array<int, 2> total_hash(string &s)
{
    int hash1 = 0, hash2 = 0;
    for (int i = 1; i < (int)s.size(); ++i)
        hash1 = (hash1 + 1LL * pw1[i] * (s[i] - 'a' + 1)) % mod1;
    for (int i = 1; i < (int)s.size(); ++i)
        hash2 = (hash2 + 1LL * pw2[i] * (s[i] - 'a' + 1)) % mod2;
    return {hash1, hash2};
}
array<int, 2> range_hash(int l, int r)
{
    int hash1 = (prefix_hash1[r] - prefix_hash1[l - 1] + mod1) % mod1;
    int hash2 = (prefix_hash2[r] - prefix_hash2[l - 1] + mod2) % mod2;
    
    hash1 = 1LL * hash1 * inv1[l - 1] % mod1;
    hash2 = 1LL * hash2 * inv2[l - 1] % mod2;
    return {hash1, hash2};
}
void solve()
{
    string s, s1;
    cin >> s >> s1;
    s = '$' + s;
    s1 = '#' + s1;
    calc_hash(s);
    auto need = total_hash(s1);
    int len = s1.size() - 1;
    int ans(0);
    for (int i(1); i + len <= (int)s.size(); ++i)
    {
        auto ache=range_hash(i, i + len - 1);
        ans += ache == need;
       // cout<<ache[0]<<" "<<ache[1]<<endl;
    }
    cout << ans << endl;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    precalc();
    solve();
}