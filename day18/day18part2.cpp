#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>

struct Point {
    int x, y, z;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct PointHash {
    std::size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ std::hash<int>()(p.y) ^ std::hash<int>()(p.z);
    }
};

std::vector<Point> directions = {
    {1, 0, 0}, {-1, 0, 0},
    {0, 1, 0}, {0, -1, 0},
    {0, 0, 1}, {0, 0, -1}
};

bool isValid(const Point& p, const Point& minBound, const Point& maxBound) {
    return p.x >= minBound.x && p.x <= maxBound.x &&
           p.y >= minBound.y && p.y <= maxBound.y &&
           p.z >= minBound.z && p.z <= maxBound.z;
}

void floodFill(const Point& start, const std::unordered_set<Point, PointHash>& cubes, 
               std::unordered_set<Point, PointHash>& visited, const Point& minBound, const Point& maxBound) {
    std::queue<Point> q;
    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        for (const auto& dir : directions) {
            Point neighbor = {current.x + dir.x, current.y + dir.y, current.z + dir.z};
            if (isValid(neighbor, minBound, maxBound) && 
                cubes.find(neighbor) == cubes.end() && 
                visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
}

int main() {
    std::ifstream file("input.txt");
    std::unordered_set<Point, PointHash> cubes;
    std::string line;

    Point minBound = {std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};
    Point maxBound = {std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), std::numeric_limits<int>::min()};

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Point cube;
        char discard;
        ss >> cube.x >> discard >> cube.y >> discard >> cube.z;
        cubes.insert(cube);

        minBound.x = std::min(minBound.x, cube.x);
        minBound.y = std::min(minBound.y, cube.y);
        minBound.z = std::min(minBound.z, cube.z);
        maxBound.x = std::max(maxBound.x, cube.x);
        maxBound.y = std::max(maxBound.y, cube.y);
        maxBound.z = std::max(maxBound.z, cube.z);
    }

    file.close();

    minBound = {minBound.x - 1, minBound.y - 1, minBound.z - 1};
    maxBound = {maxBound.x + 1, maxBound.y + 1, maxBound.z + 1};

    std::unordered_set<Point, PointHash> visited;
    floodFill(minBound, cubes, visited, minBound, maxBound);

    int exteriorSurfaceArea = 0;

    for (const auto& cube : cubes) {
        for (const auto& dir : directions) {
            Point neighbor = {cube.x + dir.x, cube.y + dir.y, cube.z + dir.z};
            if (visited.find(neighbor) != visited.end()) {
                exteriorSurfaceArea++;
            }
        }
    }

    std::cout << "Exterior surface area: " << exteriorSurfaceArea << std::endl;
}
