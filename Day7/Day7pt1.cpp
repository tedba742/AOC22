#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>

// Structure to represent a graph node
struct Node {
    std::string fileName;
    long fileSize; // Add a long member variable for file size
    std::vector<Node*> neighbors;

    Node(std::string filename, long size) : fileName(filename), fileSize(size) {}
};

// Graph class
class Graph {
private:
    std::vector<Node*> nodes;

public:
    // Add a node to the graph
    void addNode(std::string filename, long size) {
        Node* newNode = new Node(filename, size);
        nodes.push_back(newNode);
    }

    // Add an edge between two nodes
    void addEdge(std::string from, std::string to) {
        Node* fromNode = findNode(from);
        Node* toNode = findNode(to);

        if (fromNode && toNode) {
            fromNode->neighbors.push_back(toNode);
            toNode->neighbors.push_back(fromNode); // If it's an undirected graph
        }
    }

    Node* findNode(std::string filename) {
        for (Node* node : nodes) {
            if (node->fileName == filename) {
                return node;
            }
        }
        return nullptr;
    }

    
    Node* findNodePointingTo(std::string filename) {
        Node* currentNode = findNode(filename);

        if (currentNode) {
            for (Node* node : nodes) {
                for (Node* neighbor : node->neighbors) {
                    if (neighbor == currentNode) {
                        return node;
                    }
                }
            }
        }

        return nullptr;
    }

    void printNodesWithSmallNeighbors(long threshold) {
        long size {0};
        for (Node* node : nodes) {
            if (node->fileSize < 100000){
                size += node->fileSize;
                std::cout << node->fileSize << std::endl;
            }
        }
        std::cout << "Sum of sizes " << size << std::endl;
    }

    // Print the graph
    void print() {
        for (Node* node : nodes) {
            std::cout << "Node " << node->fileName << " (Size: " << node->fileSize << ") connects to: ";
            for (Node* neighbor : node->neighbors) {
                std::cout << neighbor->fileName << " ";
            }
            std::cout << std::endl;
        }
    }
};

std::string getCurrentDirectory(std::string in, std::string previousPosition, Graph& graph) {
    std::string directory = in;
    std::regex pattern{"cd"};
    std::smatch match;
    if (std::regex_search(directory, match, pattern)) {
        size_t pos = directory.rfind(' ');
        directory = directory.substr(pos);
        if (directory == "..") {
            Node* parentNode = graph.findNodePointingTo(previousPosition);
            if (parentNode) {
                return parentNode->fileName;
            }
        }
        return directory;
    }
    return previousPosition;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<std::string> in;
    Graph graph;
    std::string root{"/"};
    graph.addNode("/", 0); // Set file size to 0 initially

    std::string directory{""};
    while (std::getline(file, line)) {
        in.push_back(line);
        root = getCurrentDirectory(line, root, graph);
        std::regex pattern{"dir"};
        std::smatch match;
        if (std::regex_search(line, match, pattern)) {
            size_t pos = line.find(' ');
            directory = line.substr(pos);
            graph.addNode(directory, 0); // Set file size to 0 initially
            graph.addEdge(root, directory);
        } else if(std::isdigit(line[0])){
            size_t pos = line.find(' ');
            long fileSize = std::stol(line.substr(0, pos)); // Convert string to long
            std::string fileName = line.substr(pos);
            graph.addNode(fileName, fileSize); // Add node with file size
            graph.addEdge(root, fileName); // Use fileName as the source node
        } else {
            std::regex pattern1("\\b(?:[1-9]\\d{0,6}|1000000)\\b");
            std::smatch match1;
            if (std::regex_search(line, match1, pattern1)) {
                size_t pos1 = line.find(' ');
                directory = line.substr(pos1);
                graph.addNode(directory, 0); // Set file size to 0 initially
                graph.addEdge(root, directory);
            }
        }
    }

    graph.print();

    std::cout << "Nodes with neighbors having size less than 100000:" << std::endl;
    graph.printNodesWithSmallNeighbors(100000);
    return 0;
}
