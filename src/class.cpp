#include "class.h"
#include <iostream>
#include <utility>

FileMetadata::FileMetadata(fs::path parent_path, const std::string_view name, const std::string_view ext, const long long size)
    : m_size(size), m_parent_path(std::move(parent_path)), m_file_name(name), m_extension(ext) {}


FileMetadata::~FileMetadata() = default;


/*
- This function recursively iterates inside the directory, to find the file, and store the information inside the class variables
- If a directory is found in the iteration then the function goes inside the path, using recursion
- If a file is found, then the function will store the file path, inside the hash map, with the file extension as the key, and the vector of class objects as the value
- After every recursion, the function, calls the cleanDirectory function to check for duplicates and remove them
- After the iteration, the function will erase the hash map to free up memory and avoid memory leaks
*/
void FileMetadata::processDirectory(const fs::path &dir, std::unordered_map<std::string, std::vector<FileMetadata>> &file_info) {
    for (const auto& entry : fs::directory_iterator(dir)) {
        // if the path is a folder then iterate inside the folder
        // skip the checking of hidden folders
        const bool hidden_dir_condition = (entry.path().filename().string()[0] == '.');

        if (fs::is_directory(entry.path()) && !hidden_dir_condition) {
            processDirectory(entry.path(), file_info);
        }

        // if the path is not a directory and not a hidden file
        else if (!fs::is_directory(entry.path()) && !hidden_dir_condition) {
            FileMetadata file(entry.path().parent_path(), entry.path().filename().string(), entry.path().extension().string(), fs::file_size(entry.path()));
            file_info[file.m_extension].push_back(file);
        }
    }
    cleanDirectory(dir, file_info);
    file_info.clear();
}


/*
- This function cleans the directory by checking for duplicates and removing duplicate files
- It may call other functions to check for duplicates, calculate hash values, and move files to the "duplicates" folder
*/
void FileMetadata::cleanDirectory(const fs::path &dir, std::unordered_map<std::string, std::vector<FileMetadata>> &file_info) {
    const fs::path duplicates_folder = dir / "duplicates";
    fs::create_directories(duplicates_folder);

    for (auto &[key, value] : file_info) {
        // no point checking if there is only one file, so skip
        if (value.size() < 2) {
            continue;
        }

        //  - for same extension file, compare via size, if size is same then compare via hash value, if hash value is same then move the file to the "duplicates" folder
        // calculating hash and storing it in member variable, for later comparisions
        value[0].calculateHash(value[0].m_parent_path / value[0].m_file_name);

        for (int i = 1; i < value.size(); ++i) {
            value[i].calculateHash(value[i].m_parent_path / value[i].m_file_name);

            if (value[0].m_hash == value[i].m_hash) {
                fs::path source = value[i].m_parent_path / value[i].m_file_name;
                fs::path destination = duplicates_folder / value[i].m_file_name;

                // move the file to the "duplicates" folder
                fs::rename(source, destination);
                value.erase(value.begin() + i); // remove the file from the vector, as it is already moved to the "duplicates" folder
                --i; // decrement i to check the next file, as the current file is already removed from the vector
            }
        }
        value.erase(value.begin()); // remove the first file from the vector, as it is already moved to the "duplicates" folder
    }
}


/*
- Function to calculate hash value of a file, and store it in the member variable m_hash, for later comparisions
- This function uses hashing algorith sha256 to calculate the hash value of the file
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

    picosha2::hash256_one_by_one hasher;
    char buffer[8192]; // Read in 8KB chunks

    while (file.read(buffer, sizeof(buffer))) {
        hasher.process(buffer, buffer + file.gcount());
    }
    // Process the final partially filled chunk (if any)
    if (file.gcount() > 0) {
        hasher.process(buffer, buffer + file.gcount());
    }
    hasher.finish();

    picosha2::get_hash_hex_string(hasher, m_hash);
}