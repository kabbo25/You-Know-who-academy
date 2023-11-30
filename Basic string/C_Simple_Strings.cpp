#include <bits/stdc++.h>
using namespace std;
/*
    using prev and next character
*/
void solve()
{
    string s;
    cin >> s;
    auto next_char = [&](int ord)
    {
        ord = (ord + 1) % 26;
        return char('a' + ord);
    };
    auto prev_char = [&](int ord)
    {
        ord = (ord - 1 + 26) % 26;
        return char('a' + ord);
    };
    auto ord = [&](char ch)
    {
        return ch - 'a';
    };
    for (int i(1); i < (int)s.size(); ++i)
    {
        if (s[i] == s[i - 1])
        {
            if (i == (int)s.size() - 1)
            {
                s[i] = next_char(ord(s[i]));
            }
            if (next_char(ord(s[i])) != s[i + 1])
            {
                s[i] = next_char(ord(s[i]));
            }
            else
                s[i] = prev_char(ord(s[i]));
        }
    }
    cout << s<<endl;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}