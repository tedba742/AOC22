#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
    bool operator<(const Point& other) const {
        return tie(x, y) < tie(other.x, other.y);
    }
};

void parseInput(const string& filename, set<Point>& rocks, int& maxY) {
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string pointStr;
        vector<Point> points;
        
        while (getline(ss, pointStr, ' ')) {
            if (pointStr == "->") continue;
            replace(pointStr.begin(), pointStr.end(), ',', ' ');
            Point p;
            stringstream pointStream(pointStr);
            pointStream >> p.x >> p.y;
            points.push_back(p);
            maxY = max(maxY, p.y);
        }

        for (size_t i = 1; i < points.size(); ++i) {
            Point p1 = points[i - 1];
            Point p2 = points[i];
            if (p1.x == p2.x) {
                int yStart = min(p1.y, p2.y);
                int yEnd = max(p1.y, p2.y);
                for (int y = yStart; y <= yEnd; ++y) {
                    rocks.insert({p1.x, y});
                }
            } else if (p1.y == p2.y) {
                int xStart = min(p1.x, p2.x);
                int xEnd = max(p1.x, p2.x);
                for (int x = xStart; x <= xEnd; ++x) {
                    rocks.insert({x, p1.y});
                }
            }
        }
    }
}

int simulateSand(set<Point>& rocks, int maxY) {
    const Point source = {500, 0};
    int sandUnits = 0;
    set<Point> settledSand;

    while (true) {
        Point sand = source;
        while (true) {
            Point down = {sand.x, sand.y + 1};
            Point downLeft = {sand.x - 1, sand.y + 1};
            Point downRight = {sand.x + 1, sand.y + 1};
            
            if (down.y > maxY) return sandUnits;

            if (!rocks.count(down) && !settledSand.count(down)) {
                sand = down;
            } else if (!rocks.count(downLeft) && !settledSand.count(downLeft)) {
                sand = downLeft;
            } else if (!rocks.count(downRight) && !settledSand.count(downRight)) {
                sand = downRight;
            } else {
                settledSand.insert(sand);
                sandUnits++;
                break;
            }
        }
    }
}

int main() {
    set<Point> rocks;
    int maxY = 0;
    string filename = "input.txt";

    parseInput(filename, rocks, maxY);
    int result = simulateSand(rocks, maxY);
    cout << "Number of units of sand that come to rest: " << result << endl;
}
