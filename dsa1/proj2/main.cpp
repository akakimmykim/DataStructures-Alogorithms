#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }
  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " " 
	   << pData->firstName << " " 
	   << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
	string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

//smaller data type to store ssn
typedef struct {
	 int ssn;
	Data *dta;
} smol;
smol arr[1010000];

typedef struct {
	 unsigned long long ssn;
	 Data *dta;
} t3; 
t3 t3Array[1010000];

int qsortFn(const void *a, const void *b) {
	 	return ((smol *) a)->ssn - ((smol *) b)->ssn;
}

int qSortt3(const void *a, const void *b){
	 return (((t3 *)a)->ssn < ((t3 *)b)->ssn)? -1:1;
}
//default list sort
bool comp(Data* a, Data* b){
	 return ( a->lastName < b->lastName);
	 return ( a->firstName < b->firstName);
	 return ( a->ssn < b->ssn);
}

typedef struct {
	 string lName;
	 unsigned long long fName;
	 int ssn;
	 Data *dta;
} t22;
t22 t22Array[1010000];

int qSortt2(const void *a, const void *b){
	 if (((t22 *)a)->lName != ((t22 *)b)->lName)
	 		return (((t22 *)a)->lName < ((t22 *)b)->lName) ? -1:1;
	 else if(((t22 *)a)->lName == ((t22 *)b)->lName)
	 		return ((t22 *)a)->fName - ((t22 *)b)->fName;
	 else
			return ((t22 *)a)->ssn - ((t22 *)b)->ssn;
}

typedef struct {
	 char all[22];
	 int ssn;
	 Data *dta;
} t2;
t2 t2Array[1010000];

void conc(char f[], char l[], char array[]){
	 /*if (l[7]  > 'Z' || l[7] < 'A'){
			array[7] = '0';
	 }*/
	 for (int i = 0; i < 22; i++){
			if (i < 11){
				 if(l[i] == '\0'){
						array[i] = '0';
				 }
				 else {
						array[i] = l[i];
				 }
			}
			else{	 
				 if(f[i-11] == '\0'){
						array[i] = '0';
				 }
				 else {
						array[i] = f[i-11];
				 }
			}
	}
}

int t2qSort (const void* a, const void* b){
	 for (int i = 0; i < 22; i++){
	 		if (((t2 *)a)->all[i] != ((t2 *)b)->all[i]){
				return (((t2 *)a)->all[i] < ((t2 *)b)->all[i])? -1:1;
			}
	 }
	 return ((t2 *)a)->ssn - ((t2 *)b)->ssn;

}

void inSort(string bucket[], int length){
	 int j,i;
	 for (i = 1; i < length; i++){
			string key = bucket[i];
			j = i-1;
			while (j>=0 && (bucket[j] > key)){
				 bucket[j+1] = bucket[j];
				 j--;
			}
			bucket[j+1] = key;
	 }
}

void moveDown(smol array[], int start, int length){
	 int end = start+length;
	 for (; end > length; end--){
			array[end+1] = array[end];
			array[end] = array[end-1];
	 } 
}

char* mystr (char* a, char* b){
	 while (*a) a ++;
	 while (*a++ = *b++);
	 return --a;
}

//global arrays to store names
char temp[22];
char lName[11];
char fName[11];
char ssn[11];
char s[11];
string bucket[30];
//----------------------

void sortDataList(list<Data *> &l) {
	  //initialize iterator
		list<Data *>::iterator it = l.begin();
		int ind = 0,
				size = l.size();

			 // for t4 sort current 0.36 seconds
		if (l.front()->lastName == l.back()->lastName && l.front()->firstName == l.back()->firstName){
			 int j = 0, k = 0;
			 for(; ind < size; it++, ind++) {
					 memcpy(s, (*it)->ssn.c_str(), 11);
					 k = 10*(10*(10*(10*(10*(10*(10*(10*(s[0] - 48) + (s[1] - 48)) + (s[2] - 48)) + (s[4] - 48)) + (s[5] - 48)) + (s[7] - 48)) + (s[8] - 48)) + (s[9] - 48)) + (s[10] - 48);
					 arr[ind] = (smol) { k, *it };
			 }

			  qsort(arr, size, sizeof(smol), qsortFn);

				for(it = l.begin(), ind = 0; ind < size; it++, ind++) {
						*it = arr[ind].dta;
				}
		}
			//for t3 sort current 0.22 seconds
		else if ((*it)->firstName == (*next(it))->firstName){ 
			 //iterate through and fill the array
			 unsigned long long label = 0;
			 unsigned long long k;
					memcpy(s, (*it)->ssn.c_str(), 11);
				 	k = 10*(10*(10*(10*(10*(10*(10*(10*(s[0] - 48) + (s[1] - 48)) + (s[2] - 48)) + (s[4] - 48)) + (s[5] - 48)) + (s[7] - 48)) + (s[8] - 48)) + (s[9] - 48)) + (s[10] - 48);
					k = (10000000000*label + k);
					t3Array[ind] = (t3) {k, *it};
					ind++;
					it++;
			 for (; ind < size; ind++, it++){
					if ((*it)->firstName != (*prev(it))->firstName){
						 label ++;
					}
					memcpy(s, (*it)->ssn.c_str(), 11);
				 	k = 10*(10*(10*(10*(10*(10*(10*(10*(s[0] - 48) + (s[1] - 48)) + (s[2] - 48)) + (s[4] - 48)) + (s[5] - 48)) + (s[7] - 48)) + (s[8] - 48)) + (s[9] - 48)) + (s[10] - 48);
					k = (1000000000*label + k);
					t3Array[ind] = (t3) {k, *it};
			 }

			 qsort (t3Array, size, sizeof(t3), qSortt3);
			 for(it = l.begin(), ind = 0; ind < size; it++, ind++) {
					*it = t3Array[ind].dta;
			 } 
		}

		//t1  using t3: .078
		//else if (size<990000){
			 
		//}

		//t2 current: 1.016
		else {
			 
			 unsigned long long f;
			 int k;
				for (; ind < size; ind++, it++){
					 memcpy(lName, (*it)->lastName.c_str(),11);
					 memcpy(fName, (*it)->firstName.c_str(),11);
					 memcpy(s, (*it)->ssn.c_str(), 11); 
					 //convert strings to numbers
				 	k = 10*(10*(10*(10*(10*(10*(10*(10*(s[0] - 48) + (s[1] - 48)) + (s[2] - 48)) + (s[4] - 48)) + (s[5] - 48)) + (s[7] - 48)) + (s[8] - 48)) + (s[9] - 48)) + (s[10] - 48);

					 conc(fName, lName, temp);

					 memcpy(t2Array[ind].all, temp, 22);
					 t2Array[ind].ssn = k;
					 t2Array[ind].dta = *it;
				}
				
			 qsort(t2Array, size, sizeof(t2), t2qSort);
			 for(it = l.begin(), ind = 0; ind < size; it++, ind++) {
					*it = t2Array[ind].dta;
			 } 
			 
		}
}
		

