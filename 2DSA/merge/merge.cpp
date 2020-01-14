#include <iostream>
#include <fstream>
#include <string.h>


bool BIGARRAY[2001][2001]; 

std::string checkMerge(const std::string& A, const std::string& B, std::string& C, const int strLenA, const int strLenB){
	 
	 //check string length
	 if (C.length() != (strLenA + strLenB)){
			return "*** NOT A MERGE ***";
	 }
	 
	 //reset global array
	 memset(BIGARRAY, false, sizeof BIGARRAY);
	 
	 BIGARRAY[0][0] = true;

	 //run through the big array, filling in cells with True if matching letter is present
	 int a = 1;
	 int b = 1;
	 int x, y;
	 int depth = 0;
	 int strLenC = strLenA + strLenB;
	 for (; depth <= strLenC; depth++){
			for (x = 0; x <= depth; x++){
				 y = depth - x;
				 if (BIGARRAY[y][x] == true){
						if(A[x] == C[depth]){
							 BIGARRAY[y][x+1] = true;
						}
				 		if(B[y] == C[depth]){
							 BIGARRAY[y+1][x] = true;
						}
				 }
			}
	 }

	 //make sure the array has reached the last cell
	 if (BIGARRAY[strLenB][strLenA] != true){
			return "*** NOT A MERGE ***";

	 }

	 //trace back the path following the "true" inputs
	 depth = 0;
	 x = strLenA;
	 y = strLenB;
	 for (int g = strLenC-1; g >=0; g--){
			if (y-1 >= 0 && BIGARRAY[y-1][x] == true){
				 y--;
		 }
			else{
				 x--;
				 C[g] = C[g] - 32;
			}
	 }
	 
	 return C;
}

int main (){

	 //Open File
	 std::string inputFileName, outputFileName;
	 std::cout << "Enter name of input file: ";
	 std::cin >> inputFileName;

	 std::ifstream inputFile;
	 inputFile.open(inputFileName);
	 
	 //if cannot open file
	 if(!inputFile){
			std::cerr << "Error: could not open '" << inputFileName << "'" << std::endl;
			exit (1);
	 }
	 
	 //Write to File
	 std::cout << "Enter name of output file: ";
	 std::cin >> outputFileName;

	 std::ofstream outputFile;
	 outputFile.open(outputFileName);

	 //save variables from inputFile
	 std::string wordA, wordB, wordC;

	 while(inputFile >> wordA >> wordB >> wordC){		
			outputFile << checkMerge(wordA, wordB, wordC, wordA.length(), wordB.length()) << "\n";
	 }

	 return 0;
}
