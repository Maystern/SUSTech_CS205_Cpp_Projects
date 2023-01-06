# include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const int M = 10;
int pw10[M], a[N];
int v[N][M], cnt[N];
int fin[N], tot;
int main() {
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    pw10[0] = 1;
    for (int i = 1; i < 10; i++) pw10[i] = pw10[i - 1] * 10;
    for (int p = 1; p <= n; p++) {
        int val = abs(a[p]), sign = (a[p] < 0) ? -1 : 1;
        while (val > 0) {
            v[p][cnt[p]++] = val % 10;
            val /= 10;
        }
        for (int i = cnt[p] - 1; i >= 0; i--) {
            int res = 0, id = -1;
            for (int j = i - 1; j >= 0; j--) {
                if (sign * ((v[p][j] - v[p][i]) * pw10[i] + (v[p][i] - v[p][j]) * pw10[j]) > res) {
                    res = sign * ((v[p][j] - v[p][i]) * pw10[i] + (v[p][i] - v[p][j]) * pw10[j]);
                    id = j;
                }
            }
            if (id == -1) continue;
            fin[++tot] = res - k;
            swap(v[p][i], v[p][id]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans += a[i];
    cout << ans << endl;
    sort(fin + 1, fin + 1 + tot);
    for (int i = 1; i <= min(tot, m); i++)
        if (fin[i] > 0) ans += fin[i];
    cout << ans << endl;
    return 0;
}