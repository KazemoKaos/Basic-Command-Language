//============================================================================
// Name        : Params.cpp
// Author      : Tyler Nguyen & Lucien Zheng
// Version     : 2/20/22
// Description : Params
//============================================================================
#include "Params.hpp"
#include <iostream>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include "tools.hpp"
using namespace std;

ofstream myOutput("Output.txt" , ios::out | ios::app);

Params::Params(int argc, char* argv[]){
	int ch, code, optx;
	chdir("."); 
	startingDirectory = getcwd(NULL, 0);
	cout << "Current Working Directory: " << startingDirectory << endl;

	struct option longOpts[] = {
		{ "verbose", no_argument, NULL, 'v'},
		{ "output", required_argument, NULL, 'o' },
		{ "case", no_argument, NULL, 'c' },
		{ "help", no_argument, NULL, 'h'},
		{ "directory", required_argument, NULL, 'd' },
		{ "recursive", no_argument, NULL, 'r' },
		{ NULL, 0, NULL, 0}
	};

	while ( ( ch = getopt_long(argc, argv, "vo:chd:r", longOpts, &code) ) != -1 ) {
		switch (ch) {
			
			case 'v':
				//Print all files that were sniffed.
				verboseS = true;
				break;
			case 'o':
				//Output file make it true. Create file with the name.
				outputS = true;
				myOutput.open(optarg, ios::out | ios::app);
				outputFileName = optarg;
				break;
			case 'c':
				//Search for the word regardless of case. (EX: Hat, hat, hAt, etc)
				caseS = true;
				break;
			case 'r':
				recurvS = true;
				break;
			case 'd':
				//chdir to that directory and start search
				dirS = true;
				pathName = optarg;
				startingDirectory = optarg;
				chdir(startingDirectory);
				break;
			case '?':
				cout << ch << " is an invalid option" << endl;
			case 'h':
				//Display help menu (usage())
				helpS = true;
			default:
				usage();
		}
	}
	//Handle Command Line
	stringstream arg;
	for(int i=0;i<argc;i++){
	arg << argv[i] << ' ';
	}
	const auto finalArg = arg.str();
	commandLine = finalArg;
	
	//Handle Sniff Words
	optx = optind;
	if (optx == argc - 1){ 
	sniffWordsList = argv[optx];
	}else{ 
	fatal("Error: No words sniffed\n");
	}
}

void Params::printStream(ostream& output){
output << "Command: " << commandLine << endl;
if(dirS == true){
output << "Start at: " << pathName << endl;
}else{
output << "Start at: Current working directory" << endl;
}
if(outputS == true){
output << "Output file name: " << outputFileName << endl;
}else{
output << "No output file was specficied" << endl;
}
if(verboseS == true){
output << "Verbose? Yes" << endl;
}else{
output << "Verbose? No" << endl;
}
if(caseS == true){
output << "Case Sensitive? No" <<endl;
}else{
output << "Case sensitive? Yes" << endl;
}
if(recurvS == true){
output << "Recursive? Yes" << endl;
}else{
output << "Recursive? No" << endl;
}

output << "Sniff Words: " << sniffWordsList << endl;
output << "===============================================================" << endl;
}

void Params::print(){
if (outputS==true){ 
printStream(myOutput);
}else{ 
printStream(cout);
}
}

void Params::usage(){
cout << "---------------------------------------------------------------" << endl;
cout << "HELP MENU" << endl;
cout << "Command = sniff" << endl;
cout << "Options:\n[-v] (Print all files/directories that are currently opened)" << endl;
cout << "[-o] (Change source of output)" << endl;
cout << "[-c] (Sniff for word regardless of case)" << endl;
cout << "[-r] (**ADD what this does**)" << endl;  //***********************
cout << "[-d] (Change current working directory)" << endl;
cout << "[-h] (Display help menu)" << endl;
cout << "---------------------------------------------------------------" << endl;
}
