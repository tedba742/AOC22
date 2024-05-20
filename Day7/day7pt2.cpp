#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <fstream>
#include <limits>

struct Node {
    std::string name;
    int size; // 0 for directories
    bool isDirectory;
    std::vector<Node*> children;

    Node(std::string n, int s, bool isDir) : name(n), size(s), isDirectory(isDir) {}
};

Node* buildFileSystemTree(const std::vector<std::string>& input) {
    Node* root = new Node("/", 0, true);
    std::unordered_map<std::string, Node*> pathMap;
    pathMap["/"] = root;
    Node* current = root;

    for (const std::string& line : input) {
        if (line[0] == '$') {
            if (line.substr(0, 5) == "$ cd ") {
                std::string dir = line.substr(5);
                if (dir == "/") {
                    current = root;
                } else if (dir == "..") {
                    size_t pos = current->name.find_last_of('/');
                    current = pathMap[current->name.substr(0, pos)];
                } else {
                    current = pathMap[current->name + "/" + dir];
                }
            }
        } else if (line.substr(0, 4) == "dir ") {
            std::string dirName = line.substr(4);
            Node* newDir = new Node(current->name + "/" + dirName, 0, true);
            current->children.push_back(newDir);
            pathMap[newDir->name] = newDir;
        } else {
            std::stringstream ss(line);
            int size;
            std::string fileName;
            ss >> size >> fileName;
            Node* newFile = new Node(current->name + "/" + fileName, size, false);
            current->children.push_back(newFile);
        }
    }

    return root;
}

int calculateDirectorySizes(Node* node, std::unordered_map<std::string, int>& dirSizes) {
    if (!node->isDirectory) return node->size;

    int totalSize = 0;
    for (Node* child : node->children) {
        totalSize += calculateDirectorySizes(child, dirSizes);
    }
    dirSizes[node->name] = totalSize;
    return totalSize;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::vector<std::string> input;
    std::string line;
    while (getline(inputFile, line)) {
        input.push_back(line);
    }
    inputFile.close();

    Node* root = buildFileSystemTree(input);

    std::unordered_map<std::string, int> dirSizes;
    int totalUsedSpace = calculateDirectorySizes(root, dirSizes);

    const int totalDiskSpace = 70000000;
    const int requiredFreeSpace = 30000000;
    int currentFreeSpace = totalDiskSpace - totalUsedSpace;
    int neededSpaceToFree = requiredFreeSpace - currentFreeSpace;

    int smallestSufficientDirSize = std::numeric_limits<int>::max();
    for (const auto& pair : dirSizes) {
        if (pair.second >= neededSpaceToFree && pair.second < smallestSufficientDirSize) {
            smallestSufficientDirSize = pair.second;
        }
    }

    std::cout << "Total size of the smallest sufficient directory: " << smallestSufficientDirSize << std::endl;
}
