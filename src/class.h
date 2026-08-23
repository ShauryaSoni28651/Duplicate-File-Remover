#ifndef CLASS_H
#define CLASS_H

#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

class FileMetadata {
private:
    bool has_duplicate{};
    long long m_size{};
    fs::path m_parent_path;
    std::string m_file_name;
    std::string m_extension;
    std::string m_hash;

public:
    FileMetadata(const fs::path &, std::string_view, std::string_view, long long, bool dup = false);

    // more function here, like getters and setters for the private members
    void processDirectory(const fs::path &, std::unordered_map<std::string, std::vector<FileMetadata>> &);
    void cleanDirectory(const fs::path &, std::unordered_map<std::string, std::vector<FileMetadata>> &);

    ~FileMetadata();
};

#endif