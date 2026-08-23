#include "class.h"

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
void FileMetadata::cleanDirectory(const fs::path &dir, std::unordered_map<std::string, std::vector<FileMetadata>> &file_info) {
    fs::path duplicates_folder = dir / "duplicates";
    fs::create_directories(duplicates_folder);

    for (auto &[key, value] : file_info) {
        // no point checking if there is only one file, so skip
        if (value.size() < 2) continue;
        // for same extension file, compare via size, if size is same then compare via hash value, if hash value is same then move the file to the "duplicates" folder
        // calculating hash and storing it in member variable, for later comparisions
        value[0].calculateHash(value[0].m_parent_path / value[0].m_file_name);

        for (int i = 1; i < value.size(); ++i) {
            value[i].calculateHash(value[i].m_parent_path / value[i].m_file_name);
        
            if (value[0].m_size == value[i].m_size && value[0].m_hash == value[i].m_hash) {
                // move the file to the "duplicates" folder
                fs::path destination = duplicates_folder / value[i].m_file_name;
                fs::rename(value[i].m_parent_path / value[i].m_file_name, destination);
                value.erase(value.begin() + i); // remove the file from the vector, as it is already moved to the "duplicates" folder
                --i; // decrement i to check the next file, as the current file is already removed from the vector
            }
        }
        value.erase(value.begin()); // remove the first file from the vector, as it is already moved to the "duplicates" folder
    }
}


/*
- Function to calculate hash value of a file, and store it in the member variable m_hash, for later comparisions
- This fucntion uses hashing algorith sha256 to calculate the hash value of the file
*/



// SHA-256 hashing using PicoSHA2
// https://github.com/okdshin/PicoSHA2
// Licensed under MIT License

void FileMetadata::calculateHash(const fs::path &file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for hashing: " << file_path << std::endl;
        return;
    }

    std::vector<unsigned char> hash(picosha2::k_digest_size);
    picosha2::hash256(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), hash.begin(), hash.end());

    std::stringstream ss;
    for (auto byte : hash) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    m_hash = ss.str();
}