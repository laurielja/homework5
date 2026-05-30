//
// Created by Lauri on 2026/5/29.
//
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin>>n;
    vector<vector<int>>edge(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin>>edge[i][j];
        }
    }
    auto next = [](int x) {
        auto lowbit = x & (-x);
        auto t = lowbit + x;
        return (((x ^ t) >> 2) / lowbit) | t;
    };
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        vector<vector<int>>dp(1 << n, vector<int>(n, INT_MAX >> 2));
        dp.at(1<<i).at(i) = 0;
        for (int j = 2; j <= n; j++) {
            auto x = (1 << j) - 1;
            do {
                for (int k = 0; (1 << k) < x and k < n; k++) {
                    auto y = (1 << k);
                    if ((y & x) == 0) {
                        continue;
                    }
                    for (int m = 0; m < n; m++) {
                        dp.at(x).at(k) = min(dp.at(x).at(k), dp.at(x - y).at(m) + edge.at(m).at(k));
                    }
                }
                x = next(x);
            }while (x < (1 << n) - (1 << (n - j)));
        }
        int minn = INT_MAX;
        for (int j = 0; j < n; j++) {
            minn = min (minn, dp.at((1 << n) - 1).at(j) + edge[j][i]);
        }
        ans = min (ans, minn);
    }
    cout<<ans<<endl;
}