/*
 * main.cpp by Christopher Soderquist January 21, 2020
 *
 * Created for the DuplicateFileTool project
 *
 * This file defines the entry point of the application
 *
 * This program makes use of hash-library by stbrumme https://github.com/stbrumme/hash-library
 * hash-library is under the Zlib license
 * DuplicateFileTool is under the GPL 3.0 license
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <filesystem>
#include "hash-library/sha256.h"

//16mb buffer
#define STREAM_BUF_SIZE (1048576 * 16)

std::string hash_of_file(const std::filesystem::path &filepath) {
    //Create hash singleton and singleton buffer
    static SHA256 sha256;
    sha256.reset();
    static char *buffer = new char[STREAM_BUF_SIZE]{};

    //We don't want the "./" prefix
    std::string str_path = filepath.string().substr(2, filepath.string().size());

    //Get the size of the file in bytes
    uintmax_t file_size = std::filesystem::file_size(filepath);

    //Open the file stream
    std::ifstream input_stream(str_path);

    //Read in and stream to hash algorithm
    uintmax_t pos = 0;
    while (true) {
        //Determine number of bytes to read
        uintmax_t bytes_to_read = STREAM_BUF_SIZE;
        if (pos + bytes_to_read > file_size) bytes_to_read = (file_size - pos);

        //Stream in data and hash
        input_stream.read(buffer, bytes_to_read);
        sha256.add(buffer, bytes_to_read);
        pos += bytes_to_read;
        if (file_size == pos) break;
    }
    return sha256.getHash();
}

int main() {
    std::cout << "Listing files in this directory with duplicates..." << std::endl;

    //Map for the size comparison stage
    std::unordered_map<uintmax_t, std::vector<std::filesystem::path>> sizes_map;

    //Map for the hash comparison stage
    std::unordered_map<std::string, std::vector<std::filesystem::path>> hashes_map;

    std::filesystem::path local_dir = std::filesystem::current_path();

    //Find all files in this directory and map them by their size
    for (const auto &file_path : std::filesystem::directory_iterator(local_dir)) {
        //Ignore directories
        if (std::filesystem::is_directory(file_path)) continue;
        uintmax_t size = std::filesystem::file_size(file_path);
        sizes_map[size].push_back(file_path);
    }

    std::cout << "Found files..." << std::endl;

    //File files with similar sizes
    std::vector<std::vector<std::filesystem::path>> duplicate_sets;
    for (const auto &set : sizes_map) {
        if (set.second.size() > 1) duplicate_sets.push_back(set.second);
    }

    std::cout << "File sizes analyzed..." << std::endl;
    std::cout << "Hashing similar size files (this may take a while)..." << std::endl;

    //For each set, hash and find duplicates
    for (const auto &set : duplicate_sets) {
        for (const auto &path : set) {
            std::string hash = hash_of_file(path);
            hashes_map[hash].push_back(path);
        }
    }

    std::cout << "File hashes generated..." << std::endl;

    //Print out matches
    std::cout << "Match groups: " << std::endl << std::endl;
    for (const auto &set_pair : hashes_map) {
        if (set_pair.second.size() > 1) {
            std::cout << "|- These are similar|" << std::endl;
            for (const auto &path : set_pair.second) {
                std::cout << "    -|" << path << std::endl;
            }
            std::cout << "|- - - -|" << std::endl << std::endl;
        }
    }

    std::cout << "Done listing duplicate files." << std::endl;

    return 0;
}
