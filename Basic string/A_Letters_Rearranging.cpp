#include <bits/stdc++.h>
using namespace std;
constexpr bool is_palindrome(const std::string_view &s)
{
    return std::equal(s.cbegin(), s.cbegin() + s.size() / 2, s.crbegin());
}
void solve()
{
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    cout << (is_palindrome(s) ? "-1" : s) << endl;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int i(0); i < t; ++i)
        solve();
}