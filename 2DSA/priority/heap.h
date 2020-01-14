#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <string>
#include "hash.h"

class heap{
	 private:
			class node {
				 public:
					 std::string id;
					 int key;
					 void *pData;
					 
					 //constructor
					 node(std::string tid, int tkey, void* tpData);
					 node() = default;
			};

			//private data members
			std::vector<node> data;
			hashTable mapping;
			unsigned int capacity;
			unsigned int curSize;
			
			//private member functions
			void percolateUp (int posCur);
			void percolateDown (int posCur);
			int getPos(node* pn);

   public:
			//constructor
			heap(unsigned int cap);

			//public member functions
			int insert(const std::string& id, int key, void* pv =nullptr);
			int setKey(const std::string& id, int key);
			int deleteMin(std::string* pId=nullptr, int* pKey=nullptr, void* ppData=nullptr);
			int remove(const std::string& id, int* pKey=nullptr, void* ppData=nullptr);

};

#endif 
