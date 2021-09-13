#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 305;
int n, k, r, r2, P[10], Ans[10];
long long res;

struct point{
    long long x, y;
    bool operator < (point &p) { return x < p.x || x == p.x && y < p.y; }
} a[N], Q[N * 2], Q2[N];

void Enter() {
    scanf("%d%d", &n, &k);
    for(int i=1; i<=n; ++i) scanf("%lld%lld", &a[i].x, &a[i].y);
}

long long acreage(point a, point b, point c) {
    return a.x * (c.y - b.y) + b.x * (a.y - c.y) + c.x * (b.y - a.y);
}

long long DienTich() {
    long long tmp = 0;
    P[0] = P[k]; P[k+1] = P[1];
    for(int i=1; i<=k; ++i) tmp += (Q[P[i-1]].x - Q[P[i+1]].x) * Q[P[i]].y;
    return abs(tmp);
}

void Init() {
    sort(a+1, a+n+1);
    for(int i=1; i<=n; ++i) {
        while (r > 1 && acreage(Q[r-1], Q[r], a[i]) >= 0) --r;
        while (r2 > 1 && acreage(Q2[r2-1], Q2[r2], a[i]) <= 0) --r2;
        Q[++r] = Q2[++r2] = a[i];
    }
    while (--r2 > 1) Q[++r] = Q2[r2];
    for(int i=1; i<=r; ++i) Q[i + r] = Q[i];
}

void Solve(int x) {
    if (x > k) return;
    if (P[x-1] == P[x]) ++P[x];
    while (true) {
        Solve(x + 1);
        long long tmp = DienTich();
        ++P[x];
        if (tmp > DienTich()) {
            --P[x];
            break;
        }
    }
}

void Process() {
    for(int i=1; i<=k; ++i) P[i] = i;
    for(int i=1; i<=r; ++i) {
        P[1] = i;
        Solve(2);
        long long tmp = DienTich();
        if (res < tmp) {
            res = tmp;
            for(int j=1; j<=k; ++j) Ans[j] = P[j];
        }
    }
    for(int i=1; i<=k; ++i) printf("%lld %lld\n", Q[Ans[i]].x, Q[Ans[i]].y);
}

int main()
{
    freopen("livestock.inp","r",stdin);
    freopen("livestock.out","w",stdout);
    Enter();
    Init();
    Process();
}
