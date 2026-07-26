#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

using namespace std;

const double INF = 1e9; // Large finite number for float math

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<string> idx_to_name(n);
    map<string, int> name_to_idx;

    for (int i = 0; i < n; ++i) {
        cin >> idx_to_name[i];
        name_to_idx[idx_to_name[i]] = i;
    }

    // Initialize Additive DP Table
    vector<vector<double>> dist(n, vector<double>(n, INF));
    for (int i = 0; i < n; ++i) dist[i][i] = 0.0;

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string u, v;
        double rate;
        cin >> u >> rate >> v;
        // Transform the rate using -log()
        double cost = -log(rate);
        dist[name_to_idx[u]][name_to_idx[v]] = min(dist[name_to_idx[u]][name_to_idx[v]], cost);
    }

    // 2. Floyd-Warshall (Standard Additive Min)
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // 3. The Contagion Check (Looking for Negative Cycles)
    vector<string> ans;
    for (int i = 0; i < n; ++i) {
        bool has_arbitrage = false;
        
        for (int j = 0; j < n; ++j) {
            // Using a small epsilon (-1e-8) instead of strictly < 0 
            // to prevent floating-point precision errors from triggering false positives
            if (dist[i][j] != INF && dist[j][i] != INF && dist[j][j] < -1e-8) {
                has_arbitrage = true;
                break; 
            }
        }
        
        if (has_arbitrage) {
            ans.push_back(idx_to_name[i]);
        }
    }

    // 4. Output according to problem specifications
    if (ans.empty()) {
        cout << "No Arbitrage\n";
    } else {
        for (const string& currency : ans) {
            cout << currency << "\n";
        }
    }

    return 0;
}