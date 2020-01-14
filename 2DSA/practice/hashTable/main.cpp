#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <bits/stdc++.h>
#include <locale>

#include "hash.h"

using namespace std;


int inputDictionary(hashTable hTable){ 
	 
	string words;

	string fileName = "dictionary.txt";	
	//cin >> fileName;
	ifstream dictionary;
	dictionary.open(fileName);
	if (!dictionary){
		 cerr << "Error: could not open '" << fileName << "'" << endl;
		 exit(1);
	}

	while(dictionary >> words){
		 transform(words.begin(), words.end(), words.begin(), ::tolower);
		 if (words.length() < 21){
		 		hTable.insert(words);
		 }
		 
	}

	dictionary.close();

	return 1;
}

int checkSpelling (hashTable hTable){
	string line;
	string fileName = "input.txt";
	//cin >> fileName;
	
	ifstream inputFile;
	inputFile.open(fileName);
	if(!inputFile){
		 cerr << "Error: could not open '" << fileName << "'" << endl;
		 exit(1);
	}

  unsigned int lineNum = 1;
	bool tooLong;
	unsigned int charCount;
	string word;
	while (getline(inputFile,line)){
		 
		 //lower case transformation
		 transform(line.begin(), line.end(), line.begin(), ::tolower);

		 //tooLong = false;
		 

		 //filter for unusual characters
		 for(char& x:line){
				if (isdigit(x) || isalpha(x) || (x == '-') || (x=='\'')){
					 if (charCount < 20){
							charCount ++;
							word = word + x;
					 }
					 else if (charCount == 20){
							cout << "Long word at line " << lineNum << ", starts: " << word << endl;
							charCount ++;
					 }
				}
				else{
					 if (charCount < 21 && !hTable.contains(word) && (word !="")){
								cout << "Unknown word at line " << lineNum << ": " << word << endl; 	
					 }
							word = "";
							charCount = 0;
					 }
				
		 }	
				if(charCount < 21 &&!hTable.contains(word) && (word != "")){
					cout << "Unknown word at line " << lineNum << ": " << word << endl; 	
		      word = "";
					charCount = 0; //every new line has new character count
				}
			lineNum ++;
	}
}


int main() {

//start timer	
	clock_t t1 = clock();

//initialize hashTable
	hashTable spellChecker;
	
//Dictionary File Handling
	cout << "Enter name of dictionary: ";
	inputDictionary(spellChecker);
		
//Input File Handling
	cout << "Enter name of input file: ";
	checkSpelling(spellChecker);

	//choosing written file
	cout << "Enter name of output file: ";


	clock_t t2 = clock();
	double timeDiff = ((double) (t2-t1));
	cout << "Total time (in seconds) to load dictionary: " << timeDiff <<endl;
}
