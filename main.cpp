//============================================================================
// Name        : main.cpp
// Author(s)   : Tyler Nguyen & Lucien Zheng
// Version     : 2/20/22
// Description : Program 3
//============================================================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Sniff.hpp"
#include "tools.hpp"
using namespace std;

int main(int argc, char* argv[]){
banner();

Params prm(argc, argv);
prm.print();

Sniff sniff(prm);
sniff.oneDir();

bye();
return 0;
}
