#include <bits/stdc++.h>
#define FOR(i,l,r) for(int i=l; i<=r; ++i)
#define REP(i,l,r) for(int i=l; i<r; ++i)
#define FORD(i,r,l) for(int i=r; i>=l; --i)
#define REPD(i,r,l) for(int i=r-1; i>=l; --i)
using namespace std;
int n;
typedef struct node{
    long long sum;
    int h, cnt, xr, child[17];
    node *L, *R;
    node(int high) {
        REP(i, 0, 17) child[i] = 0;
        cnt = sum = xr = 0;
        L = R = NULL;
        h = high;
    }
} *TNode;
TNode root;

int getBIT(int x, int i) { return (x>>i)&1; }

void change(TNode &W) {
    if (W == NULL || W->xr == 0) return;
    int xr = W->xr; W->xr = 0;
    REP(i, 0, 17) if (getBIT(xr, i)) {
        int z = W->cnt - W->child[i];
        W->sum += (1LL << i) * (z - W->child[i]);
        W->child[i] = z;
    }
    if (getBIT(xr, W->h)) swap(W->L, W->R);
    if (W->L != NULL) W->L->xr ^= xr;
    if (W->R != NULL) W->R->xr ^= xr;
}

void add(TNode &W, int high, int x) {
    change(W);
    if (W == NULL) W = new node(high);
    for(int i=0; i<17; ++i) if (getBIT(x, i)) ++W->child[i];
    W->sum += x;
    W->cnt += 1;

    if (high < 0) return;
    if (!getBIT(x, high)) add(W->L, high - 1, x);
    else add(W->R, high - 1, x);
}

bool rem(TNode &W, int high, int x) {
    change(W);
    if (W == NULL) return false;
    if (high < 0) {
        W->cnt -= 1;
        W->sum -= x;
        REP(i, 0, 17) if (getBIT(x, i)) --W->child[i];
        if (W->cnt == 0) W = NULL;
        return true;
    }
    bool ok = true;
    if (!getBIT(x, high)) ok = rem(W->L, high - 1, x);
    else ok = rem(W->R, high - 1, x);
    if (ok) {
        W->cnt -= 1;
        W->sum -= x;
        REP(i, 0, 17) if (getBIT(x, i)) --W->child[i];
        if (W->cnt == 0) W = NULL;
        return true;
    }
    return false;
}

long long cal(TNode &W, int x) {
    change(W);
    if (W == NULL || x == 0) return 0;
    if (x >= W->cnt) return W->sum;
    if (W->h < 0) return W->sum / W->cnt * x;
    int cntL = (W->L == NULL ? 0 : W->L->cnt);
    if (x <= cntL) return cal(W->L, x);
    else return cal(W->L, x) + cal(W->R, x - cntL);
}

int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    int type, x;
    while (n--) {
        cin >> type >> x;
        if (type == 0) add(root, 16, x);
        else if (type == 1) rem(root, 16, x);
        else if (type == 2) {
            if (root != NULL) root->xr ^= x;
        }
        else if (type == 3) cout << cal(root, x) << '\n';
    }
}
