// NOTES
/*
- There is bug, currently where all the duplicate files, are moved deep inside the created directory folder created inside innermost folder in the directory tree
- Recheck the function processDirectory and cleanDirectory
- See if the path is being passed correctly to the function, and if the path is being used correctly in the function
*/


#include "class.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

static void printMessage();

int main(int argc, char *argv[]) {
    // checking if the correct command-line arguments are given or not
    if (argc != 2) {
        printMessage();
        return 1;
    }

    const fs::path dir_path(argv[1]);

    // checking if the directory exists or not
    if (!fs::exists(dir_path) || !fs::is_directory(dir_path)) {
        std::cerr << "Directory doesn't exist.\n";
        return 1;
    }

    std::unordered_map<std::string, std::vector<FileMetadata>> file_map;
    std::vector<FileMetadata> duplicate_files;

    FileMetadata file_processor("", "", "", 0);
    file_processor.processDirectory(dir_path, file_map);

    std::cout << "Duplicate scan complete.\n";
    return 0;
}


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
    cout << "The program moves all duplicate files except one into a folder named \"duplicates\".\n\n";

    cout << "Please rerun the program with a valid directory path.\n";
}

