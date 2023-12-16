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
    s = '#' + s + s;
    Hash hs1(s);
    hs1.build();
    auto lex = [&](auto i, auto j)
    {
        int l(0), r(n + 1);
        while (r - l > 1)
        {
            int mid = (l + r) / 2;
            auto first = hs1.range_hash(i, i + mid - 1);
            auto second = hs1.range_hash(j, j + mid - 1);
            if (first == second)
                l = mid;
            else
                r = mid;
        }
        auto ch = s[i + l], ch1 = s[j + l];
        return ch < ch1 ? i : j;
    };
    int st = 1;
    for (int i(2); i <= n; ++i)
    {
        st = lex(st, i);
    }
    cout << s.substr(st, n) << endl;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t(1);
    while (t--)
        solve();
}