//globals.cpp
#include "globals.h"

int strToInt(string s){
	int x;
	istringstream i(s);
	if(!(i >> x)){
		cout << "Bad int conversion: " << s << endl;
	}
	return x;
}

int strToInt(char* s){
	int x;
	istringstream i(s);
	if(!(i >> x)){
		cout << "Bad int conversion: " << s << endl;
	}
	return x;
}
