
#pragma once


#include <ios>
#include <string>
#include <fstream>
#include "./pathutils.h"

#include "../lib/hps/hps.h"

class Backup {
public:
    /// @brief using AppData path
    //static Backup AppData();
    Backup(const char* const d);
    Backup(const std::string& d);
    //Backup(std::string filepath);
    std::string getFilePath() const;
    bool del();
    void setFileName(const std::string&);
public:
    virtual std::string getAdditionalInfo() const;

    bool hasData() const;

    /// @returns if there are backup data to load
    template <typename T>
    bool tryLoad(T& res) {
        std::ifstream in(getFilePath());
        if (!hasData())
          return false;
        hps::from_stream<T>(in, res);
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

    virtual ~Backup();
protected:
    Backup();
    std::string dir = "./";  // endswith os.sep
    std::string stem = "cpp_final";
    std::string suffix = ".data"; // startswith '.'
};

class TimeTFormatter{
    std::string timefBuf;
    const char* format_str;
public:
    /// @throw std::invalid_argument format_str is "" or NULL
    TimeTFormatter(const char* const format_str);
    std::string& format(std::string& res, time_t);
};

class BackupWithTime: public Backup {
public:
    BackupWithTime(const std::string& d);
    ~BackupWithTime();
    // backup data's time
    std::string lastWriteTimeStr() const;
    const char* cannotGetWriteTimeFallBackMsg = "";
    std::string getAdditionalInfo() const override;
private:
    // init ttfmt
    void setTimeFormat(const char* const format = "%m-%d %H:%M");
    //time_t lastWriteTimeT() const;

    TimeTFormatter* ttfmt = nullptr; // to skip const
};
