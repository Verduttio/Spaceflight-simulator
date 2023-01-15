//
// Created by Bartek on 2023-01-15.
//

#ifndef SANDBOX_DATAREADER_H
#define SANDBOX_DATAREADER_H
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

class DataReader {
public:
    static std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> segList;
        std::stringstream line(s);
        std::string segment;

        while (std::getline(line, segment, delim)) {
            segList.push_back(segment);
        }

        return segList;
    }

    static std::vector<double> getValuesByColumn(const std::vector<std::string>& lines, int column) {
        std::vector<double> values;
        for (const auto & line : lines) {
            std::vector<std::string> lineValues = split(line, '|');
            values.push_back(std::stod(lineValues[column]));
        }
        return values;
    }

    static std::vector<std::string> readFile(const std::string& fileName) {
        std::ifstream file(fileName);
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        return lines;
    }
};

#endif //SANDBOX_DATAREADER_H
