#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
const int N = 1000055;
int n, k, num[N], c[N], cn[N], p[N], pn[N], cnt[N], L[N], exist[15], avail[N];
string s, w;
int res, P_res;

void Enter() {
    scanf("%d\n", &k);
    for(int i=1; i<=k; ++i) {
        getline(cin, w);
        s += w + char(i + 47);
        int n2 = s.length();
        for(int j=n; j<n2-1; ++j) num[j] = i;
        n = n2;
    }
}

void Suffix() {
    for(int i=0; i<n; ++i) ++cnt[s[i]];
    for(int i=1; i<256; ++i) cnt[i] += cnt[i-1];
    for(int i=n-1; i>=0; --i) p[--cnt[s[i]]] = i;
    int classes = 1;
    for(int i=1; i<n; ++i) {
        if (s[p[i]] != s[p[i-1]]) ++classes;
        c[p[i]] = classes - 1;
    }
    fill(cnt, cnt + 256, 0);
    for(int h=1; h<n && classes<n; h<<=1) {
        fill(cnt, cnt + classes, 0);
        for(int i=0; i<n; ++i) {
            pn[i] = p[i] - h;
            if (pn[i] < 0) pn[i] += n;
        }
        for(int i=0; i<n; ++i) ++cnt[c[pn[i]]];
        for(int i=1; i<classes; ++i) cnt[i] += cnt[i-1];
        for(int i=n-1; i>=0; --i) p[--cnt[c[pn[i]]]] = pn[i];
        classes = 1;
        for(int i=1; i<n; ++i) {
            if (c[p[i]] != c[p[i-1]] || c[(p[i] + h) % n] != c[(p[i-1] + h) % n]) ++classes;
            cn[p[i]] = classes - 1;
        }
        for(int i=0; i<n; ++i) c[i] = cn[i];
    }
}

void LCP() {
    for(int i=0, d=0; i<n-1; ++i) {
        int j = p[c[i] - 1];
        while (s[i + d] == s[j + d]) ++d;
        L[c[i]] = d--;
        if (d < 0) d = 0;
    }
}

void Solve() {
    deque<int> Q;
    int cnt = 0;
    for(int l=k-1, r=k; r<n; ++r) {
        ++cnt;
        int part = num[p[r]];
        if (exist[part]) --cnt, avail[exist[part]] = 0;
        avail[r] = 1;
        exist[part] = r;
        while (!avail[l]) ++l;

        while (!Q.empty() && L[Q.back()] >= L[r]) Q.pop_back();
        while (!Q.empty() && Q.front() <= l) Q.pop_front();
        Q.push_back(r);

        if (cnt == k) {
            if (res < L[Q.front()]) {
                res = L[Q.front()];
                P_res = p[Q.front()];
            }
        }
    }
    for(int i=0; i<res; ++i) putchar(s[i + P_res]);
}

void Process() {
    Suffix();
    LCP();
    Solve();
}

int main()
{
    freopen("longeststr.inp","r",stdin);
    freopen("longeststr.out","w",stdout);
    Enter();
    Process();
}
