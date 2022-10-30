//============================================================================
// Name        : Sniff.cpp
// Author      : Tyler Nguyen & Lucien Zheng
// Version     : 2/20/22
// Description : Sniff
//============================================================================
#include "Sniff.hpp"

Sniff::Sniff(Params& params) : params(params){
    string sniffWord;
    string wordList(params.sniffWordsList); //get sniff words
    string startingDirectory(params.startingDirectory); //store startingDirectory
    size_t position = startingDirectory.find_last_of('/'); //find starting position, /
    
    simpleNamePath = startingDirectory.substr(position + 1); //store as simpleNamePath, after the /
    pathName = startingDirectory; //store starting directory in pathName
    istringstream inputStream(wordList); //wrap a stream around the string
    while (true) {
        inputStream >> sniffWord;
        words.push_back(sniffWord);
       if (inputStream.eof()) break; //check for end of file
    }
}
    
void Sniff::oneDir()
{
    cout << "Relative Path Name: " << pathName << endl; //print relative path name for debugging
    DIR* dirp = opendir(".");
    if (dirp == nullptr){
    fatal("Unable to open current working directory: ", pathName);
    }
    cout << "===============================================================" << endl;
    //read and discard first two directory entries (. + ..)
    readdir(dirp);
    readdir(dirp);

    while (true) {
        currentDirectory = readdir(dirp); //processing remaining entries
        mode_t mode = DTTOIF(currentDirectory->d_type); //store mode
        simpleNamePath = string(currentDirectory->d_name); //store name of simple path
        
        if ((S_ISDIR(mode) | S_ISREG(mode)) && params.verboseS){
        cout << "Directory/File Name: " << currentDirectory->d_name << endl;
        } //check if entry is a file or a directory AND the verbatim switch is on
        
        if (S_ISDIR(mode)){ 
        cout << "Processing of Directory (Not implemented yet)" << endl;
        }
        else if (S_ISREG(mode)){
            cout << "Processing of File" << endl;
            FileID fileID = oneFile(simpleNamePath, currentDirectory->d_type, currentDirectory->d_ino, pathName);
            if (sniffWordFound){
                suspiciousFiles.push_back(fileID);
                sniffWordFound = false;
            }
            else{
            cout << "No sniff words were found" << endl;
            }
        }
        else{
        cout << "Not a directory/file" << endl;
        }
        cout << "===============================================================" << endl;        
        if (currentDirectory == nullptr){ //exit if return value is null pointer
        break;
        }
    }
    cout << "Processing of Directory Complete" << endl; //processing of directory complete
}

FileID Sniff::oneFile(string fileName, __uint8_t fileType, ino_t iNodeNumber, string pathName)
{
    FileID fileID(fileName, fileType, iNodeNumber, pathName); //create and initialize a FileID object
    ifstream inputFile(fileName); //open a stream
    if (!inputFile) {
        cout << fileName << " is unable to be opened" << endl;
        return fileID;
    } //error check

    string word;
    string comparisonWord;
    while (true) {
        inputFile >> word;
        if (inputFile.eof()){
        break;
        } 
        for (size_t i = 0; i < word.length(); i++){ //strip non-alphabetic characters
            if (!isalpha(word[i])){
            word.erase(i, 1);
            }
        }
        
        comparisonWord = word;
        if(params.caseS){ //check the i-switch
            for (size_t i = 0; i < word.length(); i++){
                comparisonWord[i] = tolower(word[i]);
            }
        }
        
        for (size_t i = 0; i < words.size(); i++){ //check for sniff words
            if (comparisonWord == words[i]){
                cout << "Sniff Word found: " << word << endl;
                fileID.storeSniffWords(word);
                sniffWordFound = true;
                break;
            }
        }
    }
    inputFile.close(); //close the file
    return fileID;
}
