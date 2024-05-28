#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
    bool operator<(const Point& other) const {
        return tie(x, y) < tie(other.x, other.y);
    }
};

void parseInput(const string& filename, set<Point>& rocks, long long& maxY) {
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
                long long yStart = min(p1.y, p2.y);
                long long yEnd = max(p1.y, p2.y);
                for (long long y = yStart; y <= yEnd; ++y) {
                    rocks.insert({p1.x, y});
                }
            } else if (p1.y == p2.y) {
                long long xStart = min(p1.x, p2.x);
                long long xEnd = max(p1.x, p2.x);
                for (long long x = xStart; x <= xEnd; ++x) {
                    rocks.insert({x, p1.y});
                }
            }
        }
    }
}

int simulateSand(set<Point>& rocks, long long floorY) {
    const Point source = {500, 0};
    long long sandUnits = 0;
    set<Point> settledSand;

    while (!settledSand.count(source)) {
        Point sand = source;
        while (true) {
            Point down = {sand.x, sand.y + 1};
            Point downLeft = {sand.x - 1, sand.y + 1};
            Point downRight = {sand.x + 1, sand.y + 1};
            
            if (down.y == floorY) {
                settledSand.insert(sand);
                sandUnits++;
                break;
            } else if (!rocks.count(down) && !settledSand.count(down)) {
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

    return sandUnits;
}

int main() {
    set<Point> rocks;
    long long maxY = 0;
    string filename = "input.txt";
    parseInput(filename, rocks, maxY);

    long long floorY = maxY + 2;
    long long result = simulateSand(rocks, floorY);
    cout << "Number of units of sand that come to rest: " << result << endl;
}
