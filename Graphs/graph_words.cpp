#include "bits/stdc++.h"
using namespace std;

// THIS IS AN IMPLICIT GRAPH PROBLEM!

unordered_set<string> dict; // the SET here is the graph! (works as the storage/adj_list, mat, edge_set)
queue<string> q; // absolute NEED for any BFS problem!
unordered_map<string, int> dist; // vector<bool>visited turned into this!!

// since we are filling up these data structures dynamically on the way, we can confidently declare them globally. we don't need to resize them

int minimum_transformation(string start, string end) {

// IF given mulutiple test cases, define all the data structures here!
   
// unordered_set<string> dict;
// queue<string> q;
// unordered_map<string, int> dist;

    q.push(start);
    dist[start] = 0; // entry created!

    while (!q.empty()) {
        string u = q.front(); // TC ??
        q.pop(); // TC??


        // so you can check immediately here
        if (u == end) return dist[u];
        // NOTE : recall from 1-2 : the moment you pop out u (head) from queue, dist[u] = exactly the minimum distance {that's literally a lemma to prove!}

        // NOTE : if the while loop doesn't return from here, 
        // then it means, mathematically, there is no path from start to end, 
        // if there were, the end string had been pushed into the queue at some time!
        // so that means, there is no path from start to end
        // that has either 2 meanings
        // 1. end string is a node from a disconnected component! but that is not possible, as per the problem's statement!
        // 2. end exists in the same graph but there is no path --> the exact case for printing -1 ! 

        // generate edges on the fly
        // edge (u, v) = u ----> v
        string temp = u;

        for (int i=0; i<temp.size(); i++) {
            char original = temp[i];
            for (char j='a'; j<='z'; j++) {
                if (j == original) continue;

                temp[i] = j;
                string v = temp;
                
                // normally we would just check    if (!visited[v]) q.push(v), visited[v] = true;

                // but since, we are generating edges on the go, we first need to check whether it's a valid edge or not
                // normally we pull out v from adj_list[u] so obviously it will be an edge

                if (dict.count(v)) {
                    if (! dist.count(v)) // dist map e nai mane visited[v] = false;
                    {
                        q.push(v);
                        dist[v] = dist[u] + 1; // ei line ta likhlei map e ekta entry create hoe jae, remember?!
                    }
                }
                temp[i] = original;
            }
        }
    }

    // if we make it to this line, then that means, the queue emptied out but there is now way from start to end
    // answer -1!
    return -1;
}


int main() {
    int n; cin >> n;

    for (int i=0; i<n; i++) {
        string word; cin >> word;
        dict.insert(word);
    }

    string start, end;
    cin >> start >> end;

    cout << minimum_transformation(start, end);


    // // IF given multiple test cases!
    // int t; cin >> t;
    // while (t--) {
    //     int n; cin >> n;
    //     for (int i=0; i<n; i++) {
    //         string word; cin >> word;
    //         dict.insert(word);
    //     }

    //     string start, end;
    //     cin >> start >> end;

    //     cout << minimum_transformation(start, end);
    // }


    // NOTES : 
    // void solve() {
    // // Declared LOCALLY! They are born completely empty every time solve() is called.******
    // unordered_set<string> dict; 
    // queue<string> q; 
    // unordered_map<string, int> dist; 

    // // ... read inputs for this specific test case ...
    // // ... run BFS ...
    // // ... print answer ...
    
    // // When solve() finishes, these structures are automatically destroyed from memory.*******
    // }


    return 0;
}

