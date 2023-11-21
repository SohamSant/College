#include <iostream>
#include <vector>

using namespace std;

bool flag = false;

void PrintSubsetSum(int index, int size, int set[], int targetSum, vector<int>& subset) {
    if (targetSum == 0) {
        flag = true;
        cout << "[ ";
        for (int i = 0; i < subset.size(); i++) {
            cout << subset[i] << " ";
        }
        cout << "]" << endl;
        return;
    }

    if (index == size||targetSum<0) {
        cout << "Backtracking" << endl;
        return;
    }

    // Backtracking
    cout << "Backtracking" << endl;
    PrintSubsetSum(index + 1, size, set, targetSum, subset);

    // Including the current element in the subset
    cout << "Including " << set[index] << endl;
    subset.push_back(set[index]);
    PrintSubsetSum(index + 1, size, set, targetSum - set[index], subset);
    subset.pop_back();
}

int main() {
    int n;
    cout << "Enter the number of elements in the set: ";
    cin >> n;

    int set[n];
    cout << "Enter the elements of the set: ";
    for (int i = 0; i < n; i++) {
        cin >> set[i];
    }

    int sum;
    cout << "Enter the target sum: ";
    cin >> sum;

    vector<int> subset;
    cout << "Output:" << endl;
    PrintSubsetSum(0, n, set, sum, subset);

    if (!flag) {
        cout << "There is no such subset";
    }

    return 0;
}