#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;
const int N = 2505;
ll n, cnt, Q[N], val[N * 2], *b[N * 2], exist[N * 2];
ll res, high[N * 2], h2[N * 2];

struct Data{
    ll xa, xb, ya, yb;
} a[N];

struct Data2{
    ll x, ya, yb, w;
    bool operator < (Data2 &p) {
        return x < p.x;
    }
} d[N];
vector<Data> Color[105];

void Enter() {
    scanf("%lld", &n);
    ll xa, ya, xb, yb, c;
    for(int i=1; i<=n; ++i) {
        scanf("%lld%lld%lld%lld%lld", &xa, &ya, &xb, &yb, &c);
        Color[c].push_back({xa, xb, ya, yb});
    }
}

void Compress() {
    for(int i=1; i<=n; ++i) b[i] = &a[i].ya, b[i+n] = &a[i].yb;
    sort(b+1, b+n*2+1, [] (ll *x, ll *y) { return *x < *y; });
    for(int i=1; i<=n*2; ++i) {
        if (!cnt || val[cnt] != *b[i]) val[++cnt] = *b[i];
        *b[i] = cnt;
    }
}

void Init() {
    Compress();
    for(int i=1; i<=n; ++i) {
        d[i] = {a[i].xa, a[i].ya, a[i].yb, a[i].xb - a[i].xa};
        d[i+n] = {a[i].xb, a[i].ya, a[i].yb, 0};
    }
    sort(d+1, d+n*2+1);
}

void update(Data2 d2) {
    for(int i=d2.ya; i<d2.yb; ++i) {
        h2[i] += d2.w;
    }
}

void update2(int add) {
    for(int i=1; i<cnt; ++i) {
        if (h2[i]) h2[i] -= add, high[i] += add;
        else high[i] = 0;
    }
}

void Solve() {
    int r = 0;
    for(int i=1; i<cnt; ++i) {
        while (r && high[Q[r]] >= high[i]) {
            res = max(res, high[Q[r]] * (val[i] - val[Q[r-1] + 1]));
            --r;
        }
        Q[++r] = i;
    }
    while (r) {
        res = max(res, high[Q[r]] * (val[cnt] - val[Q[r-1] + 1]));
        --r;
    }
}

void Process2() {
    Init();
    for(int i=1; i<=n*2; ++i) {
        int j = i;
        while (j<=n*2 && d[j].x == d[i].x) update(d[j]), ++j;
        if (j <= n*2) update2(d[j].x - d[i].x);
        i = j-1;
        Solve();
    }
}

void Process() {
    for(int i=1; i<=100; ++i) if (Color[i].size()) {
        n = Color[i].size();
        for(int j=0; j<n; ++j) a[j+1] = Color[i][j];
        Process2();
    }
    printf("%lld", res);
}

int main()
{
    freopen("chunhat.inp","r",stdin);
    freopen("chunhat.out","w",stdout);
    Enter();
    Process();
}
