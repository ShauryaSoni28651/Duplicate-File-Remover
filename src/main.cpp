#include "class.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

void printMessage();
void processDirectory(const fs::path &, std::unordered_map<std::string, std::vector<fs::path>> &);
void printHashmaps(std::unordered_map<std::string, std::vector<fs::path>> &);

int main(int argc, char *argv[]) {
    // checking if the correct command-line arguments are given or not
    if (argc != 2) {
        printMessage();
        return 1;
    }
    fs::path dir_path(argv[1]);
    // checking if the directory exists or not
    if (!fs::exists(dir_path)) {
        std::cerr << "Directory doesn't exist.\n";
        return 1;
    }
    // ! this is copy pasted form the old file, edit everything(apart form printDirectory) to match the new contents of the file
    // ? starts here
    // declaring a hash map to store different things
    std::unordered_map<std::string, std::vector<FileMetadata>> file_map;
    std::vector<FileMetadata> duplicate_files;

    // printHashmaps(extension_file_map);
    // ? ends here
    
    return 0;
}


// TODO edit this such that it prints the message in a more user-friendly way, and also add more information about the program
// TODO add more information about the program, like what it does, what it doesn't do, and how to use it
// TODO add this specific line, if if duplicate files with different names are found, then the program will move all files to another folder named "Naming Conflict"
void printMessage() {
    using namespace std;

    cout << "Duplicate File Remover\n";
    cout << "=====================\n\n";
    cout << "This program scans a directory tree and finds duplicate files.\n";
    cout << "It keeps one copy of each duplicate group and moves the remaining copies to a separate folder.\n\n";

    cout << "How to use:\n";
    cout << "----------\n";
    cout << "1. Run the program and provide an existing directory path as the only argument.\n";
    cout << "2. Example: ./duplicateFileRemover.exe C:/path/to/folder\n\n";

    cout << "What the program does:\n";
    cout << "---------------------\n";
    cout << "- Searches through the selected directory and its subdirectories.\n";
    cout << "- Ignores hidden folders while scanning.\n";
    cout << "- Groups files by extension and identifies duplicates.\n";
    cout << "- Keeps one file and moves the extra copies to another folder.\n\n";

    cout << "What the program does not do:\n";
    cout << "----------------------------\n";
    cout << "- It does not clean duplicate directories, only duplicate files.\n";
    cout << "- It does not search inside hidden folders.\n\n";

    cout << "Important notes:\n";
    cout << "---------------\n";
    cout << "The program moves all duplicate files except one into a folder named \"duplicateFilesMoved\".\n";
    cout << "If duplicate files with different names are found, the program will move all files to another folder named \"Naming Conflict\".\n\n";

    cout << "Please rerun the program with a valid directory path.\n";
}

// ! this is copy pasted form the old file, edit and replace this with another implementation of the same functions
// ? starts here

// this is a test function
void printHashmaps(std::unordered_map<std::string, std::vector<fs::path>> &hashmaps) {
    for (const auto &[key, value] : hashmaps) {
        std::cout << key << '\n';
        for (const auto &i : value) {
            std::cout << i << '\n';
        }
        std::cout << std::endl;
    }
}
// ? ends here
