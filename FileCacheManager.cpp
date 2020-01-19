//
// Created by noy on ١٣‏/١‏/٢٠٢٠.
//
#include "FileCacheManager.h"
#include <fstream>
FileCacheManager ::FileCacheManager() {}
void FileCacheManager:: addToFile(string problem, string solution)
{
    std::ofstream file(problem);
    if(file) {
        file << problem << " : " << solution << "\n"<<endl;
    } else {
        cout << "Error opening file\n" << endl;
    }
}
bool FileCacheManager::haveSolution(string problem)
{
    // If key not found in map
    if (this->problemsToSolutions_map.find(problem) == problemsToSolutions_map.end())
        return false;
    return true;
}
// get the solution. The user have to check if the solution isSaved cameFrom get it.
string FileCacheManager::getSolution(string problem)
{
    return this->problemsToSolutions_map[problem];
}
// save the solution to the problem
void FileCacheManager:: saveSolution(string problem, string solution)
{
    this->problemsToSolutions_map[problem] = solution;
}

    //private:
//    StringConverter<P, S> *sc;
//    std::string get_fname(P p){
//        // This is our key - convert it to a string
//        std::string s = sc->ConvertPToString(p);
//        std::hash<std::string> hasher;
//        std::string fname = "ServerCacheManager_" + std::to_string(hasher(s)) + ".txt";
//        return fname;
//    }
//public:
//CacheManager(StringConverter<P, S> *_sc) : sc(_sc) {}
//    S get(P p) {
//        // filename
//        std::string fname = get_fname(p);
//        // Open
//        ifstream ifs;
//        ifs.open(fname);
//        if (!ifs)
//            return "";
//
//        // Read it in
//        string str = string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
//        ifs.close();
//        S s = sc->ConvertStringToS(str);
//        return s;
//    }
//    void put(P p, S s) {
//        std::string fname = get_fname(p);
//        std::string out = sc->ConvertSToString(s);
//        cout << out << std::endl;
//        // Write it
//        ofstream ofs;
//        ofs.open(fname);
//        ofs << out;
//        ofs.close();
//    }
//}