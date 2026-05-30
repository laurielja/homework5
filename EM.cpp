//
// Created by Lauri on 2026/5/29.
//
#include<bits/extc++.h>
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
    vector<int>path(n), ans(n);
    int minint = INT_MAX;
    iota(path.begin(), path.end(), 0);
    auto len = [n, edge](vector<int> p) {
        int cnt = 0;
        for (int i = 1; i < n; i++) {
            cnt += edge[p.at(i - 1)][p.at(i)];
        }
        cnt += edge[p.at(n - 1)][p.at(0)];
        return cnt;
    };
    do {
        auto l = len(path);
        if (l < minint) {
            minint = l;
            ans = path;
        }
    }while (next_permutation(path.begin(), path.end()));
    cout<<minint<<endl;
}