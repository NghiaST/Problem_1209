/// Time Complexity : O(N * logN)
#include <iostream>
using namespace std;
const int N = 100005, M = 100005, logN = 30;
int n, q, nVer, nNode, ver[M];
long long a[N];
struct Node {
    long long ln;
    int lft, rgt;
    Node() {}
    Node(long long ln, int lft, int rgt) : ln(ln), lft(lft), rgt(rgt) {}
} it[N*logN];

void Enter() {
    cin >> n >> q;
    for(int i=1; i<=n; ++i) cin >> a[i];
}

int set_IT(int l, int r) {
    int pos = ++nNode;
    if (l == r) {
        it[pos] = Node(a[l], 0, 0);
        return pos;
    }
    int mid = (l+r) / 2;
    it[pos].lft = set_IT(l, mid);
    it[pos].rgt = set_IT(mid+1, r);
    it[pos].ln = max(it[it[pos].lft].ln, it[it[pos].rgt].ln);
    return pos;
}

int update(int l, int r, int x, int Id) {
    int pos = ++nNode;
    if (l==r) {
        it[pos] = {a[x], 0, 0};
        return pos;
    }
    int mid = (l+r) / 2;
    if (x <= mid) {
        it[pos].lft = update(l, mid, x, it[Id].lft);
        it[pos].rgt = it[Id].rgt;
    } else {
        it[pos].lft = it[Id].lft;
        it[pos].rgt = update(mid+1, r, x, it[Id].rgt);
    }
    it[pos].ln = max(it[it[pos].lft].ln, it[it[pos].rgt].ln);
    return pos;
}

long long query(int l, int r, int x, int y, int Id) {
    if (l>y || r<x) return -1;
    if (x<=l && r<=y) return it[Id].ln;
    int mid = (l+r) / 2;
    return max(query(l, mid, x, y, it[Id].lft), query(mid+1, r, x, y, it[Id].rgt));
}

void Process() {
    int l, r, type, i, xVer;
    long long v;
    while (q--) {
        cin >> type;
        if (type == 1) {
            cin >> i >> v;
            a[i] = v;
            ++nVer;
            ver[nVer] = update(1, n, i, ver[nVer-1]);
        } else {
            cin >> l >> r >> xVer;
            cout << query(1, n, l, r, ver[xVer]) << '\n';
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    freopen("Persistent.inp","r",stdin);
    freopen("Persistent.out","w",stdout);
    Enter();
    ver[0] = set_IT(1, n);
    Process();
}
