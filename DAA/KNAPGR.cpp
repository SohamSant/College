#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item
{
    int wt;
    int prof;
    double ratio;
};

bool compare (Item a, Item b)
{
    return a.ratio > b.ratio;
}

float frac_knapsack (vector<Item> items, int cap, int n)
{
    double profit = 0;

    for (int i=0; i<n; i++)
    {
        if (items[i].wt <= cap)
        {
            cap -= items[i].wt;
            profit += items[i].prof;
        }
        else
        {
            double frac = (double) cap/items[i].wt;
            profit += frac * items[i].prof;
            break;
        }
    }
    return profit;
}

int main ()
{
    int n, cap;
    cout << "Enter no. of items: ";
    cin >> n;

    cout << "Enter capacity of knapsack: ";
    cin >> cap;

    vector<Item> items (n);
    cout << endl << "Enter weight and values->" << endl;
    for (int i=0; i<n; i++)
    {
        cout << endl << "Weight of item " << i+1 << ": ";
        cin >> items[i].wt;

        cout << "Profit of item " << i+1 << ": ";
        cin >> items[i].prof;

        items[i].ratio = (float) items[i].prof / items[i].wt;
    }

    sort (items.begin(), items.end(), compare);

    float profit = frac_knapsack (items, cap, n);
    cout << endl << "Maximum possible profit is: " << profit;

    return 0;
}