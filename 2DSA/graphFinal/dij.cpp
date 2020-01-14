#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include "graph.h"

int main(){
	 
	 //initialize Graph
	 Graph gg;
	 
	 //Open File
	 std::string inputFile, outputFile;
	 std::cout << "Enter name of graph file: ";
	 std::cin >> inputFile;
	 
	 std::ifstream theFile;
	 theFile.open(inputFile.c_str());
	 
	 //if cannot open file
	 if(!theFile){
			std::cerr << "Error: could not open '" << inputFile << "'" << std::endl;
			exit (1);
	 }


	 
	 clock_t begin = clock();
	 clock_t end = clock();
	 double timeDif = ((double)(end-begin))/CLOCKS_PER_SEC;
	 std::cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << timeDif << '\n';
	 std::cout << "Enter name of output file: ";
	 std::cin >> outputFile;
}
