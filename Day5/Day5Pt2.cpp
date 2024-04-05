#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <sstream>

void moveObjects(std::vector<int> numbers, std::vector<std::vector<char>> ranges){
std::cout << numbers[0] << " "<< numbers[1] << " "<< numbers[2] << std::endl;
    for (const auto& range : ranges) {
        for (char c : range) {
            if(c!= '!'){
                std::cout << "t";
            }
        }
    }
}
int main() {
    std::ifstream file("input.txt");
    std::string line;
    int totalScore = 0;
    std::vector<std::vector<char>> ranges(9);

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (!line.empty()) {
                int index = 0;
                for (char c : line) {
                    if (std::isalpha(c)) {
                        ranges[(index / 4)].push_back(c);
                    }
                    index++;
                } 
            } else{
                  for (auto& range : ranges) {
                    std::reverse(range.begin(), range.end());
            }
            std::istringstream iss(line);
    int num;
    std::vector<int> numbers;
    while (iss >> num) {
        std::cout << "test "<< std::endl;

        numbers.push_back(num);
    }
     moveObjects(numbers, ranges);
        } }
        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    // Print the contents of ranges
    for (const auto& range : ranges) {
        for (char c : range) {
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << "Your total score was: " << totalScore << std::endl;
    return 0;
}