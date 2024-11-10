// Time Complexity: O(n * M)
// Space Complexity: O(n * M)
// https://www.w3schools.com/dsa/dsa_ref_knapsack.php

#include <bits/stdc++.h>
using namespace std;

void printDPTable(const vector<vector<int>>& dp) {
    for (const auto& row : dp) {
        for (const auto& val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int knapsack(vector<int> &profits, vector<int> &weights, int capacity) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], profits[i - 1] + dp[i - 1][w - weights[i - 1]]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
        cout << "DP table after including item " << i << " (Weight: " << weights[i - 1] 
             << ", Profit: " << profits[i - 1] << "):" << endl;
        printDPTable(dp);
    }
    return dp[n][capacity];
}

int main() {
    int n;
    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> profits(n);
    vector<int> weights(n);
    
    for (int i = 0; i < n; i++) {
        cout << "Enter the profit of  items"<<i+1<<": ";
        cin >> profits[i];
    }

    for (int i = 0; i < n; i++) {
        cout << "Enter the weight of item "<<i+1<<": ";
        cin >> weights[i];
    }

    int capacity;
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    int max_profit = knapsack(profits, weights, capacity);
    cout << "Max profit: " << max_profit << endl;

    return 0;
}

// How would you track which items are selected for the optimal solution?
// ------After filling the DP table, you can backtrack from dp[n][M] (the maximum profit) to find which items were included by comparing the 
//current value with the value in the row above (or the previous column) to check if an item was included or not.

// How does the problem change if the items are sorted by weight or profit?
// -----While sorting the items by weight or profit might give you a more efficient approach in some heuristics or greedy algorithms, it does 
// not change the solution in the dynamic programming approach, because 0/1 knapsack is not a greedy problem. Sorting is generally not a 
// helpful step in the DP approach because the optimal solution may require a non-intuitive combination of lighter and heavier items.
