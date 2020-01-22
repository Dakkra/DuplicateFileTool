# Duplicate File Tool
Tool for finding and optionally deleting duplicate files in a directory

# TODO
Offer option to remove duplicate files

# Build
Make sure to init the hash-library submodule repository:

 - `git submodule init`
 - `git submodule update`

This provides access to the hash-library repository used by this project

CMake file generated and maintained by and with JetBrains CLion 2019.3.

This project uses CMake 3.15 and operates under CPP17.

CPP17 is used for the ability to use the \<filesystem\> standard header.

# Libraries
This project makes use of a [fork of](https://github.com/Dakkra/hash-library/)  Stephan Brumme's hash-library: https://github.com/stbrumme/hash-library which is under the Zlib license.

# License
Duplicate File Tool: [LICENSE](LICENSE) GPL 3.0

hash-library: [LICENSE](https://github.com/stbrumme/hash-library/blob/master/LICENSE) Zlib