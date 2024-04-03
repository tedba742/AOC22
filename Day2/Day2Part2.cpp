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

// X = need to lose
// Y = need to draw
// Z == need to win

int getItemWeShouldUse(char a, char b){
    if(b == 'X'){
        if(a == 'A'){
            return SCISSORS + LOSS;     
        } else if(a =='B'){
            return ROCK + LOSS;
        } else {
            return PAPER + LOSS;
        }
    } else if(b == 'Y'){
        if(a == 'A'){
            return ROCK + DRAW;     
        } else if(a =='B'){
            return PAPER + DRAW;
        } else {
            return SCISSORS + DRAW;
        }    
    } else {
        if(a == 'A'){
            return PAPER + WIN;     
        } else if(a =='B'){
            return SCISSORS + WIN;
        } else {
            return ROCK + WIN;
        }        
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
            totalScore += getItemWeShouldUse(line[0], line[2]);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

std::cout << "your total score was:" << totalScore << std::endl;
  
    return 0;
}
