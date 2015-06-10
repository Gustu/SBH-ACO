#ifndef Oligo_h
#define Oligo_h


using namespace std;

class OligoClass {
public:
	enum OligoEnum
	{
		First,
		Second,
		Third,
		Fourth
	};

	OligoEnum baseOligoClass;

	OligoEnum oligoClass;

	OligoClass(int quantity);

	OligoEnum getOligoClass(int quantity);

	void setOligoClass(int quantity);

};


class Oligo {
public:
	OligoClass *oligoClass;

	string val;

	int baseQuantity;

	int quantity;

	Oligo();

	Oligo(string val);

	Oligo(string val, int quantity);

	int operator==(const Oligo &o);

	long long valToLong();

	string LongToVal(long long iVal);

private:

	
};

#endif