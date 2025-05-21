#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using o_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define int int64_t
#define endl '\n'
#define F first
#define S second
#define pii pair<int, int>
#define sz(x) (int) x.size()
using namespace std;
const int mod = 998244353;
const int N = 2e5 + 10;
const int INF = 1e18 + 10;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int l, r, k, cc, pw[62];
pii dp[62][1024][2];
string s;

pii magic(int ind, int mask, int less) { // {cnt, sm}
    if(ind == -1) return {__builtin_popcountll(mask) <= k, 0};
    auto &[a, b] = dp[ind][mask][less];
    if(~a) return {a, b};
    a = b = 0;
    int mx = less ? 9 : s[ind] - '0';
    
    for(int d = 0; d <= mx; d++) {
        auto [cnt, sm] = magic(ind - 1, !mask && !d ? mask : mask | (1LL << d), less | (d < mx));
        (a += cnt) %= mod;
        (b += sm) %= mod;
        (b += (d * pw[ind] % mod) * cnt % mod) %= mod;
    }
    return {a, b};
}

int get(int n) {
    s = to_string(n);
    reverse(s.begin(), s.end());
    for(int i = 0; i < 62; i++) for(int j = 0; j < 1024; j++) dp[i][j][0] = dp[i][j][1] = {-1, -1};
    return magic(sz(s) - 1, 0, 0).S;
}

void solve() {
    cin>>l>>r>>k;

    int ans = (get(r) - get(l - 1) + mod) % mod;
    cout<<ans<<endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    pw[0] = 1;
    for(int i = 1; i < 62; i++) pw[i] = (pw[i - 1] * 10) % mod;

    int t = 1; //cin>>t;
    for(int tc = 1; tc <= t; tc++) {
        // cerr<<"Case "<<tc<<": \n";
        solve();
    }
}