#include <bits/stdc++.h>
using namespace std;

// Structure to represent an item with value and weight
struct Item
{
    int value;
    int weight;
};

// Partition function for quicksort
int partition(Item arr[], int low, int high)
{
    double pivot = (double)arr[high].value / arr[high].weight;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if ((double)arr[j].value / arr[j].weight >= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quicksort function to sort items based on value/weight ratio
void quickSort(Item arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Knapsack algorithm to find the maximum value that can be stolen within the given weight limit
double knapsack(int w, Item arr[], int n)
{
    // Sort the items in descending order of value/weight ratio
    quickSort(arr, 0, n - 1);

    double finalLoot = 0.0;
    int curWt = 0;

    // Iterate through the sorted items and add them to the knapsack greedily
    for (int i = 0; i < n; i++)
    {
        if (curWt + arr[i].weight <= w)
        {
            curWt += arr[i].weight;
            finalLoot += arr[i].value;
            cout << "Looted item with val: " << arr[i].value << " and with weight : " << arr[i].weight << " remaining capacity : " << (w - curWt) << endl;
        }
        else
        {
            // Fractional part of the current item will be added to the knapsack
            int remain = w - curWt;
            finalLoot += ((double)arr[i].value / arr[i].weight) * (double)remain;
            cout << "Looted " << ((double)remain / arr[i].weight) * 100 << "% of item with value : " << arr[i].value << " and with weight : " << arr[i].weight << " remaining capacity : 0" << endl;
            break;
        }
    }

    return finalLoot;
}



int main()
{

    int maxWeight, n;
    cout << "Enter the maximum weight the knapsack can hold: ";
    cin >> maxWeight;

    cout << "Enter the number of items: ";
    cin >> n;

    vector<Item> items(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter value and weight for item " << i + 1 << ": ";
        cin >> items[i].value >> items[i].weight;
    }

    // Display the list of items and their value/weight
    cout << "\nList of Items:\n";
    cout << "Index | Value | Weight\n";
    cout << "-----------------------\n";
    for (int i = 0; i < n; i++)
    {
        cout << "  " << i + 1 << "   |   " << items[i].value << "   |   " << items[i].weight << endl;
    }
    cout << endl;

    double totalValue = knapsack(maxWeight, &items[0], n);
    cout << endl
         << "Maximum loot value: " << totalValue << endl;

    return 0;
}