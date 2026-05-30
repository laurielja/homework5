#include <bits/stdc++.h>
using namespace std;
using vb = vector<double>;
static constexpr double EPS = 1e-9;
    static constexpr double INF = 1e100;
void print(set<int> s) {
    for (auto x:s) {
        cout<<x<<" ";
    }
    cout<<endl;
}
struct LPSolver {


    int m, n;
    vector<int> B, N;
    vector<vb> D;

    LPSolver(const vector<vb>& A,const vb& b,const vb& c)
        : m(b.size()),n(c.size()),N(n + 1),B(m),D(m + 2, vector<double>(n + 2)){
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                D[i][j] = A[i][j];

        for (int i = 0; i < m; i++) {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }

        for (int j = 0; j < n; j++) {
            N[j] = j;
            D[m][j] = -c[j];
        }

        N[n] = -1;
        D[m + 1][n] = 1;
    }

    void Pivot(int r, int s) {
        double inv = 1.0 / D[r][s];

        for (int i = 0; i < m + 2; i++) {
            if (i == r) continue;

            for (int j = 0; j < n + 2; j++) {
                if (j == s) continue;

                D[i][j] -= D[r][j] * D[i][s] * inv;
            }
        }

        for (int j = 0; j < n + 2; j++)
            if (j != s)
                D[r][j] *= inv;

        for (int i = 0; i < m + 2; i++)
            if (i != r)
                D[i][s] *= -inv;

        D[r][s] = inv;

        swap(B[r], N[s]);
    }

    bool Simplex(int phase) {
        int x = phase == 1 ? m + 1 : m;

        while (true) {
            int s = -1;

            for (int j = 0; j <= n; j++) {
                if (phase == 2 and N[j] == -1)
                    continue;

                if (s == -1 or D[x][j] < D[x][s] - EPS or (abs(D[x][j] - D[x][s]) < EPS and N[j] < N[s]))
                    s = j;
            }

            if (D[x][s] > -EPS)
                return true;

            int r = -1;

            for (int i = 0; i < m; i++) {
                if (D[i][s] < EPS)
                    continue;

                if (r == -1)
                    r = i;
                else {
                    double lhs =
                        D[i][n + 1] / D[i][s];

                    double rhs =
                        D[r][n + 1] / D[r][s];

                    if (lhs < rhs - EPS or (abs(lhs - rhs) < EPS and B[i] < B[r]))
                        r = i;
                }
            }

            if (r == -1)
                return false;

            Pivot(r, s);
        }
    }

    double Solve(vb& x) {
        int r = 0;

        for (int i = 1; i < m; i++) {
            if (D[i][n + 1] < D[r][n + 1])
                r = i;
        }

        if (D[r][n + 1] < -EPS) {

            Pivot(r, n);

            if (!Simplex(1) ||
                D[m + 1][n + 1] < -EPS)
                return -INF;

            if (D[m + 1][n + 1] > EPS)
                return -INF;

            if (find(B.begin(), B.end(), -1) != B.end()) {

                r = find(B.begin(),B.end(),-1) - B.begin();

                int s = 0;

                for (int j = 1; j <= n; j++) {
                    if (abs(D[r][j]) > abs(D[r][s]))
                        s = j;
                }

                Pivot(r, s);
            }
        }

        if (!Simplex(2))
            return INF;

        x.assign(n, 0);

        for (int i = 0; i < m; i++) {
            if (B[i] < n)
                x[B[i]] = D[i][n + 1];
        }

        return D[m][n + 1];
    }
};
set<int> find_circle (vb x, int n) {
    set<int> s;
    vector<vb>y(n,vb(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0 ; j < n; j++) {
            y.at(i).at(j) = x.at(i * n + j);
        }
    }
    int cur = 0;
    int prev = n;
    s.insert(cur);
    auto dfs = [&](const auto &self, int fa, int u) -> void {
        for (int i = 0; i < n; i++) {
            if (i == fa or i == u) {
                continue;
            }
            if (y.at(u).at(i) > EPS or y.at(i).at(u) > EPS) {
                if (s.find(i) != s.end()) {
                    return;
                }
                s.insert(i);
                self(self, u, i);
            }
        }
    };
    dfs (dfs, n, 0);
    return s;
}
int main() {
    int n;
    cin>>n;
    vector<vector<int>>edge(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin>>edge.at(i).at(j);
        }
    }
    vector<vb>A;
    vb b, c;

    for (int i = 0; i < n * n; i++) {
        vb y;
        for (int j = 0; j < n * n; j++) {
            if (i == j) {
                y.push_back(1.0);
            }else {
                y.push_back(0.0);
            }
        }
        A.push_back(y);
    }
    for (int i = 0; i < n * n; i++) {
        b.push_back(1.0);
    }


    for (int i = 0; i < n; i++) {

        vb row(n * n, 0);

        for (int j = 0; j < n; j++) {

            if (i == j)
                continue;

            row[i * n + j] = 1;
        }
        for (int j = 0; j < n; j++) {

            if (i == j)
                continue;

            row[j * n + i] = 1;
        }

        A.push_back(row);
        b.push_back(2);
    }
    for (int i = 0; i < n; i++) {

        vb row(n * n, 0);

        for (int j = 0; j < n; j++) {

            if (i == j)
                continue;

            row[i * n + j] = -1;
        }
        for (int j = 0; j < n; j++) {

            if (i == j)
                continue;

            row[j * n + i] = -1;
        }

        A.push_back(row);
        b.push_back(-2);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c.push_back(edge.at(i).at(j) * (-1.0));
        }
    }

    LPSolver lp(A,b,c);

    vb x;

    double ans = lp.Solve(x);

    for (;;) {
        auto s = find_circle(x, n);
        //print(s);
        if (s.size() == n) {
            break;
        }
        double cnt = 0;
        vb y(n * n, 0.0), z(n * n, 0.0);
        for (auto i:s) {
            for (auto j:s) {
                if (i != j) {
                    cnt += x.at(i * n + j);
                    y.at(i * n + j) = 1.0;
                    z.at(i * n + j) = -1.0;
                }
            }
        }
        A.push_back(y);
        A.push_back(z);
        b.push_back(cnt - 1.0);
        b.push_back(1.0 - cnt);
        lp = LPSolver(A,b,c);
        ans = lp.Solve(x);

    }
    cout << -ans << endl;

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout<<x.at(i * n + j)<<" ";
    //     }
    //     cout<<endl;
    // }

}