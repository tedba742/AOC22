#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void updateKnots(vector<pair<int, int>>& knots) {
    for (int i = 1; i < knots.size(); ++i) {
        int dx = knots[i-1].first - knots[i].first;
        int dy = knots[i-1].second - knots[i].second;

        if (abs(dx) > 1 || abs(dy) > 1) {
            if (dx == 0) {
                knots[i].second += (dy > 0) ? 1 : -1;
            } else if (dy == 0) {
                knots[i].first += (dx > 0) ? 1 : -1;
            } else {
                knots[i].first += (dx > 0) ? 1 : -1;
                knots[i].second += (dy > 0) ? 1 : -1;
            }
        }
    }
}

int main() {
    ifstream inputFile("input.txt");
    vector<pair<int, int>> knots(10, {0, 0});

    set<pair<int, int>> visitedPositions;
    visitedPositions.insert(knots.back());

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        char direction;
        int steps;
        ss >> direction >> steps;

        for (int i = 0; i < steps; ++i) {
            switch (direction) {
                case 'R': knots[0].first += 1; break;
                case 'L': knots[0].first -= 1; break;
                case 'U': knots[0].second += 1; break;
                case 'D': knots[0].second -= 1; break;
            }

            updateKnots(knots);

            visitedPositions.insert(knots.back());
        }
    }

    inputFile.close();

    cout << "Number of positions visited by the tail: " << visitedPositions.size() << endl;

    return 0;
}