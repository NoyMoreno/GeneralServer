//
// Created by noy on ١٣‏/١‏/٢٠٢٠.
//
#include "FileCacheManager.h"
#include <fstream>
FileCacheManager ::FileCacheManager() {}
bool FileCacheManager::haveSolution(string problem)
{
    std::ofstream file(problem);
    if(file) {
        return true;
    } else {
        return false;
    }
}
// get the solution. The user have to check if the solution isSaved cameFrom get it.
string FileCacheManager::getSolution(string problem)
{
    string line;
    ifstream myfile (problem);
    if (myfile.is_open())
    {
         getline (myfile,line);
         myfile.close();
    }
    else cout << "Unable to open file";
    return line;
}
// save the solution to the problem
void FileCacheManager:: saveSolution(string problem, string solution)
{
    std::fstream fs;
    fs.open (problem, std::fstream::in | std::fstream::out | std::fstream::app);
    fs << solution;
    fs.close();
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