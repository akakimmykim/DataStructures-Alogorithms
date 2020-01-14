#include <iostream>
#include "hash.h"

#define HASHLIM 1000000000

//constructor
hashTable::hashTable(int size){
	 capacity = getPrime(size);
	 filled = 0;
	 data.resize(capacity);
}

//getPrime used in Constructor
unsigned int hashTable::getPrime(int size){
	 unsigned int primeTable[] = {100003, 200009, 400031, 800077, 1600177, 3200357};
	 int i = 0;
	 for (; size > primeTable[i]; i++){
	 }
	 return primeTable[i];
}

unsigned int hashTable::hash(const std::string& key){
	 unsigned int hashVal = 0;
	 
	 for (char ch : key){
			hashVal = 37*hashVal + ch;
	 }

	 hashVal = hashVal % capacity;


	 return hashVal;

}


bool hashTable::rehash(){
	 unsigned int index = 0;
	 unsigned int tempIndex = 0;
	 capacity = getPrime(2*capacity);
	 
	 //prevent infinite size hashTable
	 if (capacity > HASHLIM){
			return false;
	 }

	 //generate temporary vector
	 std::vector <hashItem> tempData = data;
	 data.clear();
	 data.resize(capacity);
	 for (auto it = tempData.begin(); it != tempData.end(); it++){
			if (tempData[index].isDeleted == false && tempData[index].isOccupied == true){ 
				 insert(tempData[index].key, tempData[index].pv);
			}
			index ++;
	 }



}

unsigned int hashTable::findPos(const std::string& key){
	 unsigned int position = hash(key);
	 //linear probing
	 while (data[position].isOccupied == true){
			if (data[position].key == key && data[position].isDeleted==false){
				 return position;
			}
			position ++;
			if (position >= capacity){
				 position = 0;
			}
	 }
	 return -1;
}


int hashTable::insert(const std::string& key, void* pv){
	 //if new insert makes rehash favorable
	 if (capacity/(filled+1) == 1){
			bool checkRehash = rehash();
			if (checkRehash == false){
				 return 2;
			}
	 }
	 
	 unsigned int index = hash(key);
	 
	 //linear probing
	 while (data[index].isOccupied == true){
				 //index goes beyond vector size, start at the beginning
				 if (data[index].key == key && data[index].isDeleted==false){
						return 1;
				 }
				 index ++;
				 if (index >= capacity){
						index = 0;
				 }
	 }

	 data[index].key = key;
	 data[index].pv = pv;
	 data[index].isOccupied = true;
	 filled ++;
	 

	 return 0;

};

bool hashTable::remove(const std::string& key){
	 int position = findPos(key);
	 if (position != -1){
			data[position].isDeleted = true;
			return true;
	 }
	 return false;
}

bool hashTable::contains(const std::string& key){
	 unsigned int position = hash(key);
	 //linear probing
	 while (data[position].isOccupied == true){
			if (data[position].key == key && data[position].isDeleted == false){
				 return true;	
			}
			position ++;
			if (position >= capacity){
				 position = 0;
			}
	 }
	 return false;
}

void* hashTable::getPointer(const std::string& key, bool* b){
	 unsigned int position = findPos(key);
	 if (position != -1 ){
			if (b!=nullptr){
				 *b = true;
			}
			return data[position].pv;
	 }
	 else{
			if(b!=nullptr){
			*b = false;
			}
				 return nullptr;
	 }
}

int hashTable::setPointer(const std::string& key, void* pv){
	 unsigned int position = findPos(key);
	 if(position != -1){
			data[position].pv = pv;
			return 0; 
	 }
	 else{
			return -1;
	 }
}

