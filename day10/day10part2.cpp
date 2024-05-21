#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct Instruction {
    std::string type;
    int value;
};

std::vector<Instruction> readInstructions(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<Instruction> instructions;
    std::string line;

    while (std::getline(file, line)) {
        Instruction inst;
        if (line.substr(0, 4) == "noop") {
            inst.type = "noop";
            inst.value = 0;
        } else if (line.substr(0, 4) == "addx") {
            inst.type = "addx";
            inst.value = std::stoi(line.substr(5));
        }
        instructions.push_back(inst);
    }

    return instructions;
}

void renderCRT(const std::vector<std::vector<char>>& screen) {
    for (const auto& row : screen) {
        for (const auto& pixel : row) {
            std::cout << pixel;
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<Instruction> instructions = readInstructions("input.txt");

    int X = 1;
    int cycle = 0;
    const int width = 40;
    const int height = 6;
    std::vector<std::vector<char>> screen(height, std::vector<char>(width, '.'));

    for (const auto &inst : instructions) {
        if (inst.type == "noop") {
            int row = cycle / width;
            int col = cycle % width;
            if (col >= X - 1 && col <= X + 1) {
                screen[row][col] = '#';
            }
            cycle += 1;
        } else if (inst.type == "addx") {
            for (int i = 0; i < 2; ++i) {
                int row = cycle / width;
                int col = cycle % width;
                if (col >= X - 1 && col <= X + 1) {
                    screen[row][col] = '#';
                }
                cycle += 1;
            }
            X += inst.value;
        }
    }

    renderCRT(screen);

}
