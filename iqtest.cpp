#include <iostream>
using namespace std;
int a[4];
bool ok1 = true, ok2 = true;

int main()
{
    freopen("iqtest.inp","r",stdin);
    freopen("iqtest.out","w",stdout);
    for(int i=0; i<4; i++) scanf("%d", &a[i]);
    for(int i=1; i<3; i++) if (a[i]*2 != a[i-1] + a[i+1]) ok1 = false;
    for(int i=1; i<3; i++) if (a[i]*a[i] != a[i-1] * a[i+1]) ok2 = false;
    if (ok1) cout << a[3]*2 - a[2];
    else if (ok2) cout << a[3]*a[3] / a[2];
    else cout << 42;
}
