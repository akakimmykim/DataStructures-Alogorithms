#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <bits/stdc++.h>
#include <locale>

using namespace std;
#include "hash.h"

int inputDictionary(hashTable& hTable){
	 string words;

	 string fileName;
	 cout << "enter name of dictionary:";
	 cin >> fileName;

	 ifstream dictionary;
	 dictionary.open(fileName);
	 if(!dictionary){
			cerr << "Error: could not open '" << fileName << "'" << endl;
			exit (1);
	 }

	 while (dictionary >> words){
			//lower case
			transform(words.begin(), words.end(), words.begin(), ::tolower);
			//word too long
			if (words.length() < 21){
				 hTable.insert(words);
			}
	 }

	 dictionary.close();
	 return 1;
}


int checkSpelling (hashTable& spellings, ofstream& outputfile, ifstream& inputFile){
	 //initialize variables
	 unsigned int lineNum = 1;
	 int charCount = 0;
	 bool hasDigit = false;
	 string word;
	 string line;
	 while(getline(inputFile,line)){

			//lower case the entire line
			transform(line.begin(), line.end(), line.begin(), :: tolower);

			for (char& x : line){
				 //if it is acceptable, then build the word
				 if (isdigit(x) || isalpha(x) || (x=='-') || (x=='\'')){ 
						charCount ++;
						//hits the 21st character, say long word warning
						if(isdigit(x)){
							 hasDigit = true;
						}
						if (charCount == 21){
							 outputfile << "Long word at line " << lineNum << ", starts: " << word << endl;
						}
						word = word + x;
				 }
				 //if it hits a word stopper, check the word if it is under the length
				 else{
						//check word if under max length and not a word, give warning
						if (charCount < 21 && !spellings.contains(word) && !hasDigit && !hasDigit && word!="" && word!="\'"){
							 outputfile << "Unknown word at line " << lineNum << ": " << word << endl;
						}
						//after checking, reset the word
						word = "";
						charCount = 0;
						hasDigit = false;
				 }
			}
				 //check the last word of the line
				 if (charCount < 21 && !spellings.contains(word) && !hasDigit && word!="" && word!="\'"){
						outputfile << "Unknown word at line " << lineNum << ": " << word << endl;
				 }
				 //after checking, reset the word
				 word = "";
				 charCount = 0;
				 hasDigit = false;
				 
				 //increase line number after finishing with the line
				 lineNum ++;
			}

}


int main(){
	 //input dictionary
	 hashTable spellings;
	 //start timer
	 clock_t t1 = clock();
	 inputDictionary(spellings);
	 clock_t t2 = clock();
	 double timeDiff = ((double)(t2-t1)) / CLOCKS_PER_SEC;
	 cout << "Total time (in seconds) to load dictionary: " << timeDiff << endl;
	
	
	 //spelling file open 
	 string fileName;
	 
	 cout << "enter name of input file: ";
	 cin >> fileName;

	 ifstream inputFile;
	 inputFile.open(fileName);
	 if(!inputFile){
			cerr << "Error: could not open '" << fileName << "'" << endl;
			exit (1);
	 }
	 
	 //written file open
	 ofstream outputfile;
	 string outputfileName;
	 cout << "enter name of output file: ";
	 cin >> outputfileName;
	 if(!outputfile){
			cerr << "Error: could not open '" << fileName << "'" << endl;
			exit (1);
	 }
	 outputfile.open(outputfileName);

	 //spell check
	 clock_t t3 = clock();
	 checkSpelling(spellings, outputfile, inputFile);


	 clock_t t4 = clock();
	 double timeDiff2 = (double)(t4-t3) /CLOCKS_PER_SEC;
	 outputfile.close();
	 cout << "Total time (in seconds) to check document: " << timeDiff2 << endl;
	 


}
