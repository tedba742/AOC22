#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>

enum scoreValues {
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3,
    WIN = 6,
    LOSS = 0,
    DRAW = 3 
};

int getWhatWasUsedDuringDraw(char a){
    switch (a) {
        case 'A':
            return ROCK;
        case 'B':
            return PAPER;
        case 'C':
            return SCISSORS;
        default:
            return 0;
    }
}

bool isEqual(char a, char b){
    if (a == 'A' && b == 'X'){
        return true;
    } else if (a == 'B' && b == 'Y') {
        return true;
    } else if (a == 'C' && b == 'Z') {
        return true;
    } 

    return false;
}
int getScore(char a, char b){
    if (isEqual(a, b)){
        return DRAW + getWhatWasUsedDuringDraw(a);
    } else if (a == 'A' && b == 'Z'){ 
        return LOSS + SCISSORS;
    } else if (a == 'C' && b == 'X' ){
        return WIN + ROCK;
    } else if (a == 'B' && b == 'X'){
        return LOSS + ROCK;
    } else if (a == 'A' && b == 'X' ){
        return WIN + ROCK;
    } else if (a == 'C' && b == 'Y'){
        return LOSS + PAPER;
    } else if (a == 'B' && b == 'Z' ){
        return WIN + SCISSORS;
    } else if (a == 'A' && b == 'Y' ){
        return WIN + PAPER;
    } 
    return 0;
} 

int main() {
    std::ifstream file("input.txt");
    std::string line;
    int totalScore{0};
    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::cout << line[0] << std::endl;
            totalScore += getScore(line[0], line[2]);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

std::cout << "your total score was:" << totalScore << std::endl;
  
    return 0;
}