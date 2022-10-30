//============================================================================
// Name        : FileID.cpp
// Author      : Tyler Nguyen & Lucien Zheng
// Version     : 2/20/22
// Description : FileID
//============================================================================
#include "FileID.hpp"

FileID::FileID(string fn, __uint8_t ft, ino_t iNode, string pn)
{
	fileName = fn;
	fileType = ft;
	iNodeNumber = iNode;
	pathName = pn;
	pathName.append(fileName);
}

void FileID::print(ostream& out)
{
	out << "INode Number: " << iNodeNumber << endl;
	out << "\tPath: " << pathName << "/" << fileName << endl;
}

void FileID::storeSniffWords(string word)
{	
	if (find(sniffWords.begin(), sniffWords.end(), word) != sniffWords.end() ){
		cout << "Word is already in the vector" << endl;
		}
		else{
		sniffWords.push_back(word);
		}
}
