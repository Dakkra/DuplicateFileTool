# Duplicate File Tool
Tool for finding and optionally deleting duplicate files in a directory

# Release
There is a windows 64-bit build under the [Release](Release) folder.

No support will provided for this build.

# Install
Place the binary in whatever place you'd like. Then map the directory/folder containing the binary into the operating system PATH. 

# Usage
 - `cd` into the directory/folder you'd like to check for duplicate files
 - Run `DuplicateFileTool` in this directory. The program will scan the files and list duplicates
 - \[Optional - Deleting Duplicates\] choose `y` if you'd like to delete duplicate files
 - Select the file from the index list that you would like to keep. All others will be deleted. `-1` allows you to skip this duplicate group and keep all files listed. 

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

# Authors
 - Chris Soderquist [Github](https://github.com/Dakkra), [Web](http://dakkra.com)