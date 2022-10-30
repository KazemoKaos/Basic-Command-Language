//============================================================================
// Name        : FileID.hpp
// Author      : Tyler Nguyen & Lucien Zheng
// Version     : 2/20/22
// Description : FileID
//============================================================================
#pragma once
#ifndef FileID_hpp
#define FileID_hpp
#include <algorithm>
#include <vector>
#include "tools.hpp"

class FileID
{
private:
	string fileName;
	ino_t iNodeNumber;
	string pathName;
	vector<string> sniffWords;
	__uint8_t fileType;

public:
	FileID(string fn, __uint8_t ft, ino_t iNode, string pn);
	void print(ostream& out);
	void storeSniffWords(string word);
};

#endif /* File_hpp */
