//
// Created by noy on ١٥‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_STRINGCONVERTER_H
#define PROJECT2_STRINGCONVERTER_H

#include <string>

template <typename P, typename S>
class StringConverter {
public:
    virtual std::string ConvertPToString(P p) = 0;
    virtual std::string ConvertSToString(S s) =  0;
    virtual S ConvertStringToS(std::string str) = 0;
    virtual ~StringConverter();
};


#endif //PROJECT2_STRINGCONVERTER_H
