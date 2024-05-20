#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

template<typename T>
class MyTemplate {
private:
    T data;

public:
    MyTemplate(T _data) : data(_data) {}

    void display() {
        std::cout << "Data: " << data << std::endl;
    }
};

std::vector<std::vector<int>> readGrid(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> grid;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char ch : line) {
            row.push_back(ch - '0');
        }
        grid.push_back(row);
    }
    return grid;
}

int calculateScenicScore(const std::vector<std::vector<int>>& grid, int row, int col) {
    int height = grid[row][col];
    int up = 0, down = 0, left = 0, right = 0;

    // Look up
    for (int i = row - 1; i >= 0; --i) {
        if (grid[i][col] >= height) {
            up++;
            break;
        }
        up++;
    }

    // Look down
    for (int i = row + 1; i < grid.size(); ++i) {
        if (grid[i][col] >= height) {
            down++;
            break;
        }
        down++;
    }

    // Look left
    for (int j = col - 1; j >= 0; --j) {
        if (grid[row][j] >= height) {
            left++;
            break;
        }
        left++;
    }

    // Look right
    for (int j = col + 1; j < grid[0].size(); ++j) {
        if (grid[row][j] >= height) {
            right++;
            break;
        }
        right++;
    }

    return up * down * left * right;
}

int main() {
    std::vector<std::vector<int>> grid = readGrid("input.txt");

    int maxScenicScore = 0;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            int scenicScore = calculateScenicScore(grid, i, j);
            if (scenicScore > maxScenicScore) {
                maxScenicScore = scenicScore;
            }
        }
    }

    MyTemplate<int> resultObj(maxScenicScore);
    resultObj.display();

    return 0;
}
