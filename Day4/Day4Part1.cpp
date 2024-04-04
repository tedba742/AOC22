#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> splitString(const std::string& str, const std::string& delimiters) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = 0;

    while ((end = str.find_first_of(delimiters, start)) != std::string::npos) {
        if (end != start) {
            tokens.push_back(str.substr(start, end - start));
        }
        start = end + 1;
    }

    if (start < str.length()) {
        tokens.push_back(str.substr(start));
    }

    return tokens;
}

std::vector<std::string> getRanges(const std::string& line) {
    std::string range;
    std::string delimiters = "-,"; 
    std::stringstream ss(line); 
    std::vector<std::string> ranges = splitString(line, delimiters);


    return ranges;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
    int totalScore = 0;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::vector<std::string> ranges = getRanges(line);

            int range1_start = std::stoi(ranges[0]);
            int range1_end = std::stoi(ranges[1]);
            int range2_start = std::stoi(ranges[2]);
            int range2_end = std::stoi(ranges[3]);

            if (range1_start <= range2_start && range1_end >= range2_end) {
                totalScore++;
            }
            else if (range1_start >= range2_start && range1_end <= range2_end) {
                totalScore++;
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    std::cout << "Your total score was: " << totalScore << std::endl;
    return 0;
}
