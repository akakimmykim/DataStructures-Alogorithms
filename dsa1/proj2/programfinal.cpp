// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2019

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
/*Author: Daniel Kim
	Professor: Carl Sable
	Course: DSA I
	Assignment: The purpose of this assignment was to create a 
	sorting algorithm that could take 4 different types of inputs.
	Each input had a unique way of generation, which meant optimal
	solutions could abuse this fact. */

#define STOP 1
typedef struct {
	long long firstName;
	long long lastName;
	long long ssn;
} mini;

	bool operator <=(const mini &a, const mini &b){
		if (a.lastName > b.lastName){
			return false;
		}
		if (a.firstName > b.firstName){
			return false;
		}
		if (a.ssn > b.ssn){
			return true;
		}
		return true;

	}
static int high[1000000];
static int low[1000000];
static long long data[1010000];
static char tempSSN[1010000][12];
static char tempFirstName[1010000][40];
static char tempLastName[1010000][40];
static long long t2[1010000];
static const char* lastNames[500] = {"ACOSTA", "ADAMS", "ADKINS", "AGUILAR", "AGUIRRE", "ALEXANDER", "ALLEN", "ALVARADO", "ALVAREZ", "ANDERSON", "ANDREWS", "ARMSTRONG", "ARNOLD", "AUSTIN", "AVILA", "AYALA", "BAILEY", "BAKER", "BALDWIN", "BANKS", "BARBER", "BARKER", "BARNES", "BARNETT", "BARRETT", "BARTON", "BATES", "BECK", "BECKER", "BELL", "BENNETT", "BENSON", "BERRY", "BISHOP", "BLACK", "BLAIR", "BLAKE", "BOWEN", "BOWMAN", "BOYD", "BRADLEY", "BRADY", "BREWER", "BROOKS", "BROWN", "BRYANT", "BURGESS", "BURKE", "BURNS", "BURTON", "BUSH", "BUTLER", "BYRD", "CABRERA", "CALDERON", "CALDWELL", "CAMACHO", "CAMPBELL", "CAMPOS", "CANNON", "CARDENAS", "CARLSON", "CARPENTER", "CARR", "CARRILLO", "CARROLL", "CARTER", "CASTANEDA", "CASTILLO", "CASTRO", "CERVANTES", "CHAMBERS", "CHAN", "CHANDLER", "CHANG", "CHAPMAN", "CHAVEZ", "CHEN", "CHRISTENSEN", "CLARK", "CLARKE", "COHEN", "COLE", "COLEMAN", "COLLINS", "COLON", "CONTRERAS", "COOK", "COOPER", "CORTEZ", "COX", "CRAIG", "CRAWFORD", "CROSS", "CRUZ", "CUMMINGS", "CUNNINGHAM", "CURRY", "CURTIS", "DANIEL", "DANIELS", "DAVIDSON", "DAVIS", "DAWSON", "DAY", "DEAN", "DELACRUZ", "DELEON", "DELGADO", "DENNIS", "DIAZ", "DIXON", "DOMINGUEZ", "DOUGLAS", "DOYLE", "DUNCAN", "DUNN", "DURAN", "EDWARDS", "ELLIOTT", "ELLIS", "ERICKSON", "ESPINOZA", "ESTRADA", "EVANS", "FARMER", "FERGUSON", "FERNANDEZ", "FIELDS", "FIGUEROA", "FISCHER", "FISHER", "FITZGERALD", "FLEMING", "FLETCHER", "FLORES", "FORD", "FOSTER", "FOWLER", "FOX", "FRANCIS", "FRANCO", "FRANK", "FRANKLIN", "FRAZIER", "FREEMAN", "FUENTES", "FULLER", "GALLAGHER", "GALLEGOS", "GARCIA", "GARDNER", "GARNER", "GARRETT", "GARZA", "GEORGE", "GIBSON", "GILBERT", "GILL", "GOMEZ", "GONZALES", "GONZALEZ", "GOODMAN", "GOODWIN", "GORDON", "GRAHAM", "GRANT", "GRAVES", "GRAY", "GREEN", "GREENE", "GREGORY", "GRIFFIN", "GRIFFITH", "GROSS", "GUERRA", "GUERRERO", "GUTIERREZ", "GUZMAN", "HAIL", "HALE", "HALL", "HAMILTON", "HAMMOND", "HAMPTON", "HANSEN", "HANSON", "HARDY", "HARMON", "HARPER", "HARRINGTON", "HARRIS", "HARRISON", "HART", "HARVEY", "HAWKINS", "HAYES", "HAYNES", "HENDERSON", "HENRY", "HERNANDEZ", "HERRERA", "HICKS", "HIGGINS", "HILL", "HINES", "HODGES", "HOFFMAN", "HOLLAND", "HOLMES", "HOLT", "HOPKINS", "HORTON", "HOWARD", "HOWELL", "HUANG", "HUBBARD", "HUDSON", "HUGHES", "HUNT", "HUNTER", "INGRAM", "JACKSON", "JACOBS", "JAMES", "JENKINS", "JENNINGS", "JENSEN", "JIMENEZ", "JOHNSON", "JOHNSTON", "JONES", "JORDAN", "JOSEPH", "JUAREZ", "KELLER", "KELLEY", "KELLY", "KENNEDY", "KHAN", "KIM", "KING", "KLEIN", "KNIGHT", "LAMBERT", "LANE", "LARA", "LARSON", "LAWRENCE", "LAWSON", "LE", "LEE", "LEON", "LEONARD", "LEWIS", "LI", "LIN", "LITTLE", "LIU", "LOGAN", "LONG", "LOPEZ", "LOVE", "LOWE", "LUCAS", "LUNA", "LYNCH", "LYONS", "MACK", "MALDONADO", "MALONE", "MANN", "MANNING", "MARQUEZ", "MARSHALL", "MARTIN", "MARTINEZ", "MASON", "MATTHEWS", "MAXWELL", "MAY", "MCCARTHY", "MCCOY", "MCDANIEL", "MCDONALD", "MCGEE", "MCKINNEY", "MCLAUGHLIN", "MEDINA", "MEJIA", "MENDEZ", "MENDOZA", "MEYER", "MILES", "MILLER", "MILLS", "MIRANDA", "MITCHELL", "MOLINA", "MONTGOMERY", "MONTOYA", "MOORE", "MORALES", "MORAN", "MORENO", "MORGAN", "MORRIS", "MORRISON", "MOSS", "MULLINS", "MUNOZ", "MURPHY", "MURRAY", "MYERS", "NAVARRO", "NEAL", "NELSON", "NEWMAN", "NEWTON", "NGUYEN", "NICHOLS", "NORMAN", "NORRIS", "NUNEZ", "OBRIEN", "OCHOA", "OCONNOR", "OLIVER", "OLSON", "ORTEGA", "ORTIZ", "OWENS", "PACHECO", "PADILLA", "PAGE", "PALMER", "PARK", "PARKER", "PARKS", "PARSONS", "PATEL", "PATTERSON", "PAUL", "PAYNE", "PEARSON", "PENA", "PEREZ", "PERKINS", "PERRY", "PERSON", "PETERS", "PETERSON", "PHAM", "PHILLIPS", "PIERCE", "PORTER", "POTTER", "POWELL", "POWERS", "PRICE", "QUINN", "RAMIREZ", "RAMOS", "RAMSEY", "RAY", "REED", "REESE", "REEVES", "REID", "REYES", "REYNOLDS", "RHODES", "RICE", "RICHARDS", "RICHARDSON", "RILEY", "RIOS", "RIVAS", "RIVERA", "ROBBINS", "ROBERTS", "ROBERTSON", "ROBINSON", "ROBLES", "RODGERS", "RODRIGUEZ", "ROGERS", "ROJAS", "ROMAN", "ROMERO", "ROSALES", "ROSE", "ROSS", "ROWE", "RUIZ", "RUSSELL", "RYAN", "SALAZAR", "SALINAS", "SANCHEZ", "SANDERS", "SANDOVAL", "SANTIAGO", "SANTOS", "SAUNDERS", "SCHMIDT", "SCHNEIDER", "SCHROEDER", "SCHULTZ", "SCHWARTZ", "SCOTT", "SERRANO", "SHARP", "SHAW", "SHELTON", "SHERMAN", "SILVA", "SIMMONS", "SIMON", "SIMPSON", "SIMS", "SINGH", "SMITH", "SNYDER", "SOLIS", "SOTO", "SPENCER", "STANLEY", "STEELE", "STEPHENS", "STEVENS", "STEVENSON", "STEWART", "STONE", "STRICKLAND", "SULLIVAN", "SUTTON", "SWANSON", "TATE", "TAYLOR", "TERRY", "THOMAS", "THOMPSON", "THORNTON", "TODD", "TORRES", "TOWNSEND", "TRAN", "TRUJILLO", "TUCKER", "TURNER", "VALDEZ", "VALENCIA", "VARGAS", "VASQUEZ", "VAUGHN", "VAZQUEZ", "VEGA", "VELASQUEZ", "WADE", "WAGNER", "WALKER", "WALLACE", "WALSH", "WALTERS", "WALTON", "WANG", "WARD", "WARNER", "WARREN", "WASHINGTON", "WATERS", "WATKINS", "WATSON", "WATTS", "WEAVER", "WEBB", "WEBER", "WEBSTER", "WELCH", "WELLS", "WEST", "WHEELER", "WHITE", "WILLIAMS", "WILLIAMSON", "WILLIS", "WILSON", "WISE", "WOLF", "WOLFE", "WONG", "WOOD", "WOODS", "WRIGHT", "WU", "YANG", "YOUNG", "ZHANG", "ZIMMERMAN"};
static const char* firstNames[500] = {"AALIYAH", "AARON", "ABEL", "ABIGAIL", "ABRAHAM", "ADALINE", "ADALYN", "ADALYNN", "ADAM", "ADDISON", "ADELINE", "ADELYN", "ADRIAN", "ADRIANA", "AIDAN", "AIDEN", "ALAINA", "ALAN", "ALANA", "ALAYNA", "ALEJANDRO", "ALEX", "ALEXA", "ALEXANDER", "ALEXANDRA", "ALEXIS", "ALICE", "ALINA", "ALIVIA", "ALIYAH", "ALLISON", "ALYSSA", "AMARA", "AMAYA", "AMELIA", "AMIR", "AMY", "ANA", "ANASTASIA", "ANDREA", "ANDRES", "ANDREW", "ANGEL", "ANGELA", "ANGELINA", "ANNA", "ANNABELLE", "ANTHONY", "ANTONIO", "ARABELLA", "ARIA", "ARIANA", "ARIANNA", "ARIEL", "ARTHUR", "ARYA", "ASHER", "ASHLEY", "ASHTON", "ATHENA", "AUBREE", "AUBREY", "AUDREY", "AUGUST", "AURORA", "AUSTIN", "AUTUMN", "AVA", "AVERY", "AVERY", "AXEL", "AYDEN", "AYLA", "BAILEY", "BARRETT", "BEAU", "BECKETT", "BELLA", "BENJAMIN", "BENNETT", "BENTLEY", "BLAKE", "BRADLEY", "BRADY", "BRANDON", "BRANTLEY", "BRAXTON", "BRAYDEN", "BRIAN", "BRIANNA", "BRIELLE", "BRODY", "BROOKE", "BROOKLYN", "BROOKLYNN", "BROOKS", "BRYAN", "BRYCE", "BRYNLEE", "BRYSON", "CADEN", "CALEB", "CALLIE", "CALVIN", "CAMDEN", "CAMERON", "CAMILA", "CARLOS", "CAROLINE", "CARSON", "CARTER", "CATHERINE", "CAYDEN", "CECILIA", "CHARLES", "CHARLIE", "CHARLIE", "CHARLOTTE", "CHASE", "CHLOE", "CHRISTIAN", "CHRISTOPHER", "CLAIRE", "CLARA", "CLAYTON", "COLE", "COLIN", "COLTON", "CONNOR", "COOPER", "CORA", "DAISY", "DAKOTA", "DALEYZA", "DAMIAN", "DANIEL", "DANIELA", "DAVID", "DAWSON", "DEAN", "DECLAN", "DELANEY", "DELILAH", "DEREK", "DESTINY", "DIANA", "DIEGO", "DOMINIC", "DYLAN", "EASTON", "EDEN", "EDWARD", "ELEANOR", "ELENA", "ELI", "ELIANA", "ELIAS", "ELIJAH", "ELISE", "ELIZA", "ELIZABETH", "ELLA", "ELLIANA", "ELLIE", "ELLIOT", "ELLIOTT", "ELOISE", "EMERSON", "EMERSYN", "EMERY", "EMILIA", "EMILIANO", "EMILY", "EMMA", "EMMANUEL", "EMMETT", "ERIC", "ESTHER", "ETHAN", "EVA", "EVAN", "EVELYN", "EVERETT", "EVERLY", "EZEKIEL", "EZRA", "FAITH", "FELIX", "FINLEY", "FINN", "FIONA", "GABRIEL", "GABRIELLA", "GAEL", "GAVIN", "GENESIS", "GENEVIEVE", "GEORGE", "GEORGIA", "GIANNA", "GIOVANNI", "GRACE", "GRACIE", "GRAHAM", "GRANT", "GRAYSON", "GREYSON", "GRIFFIN", "HADLEY", "HAILEY", "HANNAH", "HARLEY", "HARMONY", "HARPER", "HARRISON", "HAYDEN", "HAYDEN", "HAZEL", "HENRY", "HOLDEN", "HUDSON", "HUNTER", "IAN", "IRIS", "ISAAC", "ISABEL", "ISABELLA", "ISABELLE", "ISAIAH", "ISLA", "ISRAEL", "IVAN", "IVY", "JACE", "JACK", "JACKSON", "JACOB", "JADE", "JADEN", "JAKE", "JAMES", "JAMESON", "JASMINE", "JASON", "JASPER", "JAVIER", "JAX", "JAXON", "JAXSON", "JAYCE", "JAYDEN", "JAYLA", "JEREMIAH", "JEREMY", "JESSE", "JESSICA", "JESUS", "JOANNA", "JOCELYN", "JOEL", "JOHN", "JONAH", "JONATHAN", "JORDAN", "JORDYN", "JORGE", "JOSE", "JOSEPH", "JOSEPHINE", "JOSHUA", "JOSIAH", "JOSIE", "JOSUE", "JUAN", "JUDAH", "JUDE", "JULIA", "JULIAN", "JULIANA", "JULIANNA", "JULIET", "JULIETTE", "JUNE", "JUSTIN", "KADEN", "KAI", "KAIDEN", "KALEB", "KARTER", "KATHERINE", "KAYDEN", "KAYLA", "KAYLEE", "KENDALL", "KENNEDY", "KENNETH", "KEVIN", "KHLOE", "KILLIAN", "KIMBERLY", "KING", "KINGSTON", "KINSLEY", "KNOX", "KYLE", "KYLIE", "KYRIE", "LAILA", "LANDON", "LAUREN", "LAYLA", "LEAH", "LEILA", "LEILANI", "LEO", "LEON", "LEONARDO", "LEVI", "LIAM", "LILA", "LILIANA", "LILLIAN", "LILLY", "LILY", "LINCOLN", "LOGAN", "LOLA", "LONDON", "LONDYN", "LORENZO", "LUCA", "LUCAS", "LUCIA", "LUCY", "LUIS", "LUKAS", "LUKE", "LUNA", "LYDIA", "LYLA", "MACKENZIE", "MADDOX", "MADELINE", "MADELYN", "MADISON", "MAGGIE", "MAKAYLA", "MALACHI", "MALIA", "MARCUS", "MARGARET", "MARIA", "MARIAH", "MARK", "MARLEY", "MARY", "MASON", "MATEO", "MATIAS", "MATTEO", "MATTHEW", "MAVERICK", "MAX", "MAXIMUS", "MAXWELL", "MAYA", "MCKENZIE", "MELANIE", "MELODY", "MESSIAH", "MIA", "MICAH", "MICHAEL", "MICHELLE", "MIGUEL", "MILA", "MILES", "MILO", "MOLLY", "MORGAN", "MYA", "MYLES", "NAOMI", "NATALIA", "NATALIE", "NATHAN", "NATHANIEL", "NEVAEH", "NICHOLAS", "NICOLAS", "NICOLE", "NOAH", "NOELLE", "NOLAN", "NORA", "NORAH", "NOVA", "OLIVER", "OLIVIA", "OMAR", "OSCAR", "OWEN", "PAIGE", "PAISLEY", "PARKER", "PARKER", "PATRICK", "PAUL", "PAXTON", "PAYTON", "PENELOPE", "PETER", "PEYTON", "PIPER", "PRESLEY", "PRESTON", "QUINN", "RACHEL", "RAELYNN", "REAGAN", "REBECCA", "REESE", "REMI", "REMINGTON", "RHETT", "RICHARD", "RILEY", "RIVER", "ROBERT", "ROMAN", "ROSALIE", "ROSE", "ROWAN", "ROWAN", "RUBY", "RYAN", "RYDER", "RYKER", "RYLEE", "RYLEIGH", "SADIE", "SAMANTHA", "SAMUEL", "SANTIAGO", "SARA", "SARAH", "SAVANNAH", "SAWYER", "SAWYER", "SCARLETT", "SEBASTIAN", "SELENA", "SERENITY", "SIENNA", "SILAS", "SKYLAR", "SLOANE", "SOFIA", "SOPHIA", "SOPHIE", "STELLA", "STEVEN", "SUMMER", "SYDNEY", "TAYLOR", "TEAGAN", "TESSA", "THEODORE", "THIAGO", "THOMAS", "TIMOTHY", "TRINITY", "TRISTAN", "TUCKER", "TYLER", "VALENTINA", "VALERIA", "VALERIE", "VANESSA", "VICTOR", "VICTORIA", "VINCENT", "VIOLET", "VIVIAN", "WAYLON", "WESLEY", "WESTON", "WILLIAM", "WILLOW", "WYATT", "XANDER", "XAVIER", "XIMENA", "ZACHARY", "ZANDER", "ZANE", "ZAYDEN", "ZION", "ZOE", "ZOEY"};

bool compare(Data* i,Data * j){
	string ilN = (i)->lastName;
	string jlN = (j)->lastName;
	if (ilN != jlN){
		return (ilN < jlN);
	}
	string ifN = (i)->firstName;
	string jfN = (j)->firstName;
	if (ifN != jfN){
		return (ifN < jfN);	
	}
}

void swap(list<Data *>::iterator& i, list<Data *>::iterator& j){
	Data temp = **i;
	**i = **j;
	**j = temp;
}


int partition2(int low, int high){
	long long temp;
	long long pivot = t2[high];
	int i = low - 1;
	for(int j = low; j <= high-1; j++){
		if (t2[j] <= pivot){
			i++;
			temp = t2[i];
			t2[i] = t2[j];
			t2[j] = temp;
		}
	}
	temp = t2[i+1];
	t2[i+1] = t2[high];
	t2[high] = temp;
	return (i+1);
}

int partition(int low, int high, int depth){
	long long pivot = -1;
	long long temp;
	int threshhold = STOP*log(1000000);
	if (depth > threshhold){
		int mid = (low+high)/2;
		long long first = data[low];
		long long last = data[high];
		long long middle = data[mid];
			if ((middle > first && middle < last) || (middle < first && middle > last)){
				pivot = middle;
				temp = data[mid];
				data[mid] = data[high];
				data[high] = temp;
			}
			else if ((first > last && first < middle) || (first < last && first > middle)){
				pivot = first;
				temp = data[low];
				data[low] = data[high];
				data[high] = temp;
			}
			else{
				pivot = last;
			}
	}
	else{
		pivot = data[high];
	}
	int i = low - 1;
	for(int j = low; j <= high-1; j++){
		if (data[j] <= pivot){
			i++;
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}
	temp = data[i+1];
	data[i+1] = data[high];
	data[high] = temp;
	return (i+1);
}

void quickSort2(int low, int high){
	if (low< high){		
			int i;
			i = partition2(low, high);
			quickSort2(low, i-1);
			quickSort2(i+1, high);
	}
}
void quickSort(int low, int high, int depth){
	if (low < high){
		int i;
		i = partition(low, high, depth);
		quickSort(low, i-1, depth -1);
		quickSort(i+1, high, depth -1);
	}	
}

long long findLast(char* index, int low, int high){
	while(low <= high){
		int average = low + (high-low)/2;
		if (strcmp(lastNames[average], index) == 0){
			return average;
		}
		if (strcmp(lastNames[average], index) > 0){
			high = average - 1;
		}
		else{
			low = average + 1;
		}
	}
	return -1;
}

long long findFirst(char* index, int low, int high){
	while(low <= high){
		int average = low + (high-low)/2;
		if (strcmp(firstNames[average], index) == 0){
			return average;
		}
		if (strcmp(firstNames[average], index) > 0){
			high = average - 1;
		}
		else{
			low = average + 1;
		}
	}
	return -1;
}

void sortDataList(list<Data *> &l) {
  // Fill this in
	auto it = l.begin();
	auto end = l.end();
	int i = 0;
	for (; it != end; it++){
		memcpy(tempSSN[i], (*it)->ssn.c_str(), 12);
		data[i] = (100000000*(tempSSN[i][0]-'0') + 10000000*(tempSSN[i][1]-'0') + 1000000*(tempSSN[i][2]-'0') + 100000*(tempSSN[i][4]-'0') + 10000*(tempSSN[i][5]-'0') + 1000*(tempSSN[i][7]-'0') + 100*(tempSSN[i][8]-'0') + 10*(tempSSN[i][9]-'0') + (tempSSN[i][10]-'0'));
		i++;
	}
		it = l.begin();
		for (int j = 0; j < 41; it++, j++){
			memcpy(tempFirstName[j], (*it)->firstName.c_str(), 3);
			memcpy(tempLastName[j], (*it)->lastName.c_str(), 3);
		}
	if (i > 101001){
		if((strcmp(tempLastName[0], tempLastName[40]) == 0) && (strcmp(tempFirstName[0], tempFirstName[40]) == 0)){ // CASE 4
	int depth = STOP*log(i);
	quickSort(0,i-1, depth);
	it = l.begin();
	i = 0;
	for(; it != end; it++, i++){
		string s({(char)((data[i]/100000000)+'0'),(char)(((data[i]/10000000)%10)+'0'),(char)(((data[i]/1000000)%10)+'0'),'-',(char)(((data[i]/100000)%10)+'0'),(char)(((data[i]/10000)%10)+'0'),'-',(char)(((data[i]/1000)%10)+'0'),(char)(((data[i]/100)%10)+'0'),(char)(((data[i]/10)%10)+'0'),(char)(((data[i])%10)+'0')});
		(*it)->ssn = s;
	}
	}
	else if (strcmp(tempLastName[0], tempLastName[1])==0){ // CASE 3
		int count = 0;
		it = l.begin();
		for (int i = 0; it != end; it++,i++){
			memcpy(tempFirstName[i], (*it)->firstName.c_str(), 40);
			memcpy(tempLastName[i], (*it)->lastName.c_str(), 40);
			count++;
		}
		int j = 0;
		low[0]= 0;
		for(int i = 0; i < count-1; i++){
			if ((strcmp(tempFirstName[i], tempFirstName[i+1]) != 0)||(strcmp(tempLastName[i], tempLastName[i+1]) != 0)){
				high[j] = i;
				j++;
				low[j] = i+1;
			}
		}
		high[j] = count-1;
		for (int k = 0; k <= j; k++){
				quickSort(low[k], high[k], 4);
			}
				it = l.begin();
				for (int i = 0; i < count; i++, it++){
		string s({(char)((data[i]/100000000)+'0'),(char)(((data[i]/10000000)%10)+'0'),(char)(((data[i]/1000000)%10)+'0'),'-',(char)(((data[i]/100000)%10)+'0'),(char)(((data[i]/10000)%10)+'0'),'-',(char)(((data[i]/1000)%10)+'0'),(char)(((data[i]/100)%10)+'0'),(char)(((data[i]/10)%10)+'0'),(char)(((data[i])%10)+'0')});
		(*it)->ssn = s;

		}
	}
	else{ // CASE 2


			int count = 0;
			auto end = l.end();
			int i = 0;
			for (auto it = l.begin(); it != end; it++, i++, count++){
				memcpy(tempSSN[i], (*it)->ssn.c_str(), 12);
				strcpy(tempLastName[i], (*it)->lastName.c_str());
				strcpy(tempFirstName[i], (*it)->firstName.c_str());
			}
			for (int i = 0; i < count; i++){
				t2[i] = (100000000*(tempSSN[i][0]-'0') + 10000000*(tempSSN[i][1]-'0') + 1000000*(tempSSN[i][2]-'0') + 100000*(tempSSN[i][4]-'0') + 10000*(tempSSN[i][5]-'0') + 1000*(tempSSN[i][7]-'0') + 100*(tempSSN[i][8]-'0') + 10*(tempSSN[i][9]-'0') + (tempSSN[i][10]-'0'));
				char* searchFirst = tempFirstName[i];
				long long j = findFirst(searchFirst, 0, 499);
				t2[i] = t2[i] + 1000000000*j;
				char* searchLast = tempLastName[i];
				long long k = findLast(searchLast, 0, 499);
				t2[i] = t2[i]+(k*1000000000000);
			}
			quickSort2(0, count-1);
			it = l.begin();
			for (int i = 0; i < count; i++, it++){
				string s({(char)(((t2[i]%1000000000)/100000000)+'0'),(char)((((t2[i]%1000000000)/10000000)%10)+'0'),(char)((((t2[i]%1000000000)/1000000)%10)+'0'),'-',(char)((((t2[i]%1000000000)/100000)%10)+'0'),(char)((((t2[i]%1000000000)/10000)%10)+'0'),'-',(char)((((t2[i]%1000000000)/1000)%10)+'0'),(char)((((t2[i]%1000000000)/100)%10)+'0'),(char)((((t2[i]%1000000000)/10)%10)+'0'),(char)((((t2[i])%1000000000)%10)+'0')});
				(*it)->ssn = s;
				long long q = (t2[i]/(long long)1000000000)%(long long)1000;
				string f(firstNames[(int)q]);
				(*it)->firstName = f;
				string l(lastNames[(t2[i])/1000000000000]);
				(*it)->lastName = l;
			}


		}
	}
	else{ // CASE 1
			int count = 0;
			auto end = l.end();
			int i = 0;
			for (auto it = l.begin(); it != end; it++, i++, count++){
				memcpy(tempSSN[i], (*it)->ssn.c_str(), 12);
				strcpy(tempLastName[i], (*it)->lastName.c_str());
				strcpy(tempFirstName[i], (*it)->firstName.c_str());
			}
			for (int i = 0; i < count; i++){
				t2[i] = (100000000*(tempSSN[i][0]-'0') + 10000000*(tempSSN[i][1]-'0') + 1000000*(tempSSN[i][2]-'0') + 100000*(tempSSN[i][4]-'0') + 10000*(tempSSN[i][5]-'0') + 1000*(tempSSN[i][7]-'0') + 100*(tempSSN[i][8]-'0') + 10*(tempSSN[i][9]-'0') + (tempSSN[i][10]-'0'));
				char* searchFirst = tempFirstName[i];
				long long j = findFirst(searchFirst, 0, 499);
				t2[i] = t2[i] + 1000000000*j;
				char* searchLast = tempLastName[i];
				long long k = findLast(searchLast, 0, 499);
				t2[i] = t2[i]+(k*1000000000000);
			}
			quickSort2(0, count-1);
			it = l.begin();
			for (int i = 0; i < count; i++, it++){
				string s({(char)(((t2[i]%1000000000)/100000000)+'0'),(char)((((t2[i]%1000000000)/10000000)%10)+'0'),(char)((((t2[i]%1000000000)/1000000)%10)+'0'),'-',(char)((((t2[i]%1000000000)/100000)%10)+'0'),(char)((((t2[i]%1000000000)/10000)%10)+'0'),'-',(char)((((t2[i]%1000000000)/1000)%10)+'0'),(char)((((t2[i]%1000000000)/100)%10)+'0'),(char)((((t2[i]%1000000000)/10)%10)+'0'),(char)((((t2[i])%1000000000)%10)+'0')});
				(*it)->ssn = s;
				long long q = (t2[i]/(long long)1000000000)%(long long)1000;
				string f(firstNames[(int)q]);
				(*it)->firstName = f;
				string l(lastNames[(t2[i])/1000000000000]);
				(*it)->lastName = l;
			}
		}
	}	
