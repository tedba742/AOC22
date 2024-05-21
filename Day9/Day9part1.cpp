#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ifstream inputFile("input.txt");
    pair<int, int> head = {0, 0};
    pair<int, int> tail = {0, 0};

    set<pair<int, int>> visitedPositions;
    visitedPositions.insert(tail);

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        char direction;
        int steps;
        ss >> direction >> steps;

        for (int i = 0; i < steps; ++i) {
            switch (direction) {
                case 'R': head.first += 1; break;
                case 'L': head.first -= 1; break;
                case 'U': head.second += 1; break;
                case 'D': head.second -= 1; break;
            }

            int dx = head.first - tail.first;
            int dy = head.second - tail.second;

            if (abs(dx) > 1 || abs(dy) > 1) {
                if (dx == 0) {
                    tail.second += (dy > 0) ? 1 : -1;
                } else if (dy == 0) {
                    tail.first += (dx > 0) ? 1 : -1;
                } else {
                    tail.first += (dx > 0) ? 1 : -1;
                    tail.second += (dy > 0) ? 1 : -1;
                }
            }

            visitedPositions.insert(tail);
        }
    }

    inputFile.close();

    cout << "Number of positions visited by the tail: " << visitedPositions.size() << endl;
}
