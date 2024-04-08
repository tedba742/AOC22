#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <set>

int solve(std::string line, int j){
    
    for(int i=0;i<line.size()-j;i++){
            if(std::set<char>(line.begin()+i,line.begin()+i+j).size() == j){
                return i + j;
            }
    }
    return -1;
}

int main(){
    std::ifstream file("input.txt");
    std::string line;
    std::getline(file, line);
    int index{0};
    std::cout << solve(line, 4) << std::endl;

    }

