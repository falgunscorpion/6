#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <random>
#include <algorithm>
using namespace std;

double cost[4][4] = {
    {0, 5, 15, 4},
    {5, 0, 4, 8},
    {15, 4, 0, 1},
    {4, 8, 1, 0}
};

double pheromone[4][4] = {
    {0, 4, 10, 3},
    {4, 0, 1, 2},
    {10, 1, 0, 1},
    {3, 2, 1, 0}
};

double alpha = 1;   // pheromone influence
double beta = 1;    // heuristic influence
double rho = 0.5;   // evaporation rate
int numAnts = 2;
int numIterations = 5;
int numNodes = 4;

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0.0, 1.0);

int chooseNextNode(int current, const vector<int>& unvisited);

int main() {
    for (int iter = 1; iter <= numIterations; iter++) {
        cout << "=== Iteration " << iter << " ===\n";

        vector<vector<int>> allPaths;
        vector<double> allCosts;

        // Each ant constructs a path
        for (int ant = 0; ant < numAnts; ant++) {
            vector<int> path;
            path.push_back(0); // start at 'a'

            vector<int> unvisited;
            for (int i = 1; i < numNodes; i++) unvisited.push_back(i);

            while (!unvisited.empty()) {
                int next = chooseNextNode(path.back(), unvisited);
                path.push_back(next);
                unvisited.erase(remove(unvisited.begin(), unvisited.end(), next), unvisited.end());
            }

            path.push_back(0); // return to 'a'
            allPaths.push_back(path);

            // Calculate cost
            double costSum = 0;
            for (int i = 0; i < path.size() - 1; i++) {
                costSum += cost[path[i]][path[i + 1]];
            }
            allCosts.push_back(costSum);

            // Print the path of this ant
            cout << "Ant " << ant + 1 << " path: ";
            for (int node : path) cout << char('a' + node) << " ";
            cout << " | Cost = " << costSum << "\n";
        }

        // Update pheromones
        double delta[4][4] = {0};

        for (int k = 0; k < allPaths.size(); k++) {
            const vector<int>& path = allPaths[k];
            for (int i = 0; i < path.size() - 1; i++) {
                int from = path[i];
                int to = path[i + 1];
                delta[from][to] += 1.0 / allCosts[k];
            }
        }

        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                pheromone[i][j] = (1 - rho) * pheromone[i][j] + delta[i][j];
            }
        }

        // Print updated pheromone matrix
        cout << "\nUpdated Pheromone Matrix:\n";
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                cout << setw(6) << fixed << setprecision(2) << pheromone[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n-------------------------------\n\n";
    }

    return 0;
}

// Choose next node based on pheromone and heuristic
int chooseNextNode(int current, const vector<int>& unvisited) {
    vector<double> probs(unvisited.size());
    double denom = 0.0;

    for (int i = 0; i < unvisited.size(); i++) {
        int node = unvisited[i];
        denom += pow(pheromone[current][node], alpha) * pow(1.0 / cost[current][node], beta);
    }

    for (int i = 0; i < unvisited.size(); i++) {
        int node = unvisited[i];
        probs[i] = (pow(pheromone[current][node], alpha) * pow(1.0 / cost[current][node], beta)) / denom;
    }

    double r = dis(gen);
    double cumulative = 0.0;
    for (int i = 0; i < probs.size(); i++) {
        cumulative += probs[i];
        if (r <= cumulative) return unvisited[i];
    }

    return unvisited.back(); // fallback
}
