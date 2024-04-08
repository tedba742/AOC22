#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <stack>
#include <regex>

int main() {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<std::string> in;

    while(std::getline(file, line) && line[1] != '1') {
        in.push_back(line);
    }

    std::vector<std::stack<char>> stacks(line.size() / 4 + 1);
    for (int i = in.size() - 1; i >= 0; i--) {
        for (int j = 0; j < stacks.size(); j++) {
            const int k = j * 4 + 1;
            if (in[i][k] == ' ') continue;
            stacks[j].push(in[i][k]);
        }
    }

    std::getline(file, line);
    const std::regex pattern("move ([0-9]+) from ([0-9]+) to ([0-9]+)");
    while (std::getline(file, line)) {
        std::smatch match;
        std::regex_match(line, match, pattern);
        auto n = std::stoi(match[1]);
        const auto from = std::stoi(match[2]) - 1;
        const auto to = std::stoi(match[3]) - 1;
        std::vector<char> charsToStack{};    
        for (int i = 0; i < n; i++) {
            charsToStack.push_back(stacks[from].top());
            stacks[from].pop();
        }

        std::reverse(begin(charsToStack), end(charsToStack));
        for (char c : charsToStack) {
            stacks[to].push(c);
        }
        charsToStack.clear();
    }

    for (const auto& stack : stacks) {
        if (!stack.empty()) {
            std::cout << stack.top();
        }
    }

    return 0;
}
