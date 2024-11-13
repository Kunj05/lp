#include <bits/stdc++.h>
using namespace std;

const int N = 4; // Number of cities

// Final path array to store the optimal path
vector<int> final_path(N + 1);

// Array to mark visited cities in the current path
vector<bool> visited(N,false);

// Final result stores the minimum cost of the tour
int final_res = INT_MAX;

// Function to copy the current path to the final path
void copyToFinal(const vector<int>& curr_path) {
    for (int i = 0; i < N; i++) {
        final_path[i] = curr_path[i];
    }
    final_path[N] = curr_path[0]; // Complete the cycle by returning to the first city
}

// Function to find the minimum edge cost for a given vertex 'i'
int findFirstMin(const vector<vector<int>>& adj, int i) {
    vector<int> row = adj[i];
    sort(row.begin(), row.end());
    return row[0]; // Second smallest element
}

// Function to find the second minimum edge cost for a given vertex 'i'
int findSecondMin(const vector<vector<int>>& adj, int i) {
    vector<int> row = adj[i];
    sort(row.begin(), row.end());
    return row[1]; // Second smallest element
}

// Recursive function to solve TSP using Branch and Bound
void TSPRec(const vector<vector<int>>& adj, int curr_bound, int curr_weight, int level, vector<int>& curr_path) {
    // Base case: If all cities have been visited
    if (level == N) {
        if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + adj[curr_path[level - 1]][curr_path[0]]; // Add return cost
            if (curr_res < final_res) {
                copyToFinal(curr_path);
                final_res = curr_res; // Update the minimum cost
            }
        }
        return;
    }

    // Try every vertex as the next city in the tour
    for (int i = 0; i < N; i++) {
        // Skip the vertex if it's already visited or no edge exists
        if (adj[curr_path[level - 1]][i] == 0 || visited[i]) continue;

        // Temporarily mark the vertex as visited
        visited[i] = true;
        curr_path[level] = i;
        curr_weight += adj[curr_path[level - 1]][i];

        int temp_bound = curr_bound;

        // Adjust the lower bound for the current level
        if (level == 1) {
            curr_bound -= (findFirstMin(adj, curr_path[level - 1]) + findFirstMin(adj, i)) / 2;
        } else {
            curr_bound -= (findSecondMin(adj, curr_path[level - 1]) + findFirstMin(adj, i)) / 2;
        }

        // If the current lower bound + current weight is less than the final result, explore further
        if (curr_bound + curr_weight < final_res) {
            TSPRec(adj, curr_bound, curr_weight, level + 1, curr_path);
        }

        // Backtrack: Reset the visited vertex and the current path
        visited[i] = false;
        curr_weight -= adj[curr_path[level - 1]][i];
        curr_bound = temp_bound;
    }
}

// Function to initiate the Branch and Bound algorithm for TSP
void TSP(const vector<vector<int>>& adj) {
    vector<int> curr_path(N + 1,-1);
    int curr_bound = 0;

    // Calculate the initial lower bound using first and second minimum edges
    for (int i = 0; i < N; i++) {
        curr_bound += (findFirstMin(adj, i) + findSecondMin(adj, i));
    }

    // Halve the bound as per the Branch and Bound formula
    curr_bound = (curr_bound % 2 == 0) ? curr_bound / 2 : (curr_bound / 2) + 1;

    // Start from the first vertex (0th city)
    visited[0] = true;
    curr_path[0] = 0;

    // Call the recursive function to solve the problem
    TSPRec(adj, curr_bound, 0, 1, curr_path);
}

int main() {
    // Adjacency matrix for the given graph (cities and travel costs)
    vector<vector<int>> adj = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    // Call TSP function to solve the problem
    TSP(adj);

    // Output the result
    cout << "Minimum cost: " << final_res << endl;
    cout << "Path Taken: ";
    for (int i = 0; i <= N; i++) {
        cout << final_path[i] << " ";
    }
    cout << endl;

    return 0;
}
// Explanation of Branch and Bound and its Use in the Traveling Salesman Problem (TSP)
// Branch and Bound (B&B) is a general algorithm for finding optimal solutions to optimization problems, particularly those that can be formulated as combinatorial problems (where we search through a set of possible solutions). In simple terms, it's an algorithmic framework that systematically explores all possible solutions but prunes branches that cannot lead to an optimal solution, thereby reducing the search space.

// The main idea behind Branch and Bound is:

// Branching: We break the problem into smaller sub-problems (branches).
// Bounding: We calculate a bound (a lower or upper limit) for each sub-problem to decide whether we need to explore it or if we can safely ignore it (pruning).
// Pruning: If a branch can't possibly lead to an optimal solution (based on its bound), we stop exploring that branch. This makes the algorithm more efficient than brute-force search.
// How Branch and Bound Works:
// Branching: The algorithm breaks down the problem into smaller subproblems, creating a tree-like structure (the search tree). Each node in the tree represents a subproblem.
// Bounding: For each subproblem, we compute an upper or lower bound (depending on the optimization goal). If the bound indicates that this subproblem can't lead to a better solution than what has already been found, we prune the branch (i.e., we stop exploring that path).
// Pruning: This step reduces the search space. It discards branches that cannot provide a better solution based on the bound.
// Traveling Salesman Problem (TSP) and Branch and Bound
// Problem Recap:
// The Traveling Salesman Problem (TSP) involves finding the shortest possible route that visits a set of cities exactly once and returns to the starting city. Given the number of cities, the number of possible routes (or permutations) grows very quickly, and a brute-force solution would involve checking all these possible routes. For N cities, there are (N-1)! possible routes to check, which is computationally expensive for large N.

// How Branch and Bound is Applied to TSP:
// State Space Representation (Branching):

// The state space of the problem can be represented as a tree where each node represents a partial path. A path represents the cities visited so far, and the root node represents the starting point.
// From each node, there are branches that represent adding a new city to the current path. This creates a search tree.
// Bounding Function:

// For any partial path (subproblem), we need a way to calculate the lower bound of the path length, which estimates the minimum possible length of the tour starting from that node (subpath).
// The lower bound calculation helps in two ways:
// Pruning: If the lower bound for a node exceeds the length of the best solution found so far (the global minimum), we can prune that branch, as it cannot yield a better solution.
// Guiding the Search: The lower bound helps the algorithm decide which paths to explore first. In general, we explore branches with a lower bound closer to the best known solution, thus improving efficiency.
// Pruning:

// If at any point the lower bound of the partial tour is greater than the length of the best known complete tour, we stop exploring that branch (this is pruning).
// The idea is that we only continue exploring paths that have the potential to lead to better solutions, cutting off paths that are not promising.
// Key Components in the Code:
// firstMin() and secondMin() functions: These functions are used to calculate the lower bound for each city:

// firstMin(i) finds the minimum weight edge from city i to any other city.
// secondMin(i) finds the second smallest edge weight from city i. The second minimum is useful because, in the Branch and Bound algorithm, we often calculate the bound by taking the average of the minimum and second minimum edge weights, which provides a tighter bound.
// curr_bound: This represents the current lower bound on the cost of the partial solution (path). It’s updated as the algorithm progresses and helps guide the search. If at any point, the sum of the current bound and the accumulated weight exceeds the best solution found so far, the algorithm prunes that branch.

// TSPRec() function (Recursive function): This function is the heart of the Branch and Bound approach. It explores the search tree recursively by choosing one unvisited city at each level, updating the lower bound, and pruning unnecessary paths.

// final_res: This stores the minimum cost found so far. If a better solution (a shorter path) is found during the recursion, it’s updated.

// High-Level Overview of the Code:
// TSP() function: Initializes the problem and starts the recursion.

// It calculates the initial bound (curr_bound), which is a heuristic estimate of the minimum possible cost.
// The function starts by visiting the first city and then calls the recursive function TSPRec().
// TSPRec() function (Recursive Backtracking):

// It tries to extend the current path by visiting a new city, calculates the new bound, and explores further if it seems promising.
// The function backtracks when it reaches a leaf node (i.e., all cities are visited) and checks if the solution is better than the best known solution.
// If the lower bound for a path exceeds the current best solution, the branch is pruned, and further exploration is stopped for that path.
// Final Result: After the recursion, the algorithm outputs the minimum cost and the optimal path.

// Example Walkthrough:
// For the following adjacency matrix (representing distances between cities):

// cpp
// Copy code
// int adj[N][N] = {
//     {0, 10, 15, 20},
//     {10, 0, 35, 25},
//     {15, 35, 0, 30},
//     {20, 25, 30, 0}
// };
// The algorithm starts at city 0 and explores the possible paths recursively, keeping track of the minimum cost so far.
// At each step, it calculates the lower bound (based on the minimum edge costs) to decide whether it's worth continuing down the current path.
// If a branch cannot lead to a better solution than the current best path, it is pruned.
// After visiting all possible cities and evaluating each path, the algorithm outputs the shortest possible route (tour) and the corresponding cost.
// Why Branch and Bound is Efficient:
// Pruning: It dramatically reduces the number of paths explored by cutting off branches that can't lead to better solutions.
// Lower Bound: By using a lower bound, the algorithm efficiently guides the search toward the most promising paths first, leading to faster convergence to the optimal solution.
// Conclusion:
// Branch and Bound is a powerful technique used to solve optimization problems like TSP, where brute force would be too slow.
// In TSP, we explore all possible routes, but we prune many of them by using bounds that tell us when it's not worth continuing down a particular path.
// This method allows us to find the optimal solution while minimizing unnecessary computations, making it much more efficient than brute-force algorithms for problems like TSP.


