#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <array>

const int CHAMBER_WIDTH = 7;
const int NUM_ROCKS = 2022;

using Point = std::pair<int, int>;

const std::vector<std::vector<Point>> rockShapes = {
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
    {{1, 0}, {0, 1}, {1, 1}, {2, 1}, {1, 2}},
    {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}},
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}}
};

std::vector<Point> getRockPosition(const std::vector<Point>& shape, int x, int y) {
    std::vector<Point> positions;
    for (const auto& p : shape) {
        positions.emplace_back(x + p.first, y + p.second);
    }
    return positions;
}

bool canMove(const std::vector<Point>& rock, const std::set<Point>& settledRocks, int dx, int dy) {
    for (const auto& p : rock) {
        int nx = p.first + dx;
        int ny = p.second + dy;
        if (nx < 0 || nx >= CHAMBER_WIDTH || ny < 0 || settledRocks.count({nx, ny}) > 0) {
            return false;
        }
    }
    return true;
}

void addRock(std::set<Point>& settledRocks, const std::vector<Point>& rock) {
    for (const auto& p : rock) {
        settledRocks.insert(p);
    }
}

int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::string jetPattern;
    std::getline(file, jetPattern);
    file.close();

    std::set<Point> settledRocks;
    int currentHeight = 0;
    int jetIndex = 0;

    for (int i = 0; i < NUM_ROCKS; ++i) {
        const auto& shape = rockShapes[i % rockShapes.size()];
        int x = 2;
        int y = currentHeight + 3;

        while (true) {
            // Use jet push
            char jet = jetPattern[jetIndex % jetPattern.size()];
            jetIndex++;
            int dx = (jet == '>') ? 1 : -1;

            auto rock = getRockPosition(shape, x, y);
            if (canMove(rock, settledRocks, dx, 0)) {
                x += dx;
            }

            // Rock goes down
            rock = getRockPosition(shape, x, y);
            if (canMove(rock, settledRocks, 0, -1)) {
                y -= 1;
            } else {
                addRock(settledRocks, rock);
                for (const auto& p : rock) {
                    if (p.second + 1 > currentHeight) {
                        currentHeight = p.second + 1;
                    }
                }
                break;
            }
        }
    }

    std::cout << "Height of the tower after " << NUM_ROCKS << " rocks: " << currentHeight << " units" << std::endl;
}
