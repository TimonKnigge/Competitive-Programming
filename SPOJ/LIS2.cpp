#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
const int INF = 2000000000;

// Entire sequence (indices)
template<class T>
int longest_increasing_subsequence(vector<T>& a, vector<int>& seq) {
    vector<set<T>> lis(a.size(), set<T>());
    int L = 0;
    for (int i = 0; i < a.size(); ++i) {
        int l = 1, r = L;
        while (l <= r) {
            int m = (l + r + 1) / 2;
            bool check = false, _break = false;
            // is er een paar in lis[m-1] kleiner dan a[i]
            for (auto it = lis[m - 1].begin(); !_break && it != lis[m - 1].end(); ++it) {
                if (it->first < a[i].first && it->second < a[i].second)
                    check = _break = true;
                if (it->first >= a[i].first) {
                    check = false;
                    _break = true;
                }
            }
            if (check) 
                l = m + 1;
            else 
                r = m - 1;
        }
       
        lis[l - 1].insert(a[i]);
        auto it = lis[l - 1].find(a[i]);
        while (it != lis[l - 1].end()) {
            if (it->first > a[i].first && it->second > a[i].second) {
                auto rem = ++it; --it;
                lis[l - 1].erase(it);
                it = rem;
            } else it++;
        }
        if (l > L) L = l;
    }

//  seq.assign(L, -1);
//  int j = lis[L - 1];
//  for (int i = L - 1; i >= 0; --i) {
//      seq[i] = j;
//      j = pre[j];
//  }
    return L;
}

int main() {

    int N; cin >> N;
    vector<pair<int, int>> a;
    for (int i = 0; i < N; ++i) {
        int x, y; cin >> x >> y;
        a.push_back({x, y});
    }

    vector<int> seq;
    cout << longest_increasing_subsequence(a, seq) << endl;

//  for (int i = 0; i < seq.size(); ++i) cout << seq[i] << " \n"[i == seq.size() - 1];

    return 0;
}
