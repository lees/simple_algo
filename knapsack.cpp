#include <iostream>
#include <vector>

using namespace std;

// vector<string> split_string(string);

class Knapsack {
    private:
        int W;
        int** data;
        vector<int> arr;

    public:
        Knapsack(int k, vector<int> arr) {
            W = k;
            this->arr = arr;
            data = new int*[arr.size()];
            for (size_t i=0; i < arr.size(); i++) {
                data[i] = new int[k+1];
            }
        }

        int solve() {
            for (size_t i=0; i < arr.size(); i ++) {
                int* line = data[i];
                int item_w = arr[i];
                line[0] = 0;
                for (int w = 1; w <= W; w++) {
                    line[w] = 0;
                    if (item_w <= w) {
                        line[w] = line[w-item_w] + item_w;
                    }
                    if (i > 0 && data[i-1][w] > line[w]) {
                        line[w] = data[i-1][w];
                    }
                }
            }
            return data[arr.size() - 1][W];
        }

};

void tests() {
    vector<int> arr = { 1, 6, 9 };
    auto knp = Knapsack(12, arr);
    assert((knp.solve() == 12));

    arr = { 3, 4, 8 };
    knp = Knapsack(9, arr);
    assert((knp.solve() == 9));

    knp = Knapsack(12, arr);
    assert((knp.solve() == 12));
    
    knp = Knapsack(2, arr);
    assert((knp.solve() == 0));
    
    knp = Knapsack(15, arr);
    assert((knp.solve() == 15));

    arr = { 2, 6, 8 };
    knp = Knapsack(21, arr);
    assert((knp.solve() == 20));
}


int main()
{
    // vector<int> arr = { 1, 6, 9 };
    // auto knp = Knapsack(12, arr);
    // cout << knp.solve() << endl;
    tests();
    // vector<int> arr = { 3, 4, 4, 4, 8 };
    // auto knp = Knapsack(2, arr);
    // cout << knp.solve() << endl;
    return 0;
}