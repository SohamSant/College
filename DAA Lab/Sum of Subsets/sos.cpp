#include <iostream>
#include <vector>

using namespace std;

// Function to find subsets with the given sum
bool findSubsets(vector<int>& nums, int targetSum, vector<int>& currentSubset, int index, int currentSum) {
    // Base case: if the current sum equals the target sum
    if (currentSum == targetSum) {
        // Print the current subset
        cout << "Subset found: ";
        for (int num : currentSubset) {
            cout << num << " ";
        }
        cout << endl;
        return true;
    }

    // Iterate through the remaining elements
    for (int i = index; i < nums.size(); i++) {
        // Add the current element to the subset
        currentSubset.push_back(nums[i]);

        // Recursively check subsets with the current element included
        if (findSubsets(nums, targetSum, currentSubset, i + 1, currentSum + nums[i])) {
            return true; // Found a subset, no need to continue searching
        }

        // Backtrack: remove the current element from the subset
        currentSubset.pop_back();
    }

    return false; // No subset found with the current configuration
}

int main() {
    // Input: array of numbers
    vector<int> nums;

    // Input: target sum
    int targetSum;

    // Get the array size from the user
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    // Get array elements from the user
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < size; i++) {
        int num;
        cin >> num;
        nums.push_back(num);
    }

    // Get the target sum from the user
    cout << "Enter the target sum: ";
    cin >> targetSum;
    cout<<endl;

    // Vector to store the current subset
    vector<int> currentSubset;

    // Starting from the first element (index 0)
    if (!findSubsets(nums, targetSum, currentSubset, 0, 0)) {
        cout << "No solution exists." << endl;
    }

    return 0;
}
