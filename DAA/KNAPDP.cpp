#include <iostream>
#include <vector>

using namespace std;
struct Item
{
    int profit;
    int weight;
};
int knapsackDP(vector<Item> &items, int capacity, vector<vector<int>> &dp)
{
    int n = items.size();
    for (int i = 1; i <= n; i++)
    {
        for (int w = 1; w <= capacity; w++)
        {
            if (items[i - 1].weight <= w)
            {
                dp[i][w] = max(items[i - 1].profit + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][capacity];
}

void printItems(vector<Item> items)
{
    cout << "Item\tProfit\tWeight" << endl;
    for (int i=0; i < items.size(); i++)
    {
        cout << i + 1 << "\t" << items[i].profit << "\t" << items[i].weight << endl;
    }
    cout << endl;
}
int main()
{
    int capacity, n;
    cout << "Enter capacity of knapsack:" << endl;
    cin >> capacity;
    cout << "How many total items?" << endl;
    cin >> n;
    vector<Item> items;
    for (int i = 0; i < n; i++)
    {
        Item item;
        cout << "Enter Profit of item " << i + 1 << endl;
        cin >> item.profit;
        cout << "Enter weight of item " << i + 1 << endl;
        cin >> item.weight;
        items.push_back(item);
    }
    cout << "\nAvailable Items :" << endl;
    printItems(items);
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    int maxProfit = knapsackDP(items, capacity, dp);
    cout << "Maximum profit: " << maxProfit << endl;
    return 0;
}