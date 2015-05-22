#ifndef Oligo_h
#define Oligo_h

#include <string>

using namespace std; 

enum OligoClass
{
	First,
	Second,
	Third,
	Fourth
};

class Oligo {
public:
	OligoClass oligoClass;

	string val;

	void setOligoClass(int quantity);

	Oligo();

	Oligo(string val);

	Oligo(string val, int quantity);
};

#endif