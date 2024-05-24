#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <array>

struct Point {
    int x, y, z;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

// Custom hash function for Point to be used in unordered_set
struct PointHash {
    std::size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ std::hash<int>()(p.y) ^ std::hash<int>()(p.z);
    }
};

int main() {
    std::ifstream file{"input.txt"};
    std::unordered_set<Point, PointHash> cubes{};
    std::string line{""};

    while (std::getline(file, line)) {
        std::stringstream ss{line};
        Point cube{};
        char discard{};
        ss >> cube.x >> discard >> cube.y >> discard >> cube.z;
        cubes.insert(cube);
    }

    file.close();

    std::array<Point, 6> directions = {{
        {1, 0, 0}, {-1, 0, 0},
        {0, 1, 0}, {0, -1, 0},
        {0, 0, 1}, {0, 0, -1}
    }};

    int surfaceArea = 0;

    for (const auto& cube : cubes) {
        int exposedSides{6};
        for (const auto& dir : directions) {
            Point neighbor = {cube.x + dir.x, cube.y + dir.y, cube.z + dir.z};
            if (cubes.find(neighbor) != cubes.end()) {
                exposedSides--;
            }
        }
        surfaceArea += exposedSides;
    }

    std::cout << "Total surface area: " << surfaceArea << std::endl;

}
