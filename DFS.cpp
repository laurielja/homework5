//
// Created by Lauri on 2026/5/29.
//
#include<bits/stdc++.h>
using namespace std;
vector<vector<int>>edge;
vector<bool>gone;
int n, ans = INT_MAX;
void dfs (int step, int len, int prev, int begin) {
    if (len >= ans) {
        return;
    }
    if (step == n) {
        ans = min (ans, len + edge.at(prev).at(begin));
        return;
    }
    for (int i = 0; i < n; i++) {
        if (gone.at(i) == true) {
            continue;
        }
        gone.at(i) = true;
        dfs (step + 1, len + edge.at(prev).at(i), i, begin);
        gone.at(i) = false;
    }
}
int main() {
    cin>>n;
    edge.resize(n);
    gone.resize(n, false);
    for (int i = 0; i < n; i++) {
        edge.at(i).resize(n);
        for (int j = 0; j < n; j++) {
            cin>>edge.at(i).at(j);
        }
    }
    for (int i = 0; i < n; i++) {
        gone.at(i) = true;
        dfs (1, 0, i, i);
        gone.at(i) = false;
    }
    cout<<ans<<endl;
}