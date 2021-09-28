#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
const int N = 100005;
int n, res;
vector<int> S[N];
map<int, int> M[N];

void Enter() {
    scanf("%d", &n);
    int u, v;
    for(int i=1; i<n; ++i) {
        scanf("%d%d", &u, &v);
        S[u].push_back(v);
        S[v].push_back(u);
    }
}

int DFS(int u, int pa) {
    if (M[u].count(pa)) return M[u][pa];
    vector<int> Q;
    for(int v : S[u]) if (v != pa) {
        int x = DFS(v, u);
        Q.push_back(x);
    }
    sort(Q.begin(), Q.end());

    int cnt = 0;
    for(int i=1, j=0; ; ++i) {
        while (j < Q.size() && Q[j] < i) {
            if (cnt < Q[j]) ++cnt;
            ++j;
        }
        if ((int) Q.size() - j + cnt < i) return M[u][pa] = i;
    }
}

void Process() {
    for(int i=1; i<=n; ++i) {
        int x = DFS(i, i);
        res = max(res, x);
    }
    printf("%d", res);
}
/*
#include <bits/stdc++.h>
void Sinh() {
    ofstream fo("xepghe.inp");
    srand(time(NULL));
    fo << (n = 100000) << '\n';
    for(int i=2; i<=n; ++i) fo << rand() % (i-1) + 1 << ' ' << i << '\n';
    fo.close();
}
*/
int main()
{
    freopen("xepghe.inp","r",stdin);
    freopen("xepghe.out","w",stdout);
    Enter();
    Process();
}
