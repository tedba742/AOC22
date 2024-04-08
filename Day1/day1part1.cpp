#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

int main() {
    std::ifstream file("input.txt");
    std::string line;
    int maximumWeight{0};
    int currentElfCaloryCount{0};

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (!line.empty() && !std::isspace(line[0])) {
                currentElfCaloryCount += std::stoi(line);
            } else {
                if (currentElfCaloryCount > maximumWeight) {
                    maximumWeight = currentElfCaloryCount;
                }
                currentElfCaloryCount = 0;
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    std::cout << "The elf carrying most calories is carrying: " << maximumWeight << std::endl;
    return 0;
}
