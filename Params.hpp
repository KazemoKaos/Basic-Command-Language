//============================================================================
// Name        : Params.hpp
// Author      : Tyler Nguyen & Lucien Zheng
// Version     : 2/20/22
// Description : Params
//============================================================================

#pragma once
#ifndef Params_hpp
#define Params_hpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tools.hpp"
using namespace std;

class Params {
	public:
		string pathName;
		string outputFileName;
		ofstream myOutput;

		//Switches
		bool outputS = false;
		bool verboseS = false;
		bool helpS = false;
		bool caseS = false;
		bool dirS = false;
		bool recurvS = false;

  	        char* startingDirectory;
		char* sniffWordsList;
		string commandLine;
		

		//Functions
		Params(int argc, char* argv[]);
   		void printStream(ostream& output);
		void print();
		void usage();
};

#endif /* Params_hpp */
