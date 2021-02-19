#include <iostream>
#define REP(i, l, r) for(int i=l; i<r; i++)
#define FOR(i, l, r) for(int i=l; i<=r; i++)
using namespace std;
int p, q, l, r, fmin, fmax, res;
int *a, *b, *c, *d;

void Enter() {
    scanf("%d%d%d%d", &p, &q, &l, &r);
    a = new int [p] ();
    b = new int [p] ();
    c = new int [q] ();
    d = new int [q] ();
    REP(i,0,p) scanf("%d%d", &a[i], &b[i]);
    REP(i,0,q) scanf("%d%d", &c[i], &d[i]);
}

void Process() {
    fmin = max(0, a[0] - d[q-1]);
    fmax = max(0, b[q-1] - c[0]);
    FOR(i,l,r) {
        int p1 = 0, p2 = 0;
        while (p1 < p && p2 < q) {
            if (b[p1] < c[p2] + i) p1++;
            else if (d[p2] + i < a[p1]) p2++;
            else {
                res++;
                break;
            }
        }
    }
    cout << res;
}

int main()
{
    freopen("chat.inp","r",stdin);
    freopen("chat.out","w",stdout);
    Enter();
    Process();
}
