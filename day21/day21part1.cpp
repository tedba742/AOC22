#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <functional>

long long evaluate(const std::string& monkey, 
                   const std::unordered_map<std::string, std::string>& jobs,
                   std::unordered_map<std::string, long long>& memo) {
    if (memo.find(monkey) != memo.end()) {
        return memo[monkey];
    }

    const std::string& job = jobs.at(monkey);
    std::stringstream ss(job);
    std::string token;
    ss >> token;

    // Check if the job is a number
    if (isdigit(token[0]) || token[0] == '-') {
        memo[monkey] = std::stoll(token);
    } else {
        std::string lhs = token;
        std::string op;
        std::string rhs;
        ss >> op >> rhs;

        long long leftValue = evaluate(lhs, jobs, memo);
        long long rightValue = evaluate(rhs, jobs, memo);

        if (op == "+") {
            memo[monkey] = leftValue + rightValue;
        } else if (op == "-") {
            memo[monkey] = leftValue - rightValue;
        } else if (op == "*") {
            memo[monkey] = leftValue * rightValue;
        } else if (op == "/") {
            if (rightValue == 0) {
                throw std::runtime_error("Division by zero");
            }
            memo[monkey] = leftValue / rightValue;
        } else {
            throw std::runtime_error("Unknown operation: " + op);
        }
    }

    return memo[monkey];
}

int main() {
    std::ifstream inputFile("input.txt");
    std::unordered_map<std::string, std::string> jobs;
    std::unordered_map<std::string, long long> memo;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::string monkey, job;
        std::stringstream ss(line);
        std::getline(ss, monkey, ':');
        ss.ignore(1); // Skip ws after colon
        std::getline(ss, job);
        jobs[monkey] = job;
    }
    inputFile.close();
    long long result = evaluate("root", jobs, memo);
    std::cout << "Root: " << result << std::endl;


}
