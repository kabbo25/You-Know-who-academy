#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <cassert>
#include <functional>
#include <iterator>
using namespace std;
const int mod1 = 764285933, mod2 = 147043433;
const int base1 = 211, base2 = 389;
template <class Fun>
class y_combinator_result
{
    Fun fun_;

public:
    template <class T>
    explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

    template <class... Args>
    decltype(auto) operator()(Args &&...args)
    {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun)
{
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
// const int mod = 1e9 + 7;
using u64 = uint64_t;
using u128 = __uint128_t;
#define sc1(x) scanf("%lld", &(x));
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifndef NEAL_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
/*Well, probably you won't understand anything,
because you didn't try to understand anything in your life,
you expect all hard work to be done for you by someone else.
Let's start*/
// step 1: write a binary search function that find lexiographical
template <typename T, size_t N>
std::ostream &operator<<(std::ostream &os, const std::array<T, N> &arr)
{
    os << "[";
    for (size_t i = 0; i < arr.size(); ++i)
    {
        os << arr[i];
        if (i != arr.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
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
        assert(l <= r);
        int hash1 = (prefix_hash1[r] - prefix_hash1[l - 1] + mod1) % mod1;
        int hash2 = (prefix_hash2[r] - prefix_hash2[l - 1] + mod2) % mod2;

        hash1 = 1LL * hash1 * inv1[l - 1] % mod1;
        hash2 = 1LL * hash2 * inv2[l - 1] % mod2;
        return {hash1, hash2};
    }
};
void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    auto rev = s;
    reverse(rev.begin(), rev.end());
    s = '#' + s, rev = '#' + rev;
    Hash hs1(s), hs2(rev);
    // dbg(rev);
    hs1.build(), hs2.build();
    auto pal_sub = [&](int i, int j)
    {
        auto first = hs1.range_hash(i, j);
        auto second = hs2.range_hash(n - j + 1, n - i + 1);
        return first == second;
    };
    if (pal_sub(1, n))
    {
        cout << s.substr(1, n) << endl;
        return;
    }
    int len(1);
    vector cnt(26, vector(0, 0));
    auto ord = [&](char x)
    { return x - 'a'; };
    for (int i(1); i <= n; ++i)
    {
        cnt[ord(s[i])].emplace_back(i);
    }
    int st = -1;
    char last = '?';
    auto chk = [&](int x, int i) -> array<int, 2>
    {
        int temp(0);
        auto it = upper_bound(cnt[ord(s[i])].begin(), cnt[ord(s[i])].end(), x);
        if (it == cnt[ord(s[i])].begin())
            return {temp, -1};
        it--;
        if (pal_sub(*it, i))
            temp = (i - *it + 1);
        return {temp, *it};
    };
    for (int i(2); i <= n; ++i)
    {
        auto need = i - len - 1;
        auto need1 = i - len;
        auto it = upper_bound(cnt[ord(s[i])].begin(), cnt[ord(s[i])].end(), need);
        auto ans = chk(need, i);
        auto ans1 = chk(need1, i);
        if (len < ans[0])
        {
            len = ans[0];
            st = ans[1];
        }
        if (len < ans1[0])
        {
            len = ans1[0];
            st = ans1[1];
        }
    }
    if (st == -1)
    {
        cout << s[1] << endl;
    }
    else
        cout << s.substr(st, len) << endl;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t(1);
    while (t--)
        solve();
}