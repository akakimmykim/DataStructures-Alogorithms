#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstdlib>
#include <cstring>

using namespace std;
bool ARRAY[1000][1000];


std::string checkMerge(const std::string& A, const std::string& B, std::string& C, const int strLenA, const int strLenB){
//check string length
	 int a, b;
	 if (C.length() != (strLenA+strLenB)){
			return "*** NOT A MERGE ***";
	 }
	 
	 //loop through array to find all possible paths
	 for (a=0; a<= strLenB; a++) {
		 for (b=0; b<= strLenA; b++) {
			 if (a == 0 && b > 0) {
				 if (C[b-1] == A[b-1]) {
					 if (b==1){
							ARRAY[a][b] = true;
					 }
					 else{
							ARRAY[a][b] = ARRAY[a][b-1];
					 }
					 continue;
				 }
			 }
			 else if (b == 0 && a > 0) {
				 if (C[a-1] == B[a-1]) {
					 if (a==1){
							ARRAY[a][b] = true;
					 }
					 else{
							ARRAY[a][b] = ARRAY[a-1][b];
					 }
					 continue;
				 }
			 }
			 ARRAY[a][b] = false;
		 }
	 }
	 
	 //loop through row and col to determine the prioritized path in the main array
	 for (a = 1; a <= strLenB; a++) {
		 for (b = 1; b <= strLenA; b++) {
			 ARRAY[a][b] = false;

			 if (ARRAY[a-1][b] || ARRAY[a][b-1]) {
				 if (B[a-1] == A[b-1] && C[a+b-1] == A[b-1]) {
					 ARRAY[a][b] = true;
				 }
				 else if (ARRAY[a-1][b]) {
					 if (C[a+b-1] == B[a-1]) {
						 ARRAY[a][b] = true;
					 }
				 }
				 else if (ARRAY[a][b-1]) {
					 if (C[a+b-1] == A[b-1]) {
						 ARRAY[a][b] = true;
					 }
				 }
			 }
		 }
	 }
			
			//create C string to return
			if (ARRAY[strLenB][strLenA]==1) {
				a = strLenB;
				b = strLenA;
				while (b > 0 && a >= 0) {
					if (ARRAY[a][b] && (a == 0 || !ARRAY[a-1][b])) {
						C[a+b-1] = C[a+b-1]-32;
						b--;
					}
					else
						a--;
				}
				return C;
			}
			else{
				 return "*** NOT A MERGE ***";
	  	}
}


int main(){
	
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

	 std::string wordA, wordB, wordC;

	 while(inputFile >> wordA >> wordB >> wordC){

	 outputFile << checkMerge(wordA, wordB, wordC, wordA.length(), wordB.length()) << std::endl;
	 }
	 
	 return 0;	
}
