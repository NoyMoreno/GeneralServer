//
// Created by noy on ١٣‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_FILECACHEMANAGER_H
#define PROJECT2_FILECACHEMANAGER_H


#include <string>
#include <unordered_map>
#include "CacheManager.h"

class FileCacheManager : public CacheManager <string, string> {
private:
    std::unordered_map<std::string, std::string> m_map;
};


#endif //PROJECT2_FILECACHEMANAGER_H
