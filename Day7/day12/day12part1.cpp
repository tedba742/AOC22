#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <fstream>
#include <string>

using namespace std;

struct Position {
    int row;
    int col;
    int steps;
};

bool isValidMove(vector<string>& grid, vector<vector<bool>>& visited, int newRow, int newCol, int currentElevation) {
    if (newRow < 0 || newRow >= grid.size() || newCol < 0 || newCol >= grid[0].size()) {
        return false;
    }
    if (visited[newRow][newCol]) {
        return false;
    }
    int newElevation = (grid[newRow][newCol] == 'E') ? 25 : grid[newRow][newCol] - 'a';
    if (newElevation > currentElevation + 1) {
        return false;
    }
    return true;
}

int findShortestPath(vector<string>& grid, Position start, Position end) {
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    queue<Position> q;
    q.push(start);
    visited[start.row][start.col] = true;
    
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty()) {
        Position current = q.front();
        q.pop();

        if (current.row == end.row && current.col == end.col) {
            return current.steps;
        }

        int currentElevation = (grid[current.row][current.col] == 'S') ? 0 : grid[current.row][current.col] - 'a';
        
        for (auto& dir : directions) {
            int newRow = current.row + dir.first;
            int newCol = current.col + dir.second;
            
            if (isValidMove(grid, visited, newRow, newCol, currentElevation)) {
                visited[newRow][newCol] = true;
                q.push({newRow, newCol, current.steps + 1});
            }
        }
    }
    return -1;
}

vector<string> readInputFromFile(const string& filename) {
    ifstream inputFile(filename);
    vector<string> input;
    string line;
    while (getline(inputFile, line)) {
        input.push_back(line);
    }
    inputFile.close();

    return input;
}

int main() {
    try {
        vector<string> grid = readInputFromFile("input.txt");
        Position start, end;

        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] == 'S') {
                    start = {i, j, 0};
                } else if (grid[i][j] == 'E') {
                    end = {i, j, 0};
                }
            }
        }

        int shortestPath = findShortestPath(grid, start, end);

        if (shortestPath != -1) {
            cout << "The fewest steps required: " << shortestPath << endl;
        } else {
            cout << "No valid path found." << endl;
        }

    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
