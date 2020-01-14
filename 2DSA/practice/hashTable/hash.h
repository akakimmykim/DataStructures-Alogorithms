#ifndef hashHeader
#define hashHeader

#include <vector>
#include <string>

class hashTable {
	public:
		hashTable (int size = 0); //constructor
		
		int insert(const std::string &key, void *pv = NULL); //insert dictionary items
		bool contains(const std::string &key); //check if spelling word exists
		void *getPointer(const std::string& key, bool* b=NULL);
		int setPointer(const std::string& key, void* pv);
		bool remove(const std::string& key);
	
	private:

		class hashItem{
			public:
				 std::string key {""};
				 bool isOccupied {false};
				 bool isDeleted {false};
				 void *pv {nullptr};
				 
				 hashItem() = default;  
		};

	
	int capacity;
	int filled;
	std::vector<hashItem> data; //a dynamic array of hashItems

	//HASH FUNCTION
	unsigned int hash(const std::string& key);
	unsigned int findPos(const std::string& key); //find the position of an existing key
	//REHASH FUNCTION
	bool rehash();

	static unsigned int getPrime(int size);

};


#endif //hashHeader

