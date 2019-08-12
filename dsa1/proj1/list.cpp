/* Andrew Kim
// 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


template <typename T>
/* BASE CLASS */
class baseList {
 private:
 	 string name;
 protected:
	 typedef struct node {
		 T dataValue;		//stores data of various data types because of template
		 struct node* next;		
	} nPtr;		//can call nPtr as shorthand for node**/

	nPtr head; //will stay pointing to the very first node
	nPtr deleter;	//will create a new node
	nPtr follower; // will connect the previous node to the newly created node

 public:
	 // function to change the name
	 void changeName (string newName){
			name = newName;
	 }
	 
	 //function to return the name
   string getName(){
			return this->name;
	 }
	 
	 //abstract functions to transform into an abstract class
	 virtual void push(T data) = 0;	
	 virtual void pop () = 0;

   //Default Constructor
	 baseList(){
		head = NULL;
		deleter = NULL;
		follower = NULL;
		name = ""; 
	 }
	 ~baseList(){
//		 cout << "baseList destroyed" << endl;
	 }
};

/* STACK DERIVED CLASS */
template <typename T>
class stack: public baseList<T>{
 
 public:

  //Default Constructor
	stack(string initName){
		 this->changeName(initName);
	}
	
	//Destructor 
	~stack(){
	}

/*specialized push for stack*/
	void push(T data){
		typename baseList<T>::nPtr *sNode = new typename baseList<T>::nPtr;
		sNode->dataValue = data;
		
		//If a node already exists, connect the existing node to the newly made node's next ptr and set the new pointer as the new head
		if (this->head != NULL){
			 sNode->next = this->head;
			 this->head = sNode;
		}
		//If there is no node, create a new node and make it the head
		else {
			 sNode->next = NULL;
			 this->head = sNode;
		}
	 }

/*specialized pop for stack*/
	 void pop(){
	 	//If there is nothing in the stack, return error
		if (this->head == NULL){
			// cout << "ERROR: This list is empty!" << endl;
		}
		//If there is something, return the current head, set the next node as the new head, and delete the former head
		else{
			 cout << "Value popped: " << this->head->dataValue << endl;
			 this->deleter = this->head;
			 this->head = this->head->next;
			 delete this->deleter;
		}
	 }
};
/*
 //Queue DERIVED CLASS
template <typename T>
class queue: public baseList<T>{

 public:
	
	queue(){
//		cout << "Queue created" << endl;
	}
	~queue(){
//		cout << "Queue destroyed" << endl;
	}
	
	//specialized push for queue
	void push(T data){
		typename baseList<T>::node qNode = new typename baseList<T>::node;
		qNode->dataValue = data;
		qNode->next = NULL;

		if (this->head != NULL){	 //if a list already exists
			  this->follower = this->head;  //set the following pointer equal to the head (only if list has 1 item)
					//moves the follower pointer to the end of the list
				}
				this->follower->next = qNode;
		}
		else{			//if there is no list yet
			 this->head = qNode;	//set the head pointer from Null to the new linked-list element
		}
	}		
	 //specialized pop for queue
	 void pop(){
	 	if (this->head == NULL){
			 cout << "ERROR: This list is empty!" << endl;
		}
		else{
			 //cout << "Value popped: " << this->head->dataValue << endl;
			 this->deleter = this->head;
			 this->head = this->head->next;
			 delete this->deleter;
		}
	 }
};*/

int main () {
/* create the stack put all the stacks in these stacks */
stack <stack<int>> i ("intHolder");
stack <stack<double>> d ("doubleHolder");
stack <stack<string>> s ("stringHolder");

/* Ask for Filename and Open file + error check */
	 string filename;
	 fstream fileHandler;
	 cout << "Please input the filename (including the extension):" << endl;
	 cin >> filename;

	 fileHandler.open(filename);

	 if (fileHandler.fail()){
			cerr << "The file you are trying to open is invalid" << endl;
			exit(1);
	 }
	
	while (!fileHandler.eof()){
		 string job, name, value;
		 char type;
		 fileHandler >> job;
		 fileHandler >> name;
		 type = name.front();
			
		/* For Create Job */
		 if (job == "create"){
				fileHandler >> value;
		 	  switch (type){
					 case 'i':{
							//stack<int>i(name);
							}
					 	 break;
					 case 's': {stack<string>s(name);}
					 	 break;
					 case 'd': {stack<double>d(name);}
					 	 break;
				}
				
				cout << "PROCESSING COMMAND: " << job << " " << name << " " << value << "\n";
	   }	
		 else if (job == "push"){
			  fileHandler >> value;
		 	  cout << "PROCESSING COMMAND: " << job << " " << name << " " << value << "\n";
		 }
		 else if (job == "pop"){
		 	  cout << "PROCESSING COMMAND: " << job << " " << name << "\n";
		 }
	}


}

string value, word;
int number;
double decimal;

if (type == 'i'){
	if (job == "create"){
		fileHandler >> value;
		if(intHolder.checkName(name)==NULL){
			if (value == "stack"){
			intHolder.push(new Stack<int>(name));
			}
			else if (value == "queue"){
			intHolder.push(new Queue<int>(name));
			}
		}
		else{ 
			cout << "ERROR: This name already exists!" << endl;
		}
	}
	else if (job == "push"){
		fileHandler >> number;
		if(intHolder.checkName(name) != NULL){
			intHolder.checkName(name)->data->push(&number);
		}
		else{
			cout << "ERROR: This name does not exist!" << endl;
		}
	}
	else if (job == "queue"){
		if(intHolder.checkName(name) != NULL){
			intHolder.checkName(name)->data->pop();
		}
		else{
			cout << "ERROR: This name does not exist!" << endl;
		}		
	}
}

if (type == 's'){
	if (job == "create"){
		fileHandler >> value;
		if(stringHolder.checkName(name)==NULL){
			if (value == "stack"){
			stringHolder.push(new Stack<int>(name));
			}
			else if (value == "queue"){
			stringHolder.push(new Queue<int>(name));
			}
		}
		else{ 
			cout << "ERROR: This name already exists!" << endl;
		}
	}
	else if (job == "push"){
		fileHandler >> word;
		if(stringHolder.checkName(name) != NULL){
			stringHolder.checkName(name)->data->push(&word);
		}
		else{
			cout << "ERROR: This name does not exist!" << endl;
		}
	}
	else if (job == "queue"){
		if(stringHolder.checkName(name) != NULL){
			stringHolder.checkName(name)->data->pop();
		}
		else{
			cout << "ERROR: This name does not exist!" << endl;
		}		
	}
}

if (type == 'd'){
	if (job == "create"){
		fileHandler >> value;
		if(doubleHolder.checkName(name)==NULL){
			if (value == "stack"){
			doubleHolder.push(new Stack<int>(name));
			}
			else if (value == "queue"){
			doubleHolder.push(new Queue<int>(name));
			}
		}
		else{ 
			cout << "ERROR: This name already exists!" << endl;
		}
	}
	else if (job == "push"){
		fileHandler >> decimal;
		if(doubleHolder.checkName(name) != NULL){
			doubleHolder.checkName(name)->data->push(&double);
		}
		else{
			cout << "ERROR: This name does not exist!" << endl;
		}
	}
	else if (job == "queue"){
		if(doubleHolder.checkName(name) != NULL){
			doubleHolder.checkName(name)->data->pop();
		}
		else{
			cout << "ERROR: This name does not exist!" << endl;
		}		
	}
}