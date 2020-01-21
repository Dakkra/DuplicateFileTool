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
#include "hash-library/sha256.h"

int main() {
    std::cout << "Sha256 demo" << std::endl;
    SHA256 sha256;
    std::string hello = "Hello, World!";
    std::cout << sha256("Hello, World!") << std::endl;
    std::cout << sha256(hello) << std::endl;
    std::cout << "If strings are equal, this was a success" << std::endl;
    return 0;
}
