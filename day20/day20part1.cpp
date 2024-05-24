#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

vector<int> parseInput(const string& filename) {
    vector<int> numbers;
    ifstream file(filename);
    int num;

    while (file >> num) {
        numbers.push_back(num);
    }

    return numbers;
}

void mixFile(vector<int>& numbers) {
    int n = numbers.size();
    deque<pair<int, int>> mixed;  // pair of (original position, number)

    for (int i = 0; i < n; ++i) {
        mixed.push_back({i, numbers[i]});
    }

    for (int i = 0; i < n; ++i) {
        auto it = find_if(mixed.begin(), mixed.end(), [i](const pair<int, int>& p) { return p.first == i; });
        int num = it->second;
        int pos = distance(mixed.begin(), it);
        mixed.erase(it);

        int newPos = (pos + num) % (n - 1);
        if (newPos < 0) newPos += (n - 1);

        mixed.insert(mixed.begin() + newPos, {i, num});
    }

    // Extract the numbers in their new order
    for (int i = 0; i < n; ++i) {
        numbers[i] = mixed[i].second;
    }
}

int findGroveCoordinates(const vector<int>& numbers) {
    int zeroPos = find(numbers.begin(), numbers.end(), 0) - numbers.begin();
    int size = numbers.size();

    int grove1 = numbers[(zeroPos + 1000) % size];
    int grove2 = numbers[(zeroPos + 2000) % size];
    int grove3 = numbers[(zeroPos + 3000) % size];

    return grove1 + grove2 + grove3;
}

int main() {
    string filename = "input.txt";
    vector<int> numbers = parseInput(filename);

    mixFile(numbers);

    int result = findGroveCoordinates(numbers);
    cout << "Sum of the grove coordinates: " << result << endl;

}
