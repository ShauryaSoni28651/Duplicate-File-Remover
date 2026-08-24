# Duplicate-File-Remover

A C++ utility to find and remove duplicate files from a directory.

## Features

- Scans directories recursively
- Groups files by extension
- Compares files using SHA-256 hashing
- Moves duplicates to a `duplicates` folder
- Fast and memory-efficient (reads files in chunks)

## Setup Instructions

### Windows

1. **Install MinGW** (if not already installed)
   - Download from: https://www.mingw-w64.org/
   - Add to PATH

2. **Install CMake**
   - Download from: https://cmake.org/download/
   - Download Windows x64 Installer
   - During installation, check "Add CMake to the system PATH"

3. **Clone and Build**
```bash
   git clone https://github.com/ShauryaSoni28651/Duplicate-File-Remover
   cd Duplicate-File-Remover
   mkdir build
   cd build
   cmake .. -G "MinGW Makefiles"
   cmake --build .
```

4. **Run**
```bash
   ./DuplicateFileRemover.exe <directory to clean>
```

### Linux/Mac

```bash
git clone https://github.com/ShauryaSoni28651/Duplicate-File-Remover
cd Duplicate-File-Remover
mkdir build
cd build
cmake ..
make
./DuplicateFileRemover
```

## How It Works

1. Scans the target directory for files
2. Groups files by extension
3. For each group, compares files by:
   - File size (quick filter)
   - SHA-256 hash (accurate comparison)
4. Moves duplicate files to a `duplicates` folder
5. Keeps the first occurrence of each file

## Dependencies

- **PicoSHA2** - Header-only SHA-256 library
  - Source: https://github.com/okdshin/PicoSHA2
  - License: MIT

## Project Structure
```
Duplicate-File-Remover/
├── src/
│ ├── main.cpp
│ ├── class.h
│ ├── class.cpp
│ └── picosha2.h
├── .gitignore
├── CMakeLists.txt
└── README.md
```

