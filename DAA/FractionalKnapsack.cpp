// Time Complexity: O(nlogn)
// Space Complexity: O(n)

#include <bits/stdc++.h>
using namespace std;

class Item {
public:
    int weight;
    int profit;
    double ratio;

    Item(int w, int p) : weight(w), profit(p) {
        ratio = static_cast<double>(p) / w; 
    }
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio; 
}

double calculateMaxProfit(vector<Item>& items, int capacity) {
    double totalValue = 0.0;

    cout<<"Weight \t Profit \t Profit_taken "<<endl;
    for (int i = 0; i < items.size(); i++) {
        double taken=0.0;
        if (capacity == 0) {
            break; 
        }

        if (capacity >= items[i].weight) {
            capacity -= items[i].weight;
            taken=items[i].profit;
            totalValue += items[i].profit;
        } else {
            taken=capacity * items[i].ratio;
            totalValue += capacity * items[i].ratio; 
            capacity = 0; 
        }
        cout<<items[i].weight<<"\t"<<items[i].profit<<"\t"<<taken<<endl;
    }
    return totalValue;
}

int main() {
    int n;
    cout << "Enter the total number of items: ";
    cin >> n; 

    vector<Item> items;

    for (int i = 0; i < n; i++) {
        int w, p;
        cout << "Enter weight for item " << i + 1 << ": ";
        cin >> w;
        cout << "Enter profit for item " << i + 1 << ": ";
        cin >> p;
        items.emplace_back(w, p);
    }

    int capacity;
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    sort(items.begin(), items.end(), compare);

    double maxProfit = calculateMaxProfit(items, capacity);
    cout << "Maximum profit: " << maxProfit << endl;

    return 0;
}

