#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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

int main() {
    std::vector<Instruction> instructions = readInstructions("input.txt");

    int X = 1;
    int cycle = 0;
    int signalStrengthSum = 0;
    std::vector<int> signalCycles = {20, 60, 100, 140, 180, 220};
    size_t signalIndex = 0;

    for (const auto &inst : instructions) {
        if (inst.type == "noop") {
            cycle += 1;
            if (signalIndex < signalCycles.size() && cycle == signalCycles[signalIndex]) {
                signalStrengthSum += cycle * X;
                signalIndex++;
            }
        } else if (inst.type == "addx") {
            cycle += 2;
            if (signalIndex < signalCycles.size() && cycle - 1 == signalCycles[signalIndex]) {
                signalStrengthSum += (cycle - 1) * X;
                signalIndex++;
            }
            if (signalIndex < signalCycles.size() && cycle == signalCycles[signalIndex]) {
                signalStrengthSum += cycle * X;
                signalIndex++;
            }
            X += inst.value;
        }
        if (signalIndex >= signalCycles.size()) {
            break;
        }
    }

    std::cout << "Sum of signal strengths: " << signalStrengthSum << std::endl;

}
