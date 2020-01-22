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
#include <string>
#include <filesystem>
#include "hash-library/sha256.h"

std::string hash_of_file(const std::filesystem::path &filepath) {
    uint32_t buff_size = 4096;
    SHA256 sha256;
    //We don't want the "./" prefix
    std::string str_path = filepath.string().substr(2, filepath.string().size());
    //Open the file stream
    std::ifstream input_stream(str_path);

    std::string linebuf;
    while (input_stream.good()) {
        std::getline(input_stream, linebuf);
        sha256.add(linebuf.c_str(), linebuf.size());
    }
    return sha256.getHash();
}

int main() {
    std::cout << "Listing files in this directory with duplicates..." << std::endl;

    //Setup simple data structures
    std::unordered_map<std::string, std::vector<std::filesystem::path>> hashes_map;
    std::unordered_map<uintmax_t, std::vector<std::filesystem::path>> sizes_map;
    std::filesystem::path local_dir = "./";

    //Find all files in this directory and map them by their size
    for (const auto &file_path : std::filesystem::directory_iterator(local_dir)) {
        uintmax_t size = std::filesystem::file_size(file_path);
        sizes_map[size].push_back(file_path);
    }

    std::cout << "Files listed..." << std::endl;

    //File files with similar sizes
    std::vector<std::vector<std::filesystem::path>> duplicate_sets;
    for (const auto &set : sizes_map) {
        if (set.second.size() > 1) duplicate_sets.push_back(set.second);
    }

    std::cout << "Sizes analyzed..." << std::endl;

    //For each set, hash and find duplicates
    for (const auto &set : duplicate_sets) {
        for (const auto path : set) {
            std::string hash = hash_of_file(path);
            hashes_map[hash].push_back(path);

        }
    }

    std::cout << "Hashes generated..." << std::endl;

    //Print out matches
    std::cout << "Match groups: " << std::endl;
    for (const auto &set_pair : hashes_map) {
        if (set_pair.second.size() > 1) {
            std::cout << "|- Group|" << std::endl;
            for (const auto &path : set_pair.second) {
                std::cout << "    -|" << path << std::endl;
            }
            std::cout << "|- - - -|" << std::endl;
        }
    }

    return 0;
}
