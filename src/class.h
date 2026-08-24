#ifndef CLASS_H
#define CLASS_H

#include "picosha2.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

class FileMetadata {
private:
    long long m_size{};
    fs::path m_parent_path;
    std::string m_file_name;
    std::string m_extension;
    std::string m_hash;

public:
    FileMetadata(fs::path , std::string_view, std::string_view, long long);

    // more function here, like getters and setters for the private members
    void calculateHash(const fs::path &);
    static void cleanDirectory(const fs::path &, std::unordered_map<std::string, std::vector<FileMetadata>> &);
    static void processDirectory(const fs::path &, std::unordered_map<std::string, std::vector<FileMetadata>> &);

    ~FileMetadata();
};

#endif