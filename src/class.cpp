#include "class.h"
#include <unordered_map>

FileMetadata::FileMetadata(const fs::path &parent_path, std::string_view name, std::string_view ext, long long size, bool dup) 
    : m_parent_path(parent_path), m_file_name(name), m_extension(ext), m_size(size) {}


FileMetadata::~FileMetadata() {}


/*
- This function recursively iterates inside the directory, to find the file, and store the information inside the class variables
- If a directory is found in the iteration then the function goes inside the path, using recursion
- If a file is found, then the funtion will store the file path, inside the hash map, with the file extension as the key, and the vector of class objects as the value
- After every recursion, the fucntion, calls the cleanDirectory function to check for duplicates and remove them
- After the iteration, the function will erase the hash map to free up memory and avoid memory leaks
*/
void FileMetadata::processDirectory(const fs::path &dir, std::unordered_map<std::string, std::vector<FileMetadata>> &file_info) {
    // iterating inside the directory
    for (const auto& entry : fs::directory_iterator(dir)) {
        // if the path is a folder hten iterate inside the folder
        // skip the checking of hidden folders
        bool hidden_folders_condition = (entry.path().filename().string()[0] == '.');
        if (fs::is_directory(entry.path()) && !hidden_folders_condition) {
            processDirectory(entry.path(), file_info);
        }

        // if the path is not a directory and not a hidden file
        if (!fs::is_directory(entry.path()) && !hidden_folders_condition) {
            // call constructor to create a new object of the class FileMetadata, and adds the constructed object to the vector of class objects
            FileMetadata file(entry.path().parent_path(), entry.path().filename().string(), entry.path().extension().string(), fs::file_size(entry.path()));
            // this pushes the file object into the hash map, with the file extension as the key, and the vector of class objects as the value
            file_info[m_extension].push_back(file);
        }

        // here call the funtion which cleans the directory
        cleanDirectory(dir, file_info);
        file_info.clear(); // clear the hash map to free up memory and avoid memory leaks
    }
}



/*
- Function to calculate hash value of a file, and return true if the hash value is same, else return false
*/
bool compareHashValues(const fs::path &file1, const fs::path &file2) {
    // calculate hash values of the files and compare
    // return true if hash values are same, else return false
    return false; // placeholder
}