#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an item with value and weight
struct Item {
    int value;
    int weight;
};

// Function to solve the 0-1 knapsack problem using dynamic programming
int knapsack(int maxWeight, const vector<Item>& items, vector<bool>& selectedItems) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= maxWeight; w++) {
            if (items[i - 1].weight > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                dp[i][w] = max(dp[i - 1][w], items[i - 1].value + dp[i - 1][w - items[i - 1].weight]);
            }
        }
    }

    int maxValue = dp[n][maxWeight];
    int w = maxWeight;
    for (int i = n; i > 0 && maxValue > 0; i--) {
        if (maxValue != dp[i - 1][w]) {
            selectedItems[i - 1] = true;
            maxValue -= items[i - 1].value;
            w -= items[i - 1].weight;
        }
    }

    return dp[n][maxWeight];
}

int main() {
    int maxWeight, n;
    cout << "Enter the maximum weight the knapsack can hold: ";
    cin >> maxWeight;

    cout << "Enter the number of items: ";
    cin >> n;

    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight for item " << i + 1 << ": ";
        cin >> items[i].value >> items[i].weight;
    }

    vector<bool> selectedItems(n, false);
    int maxValue = knapsack(maxWeight, items, selectedItems);

    cout << "Maximum loot value: " << maxValue << endl;

    // Display selected items in a table
    cout << "\nSelected Items:\n";
    cout << "Index | Value | Weight\n";
    cout << "-----------------------\n";
    for (int i = 0; i < n; i++) {
        if (selectedItems[i]) {
            cout << "  " << i + 1 << "   |   " << items[i].value << "   |   " << items[i].weight << endl;
        }
    }

    return 0;
}