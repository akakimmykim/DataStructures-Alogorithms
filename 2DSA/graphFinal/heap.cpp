#include <iostream>
#include "heap.h"
#include "hash.h"

//node constructor
heap::node::node(std::string tid, int tkey, void* tpData){
	 id = tid;
	 key = tkey;
	 pData = tpData;
}

//heap constructor
heap::heap(int cap):mapping(cap*2){
	 capacity = cap;
	 curSize=0;
	 data.resize(capacity+1); //resize heap to 
}

//percolate up
void heap::percolateUp(int posCur){
	 
	 //move whatever is in the current position to the unused index 0
	 data[0] = std::move(data[posCur]);
	 mapping.setPointer(data[0].id, &data[0]);

	 //hole that is used to compare key values
	 int hole = posCur;
	 
	 //compares the current data to the hole and moves the hole up by swapping if the current data is smaller than the parent of the hole
	 for (;data[0].key < data[hole/2].key; hole/=2){
			//swap existing data in heap with the hole
			data[hole] = std::move(data[hole/2]);
			//reassigns the pointer in the hash table to the new location
			mapping.setPointer(data[hole].id, &data[hole]);
	 }
	 
	 //moves the current data into the hole
	 data[hole]=std::move(data[0]);
	 //sets the pointer in the hash table to the new position in the hole
	 mapping.setPointer(data[hole].id, &data[hole]);
}

//percolate down
void heap::percolateDown(int posCur){
	 
	 //position of the child
	 int child;
	 
	 //creates a temporary node to store the data of the current position to create a hole
	 node tempNode = data[posCur]; 
	 mapping.setPointer(tempNode.id, &tempNode);

	 //every loop compares the current data point to that of the child and sets the child as the new parent for the next loop
	 for(; posCur*2 <= curSize; posCur = child){
			child = posCur*2;
			
			//if the child branch exists and the right child is smaller than the left child, compare with the right child
			if (child < curSize && data[child+1].key < data[child].key){
				 child++;	 
			}

			//if the child's key is smaller than the current data value, swap the child and the hole
			if (data[child].key < tempNode.key){
				 data[posCur] = std::move(data[child]);
				 mapping.setPointer(data[posCur].id, &data[posCur]);
			}
			else{
				 break;
			}
	 }
	 //replace the hole with the data originally moved
	 data[posCur] = std::move(tempNode);
	 mapping.setPointer(data[posCur].id, &data[posCur]);
}

//get the Position of a node in the heap
int heap::getPos(node* pn){
	 int pos = pn - &data[0];
	 return pos;
}

//insert a key into the heap
int heap::insert(const std::string& id, int key, void* pv){
	 
	 //if the heap is full, reject
	 if(curSize == capacity){
			return 1;
	 }
	 //if the hash table already contains the an input with the same id
	 if(mapping.contains(id)){
			return 2;
	 }

	 //insert the new id into hash
	 mapping.insert(id, &data[0]);
	 
	 //insert the new id into the end of the heap
	 data[curSize+1] = node(id, key, pv);

	 //fix binary heap
	 percolateUp(curSize + 1);
	 curSize ++;


	 return 0;
}

int heap::setKey(const std::string& id, int key){ 
	 
	 //if the heap does not contain the id
	 if (!mapping.contains(id)){
			return 1;
	 }
	 
	 //obtain the pointer to the appropriate poiner and change its key
	 node* tempNodePtr = (node*) mapping.getPointer(id);
	 tempNodePtr->key=key;
	 
	 //find the position in the binary heap of the relavant id
	 int curPos = getPos(tempNodePtr);    
	 
	 //fix the heap via percolate up or down depending on the new key
	 if (data[curPos].key < data[curPos/2].key){
			percolateUp(curPos);
	 }
	 else{
			percolateDown(curPos);
	 }

	 return 0;
}

//delete minimum value
int heap::deleteMin(std::string* pID, int* pKey, void* ppData){
	 //if heap is empty
	 if (curSize == 0){
			return 1;
	 }

	 //move the top of the heap into the unused 0 index
	 data[0] = std::move(data[1]);
	 mapping.setPointer(data[0].id, &data[0]);
	 //remove the data point from the hash table
	 mapping.remove(data[0].id);
	 
	 //if pointer values are given, set the id values to the arguments
	 if(pID){
			*pID = data[0].id;
	 }
	 if(pKey){
			*pKey = data[0].key;
	 }
	 if(ppData){
			*static_cast<void**>(ppData) = data[0].pData;
	 }

	 //replace the top of the heap with end of the heap and fix the heap order
	 data[1] = std::move(data[curSize--]);
	 mapping.setPointer(data[1].id, &data[1]);

	 percolateDown(1);

	 return 0;
}

//remove an id from a heap given its id
int heap::remove(const std::string& id, int* pkey, void* ppData){
	 //if the heap doesn't contain the id
	 if (!mapping.contains(id)){
			return 1;
	 }

	 //store the data of the removed data point
	 node* tempNodePtr = (node*)mapping.getPointer(id);
	 //remove from hash table
	 mapping.remove(id);

	 //get the position of the removed id in the heap
	 int curPos = getPos(tempNodePtr);
	 
	 //save data about the removed key into the arguments
	 if(pkey){
			*pkey = data[curPos].key;
	 }
	 if(ppData){
			*static_cast<void**>(ppData) = data[curPos].pData;
	 }

	 //replace the hole with the end of the heap and fix the heap order
	 data[curPos] = std::move(data[curSize--]);
	 mapping.setPointer(data[curPos].id, &data[curPos]);
	 if (data[curPos].key < data[curPos/2].key){
			percolateUp(curPos);
	 }
	 else{
			percolateDown(curPos);
	 }

	 return 0;
}
