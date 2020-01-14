#include <iostream>
#include "hash.h"

#define HASHLIMIT 4000000000

//constructor
hashTable::hashTable(int size){
	capacity = getPrime(size);
	filled = 0;
	data.resize(capacity);
}

// functions from class definition in the header file
//PRIMES
unsigned int hashTable::getPrime(int size){
	 unsigned int primes[13] = { 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117};
		 int i = 0;
	while (size > primes[i]){
		i ++;	 
	}
	return primes[i];
}

//hash function that returns a hash value
unsigned int hashTable::hash(const std::string& key){
	unsigned int hashVal = 0;

	for (char ch : key){
		 hashVal = 37*hashVal + ch;
	}

	hashVal = hashVal % capacity;

	//linear Probing
	if (data[hashVal].isOccupied && !data[hashVal].isDeleted){
		 for (hashVal++; hashVal < capacity; hashVal++){
				if (!data[hashVal].isOccupied || data[hashVal].key == key){
					 return hashVal;
				}
		 }

		 rehash();
	}
	//already empty
	else{
		 return hashVal;
	}
}

//find position
unsigned int hashTable::findPos(const std::string& key){
	 unsigned int pos = hash(key);
	 if (data[pos].isOccupied == false){
			return -1;
	 }
	 else{
			return pos;
	 }

}

//rehash
bool hashTable::rehash(){
	 unsigned int index = 0;
	 unsigned int newIndex;
	 unsigned int prevCap = capacity;
	 //new capcity from prime
	 capacity = getPrime(2*prevCap);
	 if (capacity > HASHLIMIT) {
			return false;
	 }
	 //generate temporary table for rehashing and copy old data into temp
	 std::vector <hashItem> tempData (capacity);
	 tempData = std::move(data);
	 //resize original hash
	 data.resize(capacity);

	 //rehash existing elements
	 while (index < prevCap){
			
			//actual deletion
			if ((tempData[index].isDeleted == false)){
				 newIndex = hash(tempData[index].key);
				 data[newIndex] = tempData[index];
			}
			index++;
	 }
	 return true;
}


//insert dictionary components
int hashTable::insert(const std::string& key, void *pv){
	unsigned int hashValue = hash(key);	
	//need to resize
	if (capacity/(filled+1) < 2){ //rehash 
		 rehash();
		 if (rehash() == false){
				return 2;
		 }
	}
	
	//key already exists
	if (data[hashValue].key == key){
		 return 1;
	}
	
	//successful insert
	data[hashValue].key = key;
	data[hashValue].isOccupied = true;
	data[hashValue].pv = pv;
	filled ++;
 	return 0;
}

//check if an element exists in the hash table
bool hashTable::contains(const std::string& key){
	 unsigned int pos = hash(key);
	 if(data[pos].key == key && !data[pos].isDeleted){
			return true;	
	 }
	 return false;
}


void* hashTable::getPointer(const std::string& key, bool* b){
	 if (contains(key)==false){
			return NULL;
	 }
	 else if (b != NULL){
			*b = true;
	 }
	 else{
			*b = false;
	 }
}

int hashTable::setPointer(const std::string& key, void* pv){
	 unsigned int pos = hash(key);
	 if(data[pos].isOccupied == false){
			return 1;
	 }
	 else {
			data[pos].pv = pv;
			return 0;
	 }
}

bool hashTable::remove(const std::string& key){
	 unsigned int pos = hash(key);
	 if(data[pos].isOccupied == false){
			return false;
	 }
	 else{
			data[pos].isDeleted = true;
			return true;
	 }
}
