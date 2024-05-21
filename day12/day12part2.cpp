#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct Position {
    int row;
    int col;
    int steps;
};

vector<pair<int, int>> getNeighbors(int row, int col, int rows, int cols) {
    vector<pair<int, int>> neighbors;
    if (row > 0) neighbors.emplace_back(row - 1, col);
    if (row < rows - 1) neighbors.emplace_back(row + 1, col);
    if (col > 0) neighbors.emplace_back(row, col - 1);
    if (col < cols - 1) neighbors.emplace_back(row, col + 1);
    return neighbors;
}

int bfs(const vector<string>& heightmap, const vector<Position>& startPositions, Position endPosition) {
    int rows = heightmap.size();
    int cols = heightmap[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<Position> q;

    for (const auto& start : startPositions) {
        q.push(start);
        visited[start.row][start.col] = true;
    }

    while (!q.empty()) {
        Position current = q.front();
        q.pop();

        if (current.row == endPosition.row && current.col == endPosition.col) {
            return current.steps;
        }

        for (const auto& neighbor : getNeighbors(current.row, current.col, rows, cols)) {
            int newRow = neighbor.first;
            int newCol = neighbor.second;
            if (!visited[newRow][newCol] &&
                heightmap[newRow][newCol] <= heightmap[current.row][current.col] + 1) {
                q.push({newRow, newCol, current.steps + 1});
                visited[newRow][newCol] = true;
            }
        }
    }

    return -1; // If there is no path found
}

int main() {
    ifstream inputFile("input.txt");
    vector<string> heightmap;
    string line;
    Position startPos, endPos;
    vector<Position> startPositions;

    int row = 0;
    while (getline(inputFile, line)) {
        heightmap.push_back(line);
        for (int col = 0; col < line.size(); ++col) {
            if (line[col] == 'S') {
                startPos = {row, col, 0};
                startPositions.push_back(startPos);
                heightmap[row][col] = 'a'; // Treat 'S' as elevation 'a'
            }
            if (line[col] == 'E') {
                endPos = {row, col, 0};
                heightmap[row][col] = 'z'; // Treat 'E' as elevation 'z'
            }
            if (line[col] == 'a') {
                startPositions.push_back({row, col, 0});
            }
        }
        ++row;
    }

    int shortestPath = bfs(heightmap, startPositions, endPos);

    cout << "Shortest path from any 'a' to 'E': " << shortestPath << endl;

    return 0;
}
