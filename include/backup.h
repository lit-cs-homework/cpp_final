
#pragma once


#include <ios>
#include <string>
#include <fstream>
#include "../lib/hps/hps.h"

class Backup {
public:
    /// @brief using AppData path
    //static Backup AppData();
    static Backup Cwd();
    //Backup(std::string filepath);
    std::string getFilePath();
    void setFileName(const std::string&);

    bool hasData();

    /// @returns if there are backup data to load
    template <typename T>
    bool tryLoad(T& res) {
        std::ifstream in(getFilePath());
        if (!hasData())
          return false;
        res = hps::from_stream<T>(in);
        in.close();
        return true;
    }

    /// @throw runtime_error if no data to read
    template <typename T>
    T load() {
        T res;
        if (!tryLoad(res))
          throw std::runtime_error(
            std::string("no data to load from file: ")+getFilePath());
        return res;
    }

    template <typename T>
    bool trySave(const T& x) {
        /*  C++ cannot truncate???
        out.seekp(0);
        out.truncate();
        */
        std::ofstream out;
        out.open(getFilePath(), std::ios::trunc|std::ios::out);
        if(out.fail())
          return false;
        hps::to_stream(x, out);
        out.close();
        return true;
    }
    /// @throw runtime_error if failed to write
    template <typename T>
    void save(const T& x) {
        if(trySave(x)) return;
        throw std::runtime_error(
          std::string("failed to save to file: ")+getFilePath());
    }

private:
    Backup(); 
    const char* dir = "./";
    const char* filename = "cpp_final.data";
};
