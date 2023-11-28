#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    stack<char> st;
    int cnt(0);
    for (auto &x : s)
    {
        if (st.empty() or st.top() != x)
        {
            st.emplace(x);
        }
        else
        {
            cnt++;
            st.pop();
        }
    }
    cout << (cnt & 1 ? "Yes" : "No") << endl;
}