#ifndef CLASS_H
#define CLASS_H

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

class FileInfo {
private:
    bool has_duplicate{};
    double m_size{};
    fs::path m_path;
    std::string m_file_name;
    std::string m_extension;
    std::string m_hash;
    std::vector<fs::path> m_list_of_duplicates{};

public:
    FileInfo(fs::path &, std::string_view, std::string_view, double, bool dup = false);

    // more function here, like getters and setters for the private members
    ~FileInfo();
};

#endif