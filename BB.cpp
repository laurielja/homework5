//
// Created by Lauri on 2026/5/29.
//
#include<bits/extc++.h>
using namespace std;
vector<vector<int>>edge;
vector<int>min_out;
int n;
struct node {
    vector<int>path;
    vector<bool>gone;
    int depth;
    int len;
    int bound;
    int current;
    int get_bound () {
        auto lower = this->len;
        int minn = INT_MAX >> 2;
        for (int i = 0; i < n; i++) {
            if (!gone.at(i)) {
                lower += min_out.at(i);
                minn = min(minn, edge.at(i).at(path.at(0)));
            }
        }
        return lower + minn;
    }
    auto operator<(const node& other) const {
        return this->bound > other.bound;
    }
    node (vector<int> p, vector<bool>g, int d, int l, int b, int c) {
        this->path = p;
        this->gone = g;
        this->depth = d;
        this->len = l;
        this->bound = b;
        this->current = c;
    }

    node (int m) : depth(0), len(0), bound(0), current(0) {
        this->gone.resize(m, false);
    }
};
int main() {

    cin>>n;
    edge.resize(n);
    min_out.resize(n, INT_MAX);
    for (int i  = 0; i < n; i++) {
        edge.at(i).resize(n);
        for (int j = 0; j < n; j++) {
            cin>>edge.at(i).at(j);
            if (i != j){
                min_out.at(i) = min(min_out.at(i), edge.at(i).at(j));
            }
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        vector<bool>bl(n, false);
        bl.at(i) = true;
        node a(vector<int>{i}, bl, 1, 0, 0, i);
        a.bound = a.get_bound();
        priority_queue<node>pq;
        pq.push(a);
        while (!pq.empty()) {
            auto x = pq.top();
            pq.pop();
            if (x.bound >= ans) {
                continue;
            }
            if (x.depth == n) {
                auto total_len = x.len + edge[x.current][x.path.at(0)];
                if (total_len < ans) {
                    ans = total_len;
                }
                continue;
            }
            for (int j = 0; j < n; j++) {
                if (!x.gone.at(j)) {
                    auto y = x;
                    y.gone.at(j) = true;
                    y.path.push_back(j);
                    y.len += edge[x.current][j];
                    y.current = j;
                    y.depth++;
                    y.bound = y.get_bound();
                    if (y.bound < ans) {
                        pq.push(y);
                    }
                }
            }
        }
    }
    cout<<ans<<endl;
}