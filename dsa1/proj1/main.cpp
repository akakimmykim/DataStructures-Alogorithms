/*Andrew Kim 
Data Structures and Algorithms I
Project 1
This program reads from an input text file that contains directions to create stacks and queues as well as push
and pop strings, integers, or doubles into those stacks and queues. The stacks and queues were reconstructed using 
a base class, and the built-in list class was used to manipulate and store custom made stacks and queues. 
The output of the program is a file that contains lines as instructed by the project assignment*/

#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

/*The List class (capital L) should not be confused with the built-in list class (lowercase L). List is the base class for the custom stacks and queues */
template <class T>
class List {	
	protected:
		struct Node{
			T data;
			struct Node* next;
		};
		string name;
		
	public:
		// pointers that will be managing the list	
		Node* head;
		Node* follower;
		
		//default constructor 
		List(){
			head = NULL;
			follower = NULL;
		}

		//destructor that frees memory upon destruction
		~List() {
			delete this;
		}

		//abstract functions
		virtual void push(T* value) = 0;
		virtual void pop(ofstream& outfile) = 0;

		//derived classes will inherit the ability to change the name
		void changeName(string newName){
			name = newName;
		}
		//used to check the name of the stack or queue
		string getName ()const{
			 return this->name;
		}
};

/*Derived Stack Class*/
template <typename T>
class Stack : public List<T> {
	public:
		//default constructor
		Stack(string newName){
			 this->List<T>::changeName(newName);
		}
		//destructor
		~Stack(){
			delete this;
		}
		
		//functions declared below
		void push(T* value);
		void pop(ofstream& outfile);	
};

//abstract classes defined
template <typename T>
void Stack<T>::push(T* value){
	typename List<T>::Node *nNode = new typename List<T>::Node;
	nNode->data = *value;

	//if no node in the list
	 if (this->head == NULL){
			this->head = nNode;
			nNode->next = NULL;
	 }
	 // if items are already in the list
	 else{
			nNode->next = this->head;
			this->head = nNode;
	 }
}
template <typename T>
void Stack<T>::pop(ofstream& outfile) {
	typename List<T>::Node* deleter = this->head;
	//if no items in the list
	if (this->head == NULL){
			outfile << "ERROR: This list is empty!" << endl;
	 }
	//if there is only one item in the list
	else if (this->head->next == NULL){
			outfile << "Value popped: " << this->head->data << endl;
			this->head = NULL;
			delete deleter;
	 }
	//if there exists an item to pop
	else{
			outfile << "Value popped: " << this->head->data << endl;
			this->head = this->head->next;
			delete deleter;
	}
}

/*Derived Queue Class */
template <typename T>
class Queue: public List<T> {
	public:
		//default constructor
		Queue(string newName){
			this->List<T>::changeName(newName);
		}
		//destructor
		~Queue(){
			delete this;
		}

		void push(T* value);
		void pop(ofstream& outfile);
}; 

//abstract classes defined
template <typename T>
void Queue<T>::push(T* value){
	 typename List<T>::Node *nNode = new typename List<T>::Node;
	 nNode->data = *value;

	 //if no node in the list
	 if (this->head == NULL){
			this->head = nNode;
			this->follower = nNode;
			nNode->next = NULL;
	 }
	 // if items are already in the list
	 else{
			this->follower->next = nNode;
			this->follower = nNode;
			nNode->next = NULL;
	 }
}

template <typename T>
void Queue<T>::pop(ofstream& outfile) {
	 typename List<T>::Node* deleter = this->head;
	 //if no items in the list
	 if (this->head == NULL){
			outfile << "ERROR: This list is empty!" << endl;
	 }
	 //if there is only one item in the list
	 else if (this->head->next == NULL){
			outfile << "Value popped: " << this->head->data << endl;
			this->head = NULL;
			delete deleter;;
	 }
	 //if there exists an item to pop
	 else {
			outfile << "Value popped: " << this->head->data << endl;
			this->head = this->head->next;
			delete deleter;
	 }
}

//Used to check if the stack or list exists already before creating a new stack or queue
template <typename T>
bool checkName(list<List<T>*> li, string name){
	 for (auto it = li.begin(); it != li.end(); it++){
			if ((*it)->getName() == name){
				 return 1;
			}
	 }
			 return 0;
}

//Used to check and push in a value to the appropriate stack or queue
template <typename T, typename V>
void checkPush (list<T> li, string name, V data, ofstream& outfile){
	 //cycles through all the stacks and queues in the container and looks for a name match
	 for (auto it = li.begin(); it != li.end(); it++){
			//if there is a match, push the value into that match
			if ((*it)->getName() == name){
				 (*it)->push(&data);
				 return; 
			}
	 }
			outfile << "ERROR: This name does not exist!" << endl;
}

//Used to check and pop a value of the appropriate stack or queue
template <typename T>
void checkPop (list<T> li, string name, ofstream& outfile){
	 //cycles thhrough all the stacks and queues in the container and looks for a name match
	 for (auto it = li.begin(); it != li.end(); it++){
			//if there is a match, pop from that match
			if ((*it)->getName() == name){
				 (*it)->pop(outfile);
				 return; 
			}
	 }
			outfile << "ERROR: This name does not exist!" << endl;
}

int main(){
	 

	 /* create the stack put all the stacks in these stacks */
	 list<List<int>*>intHolder;
	 list<List<string>*>stringHolder;
	 list<List<double>*>doubleHolder;

	 /* Ask for Filename and Open file + error check */
			string inFilename, outFileName;
			
			//opening and reading file
			fstream fileHandler;
			cout << "Please input the filename (including the extension):" << endl;
			cin >> inFilename;
			
			fileHandler.open(inFilename);
			if (fileHandler.fail()){
				 cerr << "The file you are trying to open is invalid" << endl;
				 exit(1);
			}
			
			//writing into file
			cout<< "Name the file that will contain the results (including the extension):" << endl;
			cin >>  outFileName;
			ofstream outfile(outFileName);
			

		 /* Program Reading and Following Instructions */
		 while (!fileHandler.eof()){
				string job, name, value;
				char type;
				fileHandler >> job;
				fileHandler >> name;
				type = name.front();
			
			//The three variables below will store the value that will be pushed
			int number;
			string word;
			double decimal;

			/*INTEGERS*/
			if (type == 'i'){
				if (job == "create"){
					fileHandler >> value;
					outfile << "PROCESSING COMMAND: " << job << " " << name << " " << value << endl;		
					if(checkName(intHolder, name)==0){
						if (value == "stack"){
						intHolder.push_front(new Stack<int>(name));
						}
						else if (value == "queue"){
						intHolder.push_front(new Queue<int>(name));
						}
					}
					else{ 
						outfile << "ERROR: This name already exists!" << endl;
					}
				}
				else if (job == "push"){
					fileHandler >> number;
					outfile << "PROCESSING COMMAND: " << job << " " << name << " " << number << endl;	
					checkPush(intHolder, name, number, outfile);
					}
				else if (job == "pop"){
					outfile << "PROCESSING COMMAND: " << job << " " << name << endl;
					checkPop(intHolder, name, outfile);
					}		
			}
			
			/*STRINGS*/
			if (type == 's'){
				if (job == "create"){
					fileHandler >> value;
					outfile << "PROCESSING COMMAND: " << job << " " << name << " " << value << endl;
					if(checkName(stringHolder,name)==0){
						if (value == "stack"){
						stringHolder.push_front(new Stack<string>(name));
						}
						else if (value == "queue"){
						stringHolder.push_front(new Queue<string>(name));
						}
					}
					else{ 
						outfile << "ERROR: This name already exists!" << endl;
					}
				}
				else if (job == "push"){
					fileHandler >> word;
					outfile << "PROCESSING COMMAND: " << job << " " << name << " " << word << endl;
					checkPush(stringHolder, name, word, outfile);
				}
				else if (job == "pop"){
					outfile << "PROCESSING COMMAND: " << job << " " << name << endl;
					checkPop(stringHolder, name, outfile);
					}		
				}
			
			/*DOUBLES*/
			if (type == 'd'){
				if (job == "create"){
					fileHandler >> value;
					outfile << "PROCESSING COMMAND: " << job << " " << name << " " << value << endl;
					if(checkName(doubleHolder, name)==0){
						if (value == "stack"){
						doubleHolder.push_front(new Stack<double>(name));
						}
						else if (value == "queue"){
						doubleHolder.push_front(new Queue<double>(name));
						}
					}
					else{ 
						outfile << "ERROR: This name already exists!" << endl;
					}
				}
				else if (job == "push"){
					fileHandler >> decimal;
					outfile << "PROCESSING COMMAND: " << job << " " << name << " " << decimal << endl;
					checkPush(doubleHolder, name, decimal, outfile);
				}
				else if (job == "pop"){
					outfile << "PROCESSING COMMAND: " << job << " " << name << endl;
					checkPop(doubleHolder, name, outfile);
				}
			}
		}
		
		//finished following instructions and shutting down
		fileHandler.close();
		outfile.close();
		return 0;
}
