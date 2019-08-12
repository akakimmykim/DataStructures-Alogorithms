#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
vector <string> names;
int main(){
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
		}

		while (fileHandler!=EOF){

		}
}
