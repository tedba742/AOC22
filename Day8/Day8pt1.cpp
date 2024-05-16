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

// Function to count visible trees
int countVisibleTrees(const std::vector<std::vector<int>> &grid) {
    int visibleCount = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    // Check visibility for all edge trees
    visibleCount += 2 * (rows + cols - 2); // All edge trees are visible

    // Check visibility for interior trees
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            int height = grid[i][j];
            bool visible = true;

            // Check left
            for (int k = 0; k < j; ++k) {
                if (grid[i][k] >= height) {
                    visible = false;
                    break;
                }
            }
            if (visible) {
                visibleCount++;
                continue;
            }

            visible = true;
            // Check right
            for (int k = j + 1; k < cols; ++k) {
                if (grid[i][k] >= height) {
                    visible = false;
                    break;
                }
            }
            if (visible) {
                visibleCount++;
                continue;
            }

            visible = true;
            // Check up
            for (int k = 0; k < i; ++k) {
                if (grid[k][j] >= height) {
                    visible = false;
                    break;
                }
            }
            if (visible) {
                visibleCount++;
                continue;
            }

            visible = true;
            // Check down
            for (int k = i + 1; k < rows; ++k) {
                if (grid[k][j] >= height) {
                    visible = false;
                    break;
                }
            }
            if (visible) {
                visibleCount++;
            }
        }
    }

    return visibleCount;
}

int main() {

    std::vector<std::vector<int>> grid = readGrid("input.txt");
    int visibleTrees = countVisibleTrees(grid);

    MyTemplate<int> resultObj(visibleTrees);
    resultObj.display();
}
