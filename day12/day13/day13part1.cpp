#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

using namespace std;

struct Packet {
    enum Type { INTEGER, LIST };
    Type type;
    int value;
    shared_ptr<vector<Packet>> list;

    Packet(int val) : type(INTEGER), value(val), list(nullptr) {}
    Packet(vector<Packet> lst) : type(LIST), value(0), list(make_shared<vector<Packet>>(lst)) {}
};

Packet parsePacket(const string& str, size_t& pos) {
    if (str[pos] == '[') {
        vector<Packet> list;
        ++pos; // skip '['
        while (str[pos] != ']') {
            if (str[pos] == ',') {
                ++pos; // skip ','
                continue;
            }
            list.push_back(parsePacket(str, pos));
        }
        ++pos; // skip ']'
        return Packet(list);
    } else {
        int num = 0;
        while (pos < str.size() && isdigit(str[pos])) {
            num = num * 10 + (str[pos] - '0');
            ++pos;
        }
        return Packet(num);
    }
}

Packet parsePacket(const string& str) {
    size_t pos = 0;
    return parsePacket(str, pos);
}

bool comparePackets(const Packet& left, const Packet& right) {
    if (left.type == Packet::INTEGER && right.type == Packet::INTEGER) {
        return left.value < right.value;
    }
    if (left.type == Packet::LIST && right.type == Packet::LIST) {
        const auto& leftList = *left.list;
        const auto& rightList = *right.list;
        for (size_t i = 0; i < min(leftList.size(), rightList.size()); ++i) {
            if (comparePackets(leftList[i], rightList[i])) return true;
            if (comparePackets(rightList[i], leftList[i])) return false;
        }
        return leftList.size() < rightList.size();
    }
    if (left.type == Packet::INTEGER) {
        return comparePackets(Packet(vector<Packet>{left}), right);
    }
    return comparePackets(left, Packet(vector<Packet>{right}));
}

int main() {
    ifstream inputFile("input.txt");
    vector<pair<Packet, Packet>> packetPairs;
    string line;

    while (getline(inputFile, line)) {
        if (line.empty()) continue;
        Packet left = parsePacket(line);
        getline(inputFile, line);
        Packet right = parsePacket(line);
        packetPairs.emplace_back(left, right);
        getline(inputFile, line); // blank line
    }

    int sumOfIndices = 0;
    for (size_t i = 0; i < packetPairs.size(); ++i) {
        if (comparePackets(packetPairs[i].first, packetPairs[i].second)) {
            sumOfIndices += (i + 1);
        }
    }

    cout << "Sum of indices of pairs in the correct order: " << sumOfIndices << endl;
}
