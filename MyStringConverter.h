//
// Created by noy on ١٥‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_MYSTRINGCONVERTER_H
#define PROJECT2_MYSTRINGCONVERTER_H

#include "StringConverter.h"
#include <string>
#include <vector>
#include <numeric>

class MyStringConverter : public StringConverter<std::vector<std::string>, std::string> {
public:
    MyStringConverter(){}
    std::string ConvertPToString(std::vector<std::string> p) {
        return std::accumulate(p.begin(), p.end(), std::string(""));
    };
    std::string ConvertSToString(std::string s) {
        return s;
    }
    std::string ConvertStringToS(std::string str) {
        return str;
    };
};


#endif //PROJECT2_MYSTRINGCONVERTER_H
