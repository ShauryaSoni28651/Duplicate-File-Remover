#include "class.h"

FileInfo::FileInfo(fs::path &path, std::string_view name, std::string_view ext, double size, bool dup = false) 
    : m_path(path), m_file_name(name), m_extension(ext), m_size(size) {
    // constructor code here
}

FileInfo::~FileInfo() {
    // destructor code here
}