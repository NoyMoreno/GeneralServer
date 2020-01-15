//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_CACHEMANAGER_H
#define PROJECT2_CACHEMANAGER_H

#include <string>
#include <fstream>
#include <iostream>
#include "StringConverter.h"

using namespace std;

template <typename P, typename S>
class CacheManager {
private:
    StringConverter<P, S> *sc;
    std::string get_fname(P p){
        // This is our key - convert it to a string
        std::string s = sc->ConvertPToString(p);
        std::hash<std::string> hasher;
        std::string fname = "ServerCacheManager_" + std::to_string(hasher(s)) + ".txt";
        return fname;
    }
public:
CacheManager(StringConverter<P, S> *_sc) : sc(_sc) {}
    S get(P p) {
        // filename
        std::string fname = get_fname(p);
        // Open
        ifstream ifs;
        ifs.open(fname);
        if (!ifs)
            return "";

        // Read it in
        string str = string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
        ifs.close();
        S s = sc->ConvertStringToS(str);
        return s;
    }
    void put(P p, S s) {
        std::string fname = get_fname(p);
        std::string out = sc->ConvertSToString(s);
        cout << out << std::endl;
        // Write it
        ofstream ofs;
        ofs.open(fname);
        ofs << out;
        ofs.close();
    }
};


#endif //PROJECT2_CACHEMANAGER_H
