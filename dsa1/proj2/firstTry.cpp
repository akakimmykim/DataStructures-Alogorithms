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

//converts ssn string to a double
unsigned int numberChange(string ssn){
	 ssn.erase(3,1);
	 ssn.erase(5,1);
	 return stoi(ssn);
}

string numberChangeBack(int number){
	 string ssn = to_string(number);
	 ssn.insert(ssn.begin(), 9-ssn.length(), '0');
	 ssn.insert(5,"-");
	 ssn.insert(3,"-");
	 return ssn;
}

/*quick sort stuff*/
struct {
	bool operator () (Data* d1, Data* d2){
		 if (d1->ssn < d2->ssn){
				return true;
		 }
		 else {
				return false;
		}
	}
} customSortT4;

struct {
	 bool operator() (Data* d1, Data* d2){
			if (d1->lastName < d2->lastName) {
				return true;
			}
			if (d1->lastName > d2->lastName) {
				return false;
			}
			if (d1->firstName < d2->firstName) {
				return true;
			}
			if (d1->firstName > d2->firstName) {
				return false;
			}
			if (d1->ssn < d2->ssn) {
				return true;
			}
			if (d1->ssn > d2->ssn) {
				return false;
			}
	 }
} customSort;

//other useful functions
void makeIntArray (list<Data *> &l, int array[]){
	 int i = 0;
	 for (auto it = l.begin(); it != l.end(); i++, it++){
			array[i] = numberChange((*it)->ssn);
	 }
}

void equateInt (list<Data *> &l, int array[]){
	 int i = 0;
	 for(auto it = l.begin(); it != l.end(); it++ , i++){
			(*it)->ssn = numberChangeBack(array[i]);
			cout << (*it)->ssn << endl;
	 }
}


//other sorts
int array[1200000] = {0};
int output[1200000] = {0};

//COUNT SORT
void countSort(int size, int exp){
	 int count[10] = {0}; //create an array to store counts
	 int i = 0;
	 if (array[i] != 0){
			for (; i<size; i++){
				 count[(array[i]/exp)%10]++; //increases the count based on the number
			}

			for (int i = 1; i < 10; i++){ //add previous counts
				 count[i] += count[i-1];
			}

			for(i=size-1; i >= 0 ; i--){ //place in correct order in a temporary array
				 output[count[(array[i]/exp)%10]-1] = array[i];
				 count[(array[i]/exp)%10]--;
			}

			for(i=0; i<size; i++){
				 array[i] = output[i];
				 //cout << array [i] << endl;
			}
	 }
} 


const int BKTSZE = 1200;
const int PART = 10000;
int buckets[PART][BKTSZE] = {0};
int bucketPtrs[PART] = {0};
int buckTemp[BKTSZE] = {0};

//broken
void bucCountSort(int change[], int size, int exp){
	 int count[10] = {0}; //create an array to store counts
	 int i = 0;
	 if (change[i] != 0){
			for (; i<size; i++){
				 count[(change[i]/exp)%10]++; //increases the count based on the number
			}

			for (int i = 1; i < 10; i++){ //add previous counts
				 count[i] += count[i-1];
			}

			for(i=size-1; i >= 0 ; i--){ //place in correct order in a temporary array
				 buckTemp[count[(array[i]/exp)%10]-1] = change[i];
				 count[(change[i]/exp)%10]--;
			}

			for(i=0; i<size; i++){
				 change[i] = buckTemp[i];
				 //cout << array [i] << endl;
			}
	 }
} 

//radix sort for t4Sort
void bucRadixSort(int bucket[]){
	 for (int exp = 1; 999999999/exp > 0; exp*=10){
			bucCountSort(bucket, BKTSZE,exp);
	 }
}

void t4Sort(list<Data *> &l){
	 //create the bucket and the array list
	 int length = l.size();
	 //makeIntArray(l, array);
	 int bucketPos, i, j;
	
	 //put things into buckets
	 for (auto it = l.begin(); it != l.end(); it++){
			int social = numberChange((*it)->ssn);
			bucketPos = social/100000;
			buckets[bucketPos][bucketPtrs[bucketPos]++] = social;
			if(bucketPtrs[bucketPos] >= BKTSZE) {
					cout << "ERROR BOUNDS" << endl;
					bucketPtrs[bucketPos] = BKTSZE - 1;
			}
	 }
	 //sort each bucket
	 for(i=0; i<PART; i++){
	  	//sort(buckets[i], buckets[i]+BKTSZE); //custom Sort
			bucRadixSort(buckets[i]);
	 }

	 //make bucket look like original array
	 i=0;
	 j=0;
	 auto it = l.begin();
	 while (j<length){
			if(buckets[0][i]!=0){
				 (*it)->ssn = numberChangeBack(buckets[0][i]);
				 it++;
				 j++;
			}
			 i++;
	 }
}

string* sArray[1200000]= {};

int partition(string* sArray[], int low, int high){

	 string pivot = *sArray[high]; //choose pivot
	 int i = low - 1;

	 for(int j = low; j <= high - 1; j++){
			//if current element is smaller or equal to pivot
			if (*sArray[j] <= pivot){
				 i++;
				 swap(sArray[i], sArray[j]);
			}
	 }
	 swap (sArray[i+1], sArray[high]);
	 return (i+1);
}

void quickSort(string* array[], int low, int high){
	 if (low < high){
			int pi = partition(sArray, low, high);
	 
			quickSort(sArray, low, pi-1);
			quickSort(sArray, pi+1, high);
			//cout << pi << endl;
	 }
}

void FquickSort(list <Data *> &l, int low, int high){
	 int i = 0;
	 //cout << "hi" << endl;
	 for(auto it = l.begin(); it!=l.end(); it ++, i++){
			sArray[i] = &((*it)->ssn);
	 }
	 //cout << "hi2" << endl;
	 if (low < high){
			int pi = partition(sArray, low, high);
			//cout << pi << endl; 
			quickSort(sArray, low, pi-1);
			quickSort(sArray, pi+1, high);
	 }
}

//void sortDataList(list<Data *> &l) {
	 
	 /* Built In Sort -- have to beat those times */
	 //l.sort(customSortT4); //2.047 seconds only applicable to T4
	 //l.sort(customSort); //3.203 T4 -- 1.032 T3 -- 2.687 T2 -- 0.187 T1 
	 /*SORT THE ALMOST SORTED t4*/
	 //t4Sort(l); //2.21 seconds with build-in sort
	 //radixSort(l); //1.516 seconds
	 
	 /*FquickSort(l, 0, l.size()-1); //quickSort t4 1.203 seconds
	 int i = 0;
	 for (auto it = l.begin(); it != l.end(); i++, it++){
			(*it)->ssn = *sArray[i];
		}*/
//}

bool sortFn(Data * &a, Data * &b) {
		return a->ssn.compare(b->ssn) > 0; // trial 1
		//return a->ssn > b->ssn;						 // trial 2
}
int qsortFn(const void *a, const void *b) {
		return (*((Data **) a))->ssn.compare((*((Data **) b))->ssn); // trial 1
}

void sortDataList(list<Data *> &l) {
		// l.sort(sortFn); // trials 1 and 2

		vector<Data *> v{ begin(l), end(l) };

		// vector<Data *> v{ make_move_iterator(begin(l)), make_move_iterator(end(l)) };
		// sort(v.begin(), v.end(), sortFn);
		qsort(&v[0], v.size(), sizeof(Data *), qsortFn);
		
		l.clear();
		copy(v.begin(), v.end(), back_inserter(l));
}
