#include "bits/stdc++.h"

using namespace std;

int main() {

    int n, m; cin >> n >> m;
    
    int steps = 0;
    while (m > n) {
        if (m&1) m++;
        else m /= 2;
        steps++;
    }

    cout << steps + n - m;

    return 0;
}