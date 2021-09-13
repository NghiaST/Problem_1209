#include <iostream>
#include <vector>
#include <deque>
#define dep deque<pair<long long, long long>>
using namespace std;
int n, L, R, L3, R3;
long long res;
vector<int> S[50005];

void Enter() {
    scanf("%d%d%d", &n, &L, &R);
    L3 = (L + 2) / 3 * 3;
    R3 = (R + 3) / 3 * 3;
    int u, v;
    for(int i=1; i<n; ++i) {
        scanf("%d%d", &u, &v);
        S[u].push_back(v);
        S[v].push_back(u);
    }
}

long long get(dep &a, int x) {
    if (x < 0) return a[0].first;
    if (x >= a.size()) return 0;
    return a[x].first;
}

long long get3(dep &a, int x) {
    if (x < 0) x = (x%3 + 3) % 3;
    if (x >= a.size()) return 0;
    return a[x].second;
}

void update(dep &a, dep &b) {
    for(int i=0; i<b.size(); ++i) {
        long long tmp = b[i].first - (i+1 < b.size() ? b[i+1].first : 0);
        long long tmp2 = get(a, L - i) - get(a, R - i + 1);
        long long tmp3 = get3(a, L3 - i) - get3(a, R3 - i);
        res += tmp * (tmp2 - tmp3);
    }
    for(int i=0; i<b.size(); ++i) a[i].first += b[i].first, a[i].second += b[i].second;
}

dep DFS(int u, int pa) {
    dep Q{{1, 1}};
    for(int v : S[u]) if (v != pa) {
        dep P = DFS(v, u);
        P.push_front({P.front().first, get3(P, 2)});
        if (Q.size() < P.size()) Q.swap(P);
        update(Q, P);
    }
    return Q;
}

void Process() {
    DFS(1, 0);
    printf("%lld", res);
}

int main()
{
    freopen("cntpairs.inp","r",stdin);
    freopen("cntpairs.out","w",stdout);
    Enter();
    Process();
}
