#include <iostream>
using namespace std;
const int N = 10005, M = 1005;
int t, n, m, w[N], v[N], ok[N], D1[M], D2[M];
int vmax, pmax, res;

void Enter() {
    cin >> n >> m;
    for(int i=1; i<=n; ++i) cin >> w[i];
    for(int i=1; i<=n; ++i) cin >> v[i];
}

void QHD(int l, int r, int k, int *D) {
    fill(D, D+k+1, 0);
    D[0] = 1;
    for(int i=l; i<=r; ++i) {
        for(int j=k; j>=w[i]; --j) D[j] = max(D[j], D[j-w[i]] + v[i]);
    }
    for(int i=0; i<=k; ++i) --D[i];
}

void Divide(int l, int r, int k, int val) {
    if (k == 0) return;
    if (l == r) return (void)(ok[l] = true);
    int mid = (l+r) / 2;
    QHD(l, mid, k, D1);
    QHD(mid+1, r, k, D2);
    int p = -1;
    for(int i=0; i<=k; ++i) if (D1[i] + D2[k-i] == val) p = i;
    int vmid = D1[p];
    Divide(l, mid, p, vmid);
    Divide(mid+1, r, k-p, val-vmid);
}

void Process() {
    fill(ok+1, ok+n+1, 0);
    QHD(1, n, m, D1);
    pmax = 0;
    for(int i=1; i<=m; ++i) if (D1[pmax] < D1[i]) pmax = i;
    vmax = D1[pmax];
    Divide(1, n, pmax, vmax);
    res = 0;
    for(int i=1; i<=n; ++i) res += ok[i];
    cout << vmax << ' ' << res << '\n';
    for(int i=1; i<=n; ++i) if (ok[i]) cout << i << ' ';
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin >> t;
    while (t--) {
        Enter();
        Process();
    }
}
