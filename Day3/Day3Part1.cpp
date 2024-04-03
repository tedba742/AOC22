#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

std::string addMatchingCharacters(std::string part1, std::string part2){
    std::set<char> matchingCharacters{};
    std::set<char> set1{part1.begin(), part1.end()};
    std::set<char> set2{part2.begin(), part2.end()};
    std::string matchingCharactersString{};

    for (char ch : set1) {
        if (set2.find(ch) != set2.end()) {
            matchingCharacters.insert(ch);
        }
    }
                 
    for (char ch : matchingCharacters) {
        matchingCharactersString += ch;
    }

    return matchingCharactersString;
}

std::map<char, int> createAlphabetMap() {
    std::map<char, int> alphabetMap;
    char letter = 'a';
    int position = 1;

    while (letter <= 'z') {
        alphabetMap[letter] = position;
        ++letter;
        ++position;
    }

    letter = 'A';
    position = 27;

    while (letter <= 'Z') {
        alphabetMap[letter] = position;
        ++letter;
        ++position;
    }

    return alphabetMap;
}

int getValues(std::map<char,int> alphabetMap, std::string unionString){
    int totalValueOfString{0};
    for(auto c: unionString){
        if (alphabetMap.find(c) != alphabetMap.end()) { 
            totalValueOfString += alphabetMap[c]; 
        }

    }
    return totalValueOfString;
}
int main() {
    std::ifstream file("input.txt");
    std::string line;
    int totalScore{0};
    std::string matchingCharactersVector{};
    std::map<char, int> alphabetMap = createAlphabetMap();

    if (file.is_open()) {
        while (std::getline(file, line)) {
        size_t midpoint = line.length() / 2;
        std::string part1 = line.substr(0, midpoint);
        std::string part2 = line.substr(midpoint);
        std::string commonCharacters{addMatchingCharacters(part1, part2)};
        totalScore += getValues(alphabetMap, commonCharacters);
        }

        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

std::cout << "your total score was:" << totalScore << std::endl;

return 0;
}