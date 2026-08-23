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
- This function cleans the directory by checking for dupliactes and removing duplicate files
- It may call other functions to check for duplicates, calculate hash values, and move files to the "duplicates" folder
*/
/*
void FileMetadata::cleanDirectory(const fs::path &dir, std::unordered_map<std::string, std::vector<FileMetadata>> &file_info) {
    fs::path duplicates_folder = dir / "duplicates";
    fs::create_directories(duplicates_folder);

    for (auto &[key, value] : file_info) {
        // no point checking if there is only one file, so skip
        if (value.size() < 2) continue;
        // for same extension file, compare via size, if size is same then compare via hash value, if hash value is same then move the file to the "duplicates" folder
        for (size_t i = 0; i < value.size(); ++i) {
            for (size_t j = i + 1; j < value.size(); ++j) {
                if (value[i].m_size == value[j].m_size) {
                    // calculate hash values and compare
                    // if hash values are same, then move the file to the "duplicates" folder, and remove the first file from the vector, and set the has_duplicate variable to true
                    // else do nothing, remove the first file from the vector, and set the has_duplicate variable to false
                    if (compareHashValues(value[i].m_parent_path / value[i].m_file_name, value[j].m_parent_path / value[j].m_file_name)) {
                        // move the file to the "duplicates" folder
                        fs::path destination = duplicates_folder / value[j].m_file_name;
                        fs::rename(value[j].m_parent_path / value[j].m_file_name, destination);

                        value.erase(value.begin() + j);
                        value[i].has_duplicate = true;
                    } else {
                        value.erase(value.begin() + j);
                        value[i].has_duplicate = false;
                    }

                }
            }
        }
    }
}
*/

/*
- Function to calculate hash value of a file, and return true if the hash value is same, else return false
*/
bool compareHashValues(const fs::path &file1, const fs::path &file2) {
    // calculate hash values of the files and compare
    // return true if hash values are same, else return false
    return false; // placeholder
}