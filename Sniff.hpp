//============================================================================
// Name        : Sniff.hpp
// Author      : Tyler Nguyen & Lucien Zheng
// Version     : 2/20/22
// Description : Sniff
//============================================================================
#pragma once
#ifndef Sniff_hpp
#define Sniff_hpp
#include <dirent.h>
#include <sys/stat.h>
#include <bits/stdc++.h>
#include <algorithm>
#include <sys/stat.h>
#include "Params.hpp"
#include "FileID.hpp"
#include "tools.hpp"

class Sniff
{
private:
    Params& params;
    string simpleNamePath;
    string pathName;
    vector<string> words;
    vector<FileID> suspiciousFiles;
    struct dirent* currentDirectory;
    bool sniffWordFound = false;

public:
    Sniff(Params& params);
    void oneDir();
    FileID oneFile(string fileName, __uint8_t fileType, ino_t iNodeNumber, string pathName);
};

#endif /* Sniff_hpp */
