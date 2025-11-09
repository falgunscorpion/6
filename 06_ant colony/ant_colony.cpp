#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<vector<int>> CostGraph = {
        {0, 5, 15, 4},
        {5, 0, 4, 8},
        {15, 4, 0, 1},
        {4, 8, 1, 0}
    };

    int n = CostGraph.size();
    vector<int> nodes;

    for (int i = 1; i < n; i++) nodes.push_back(i);

    cout << "All possible paths starting and ending at 'a':\n";

  
    do {
        int cost = 0;
        int current = 0;

        cout << "a -> ";
        for (int i : nodes) {
            cost += CostGraph[current][i];
            cout << char('a' + i) << " -> ";
            current = i;
        }

        cost += CostGraph[current][0]; 
        cout << "a  |  Cost = " << cost << endl;

    } while (next_permutation(nodes.begin(), nodes.end()));

    return 0;
}
