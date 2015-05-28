#include "Source.h"

Oligo::Oligo() {
	val = "";
}

Oligo::Oligo(string val) {
	this->val = val;
	oligoClass = new OligoClass(1);
	baseQuantity = 1;
}

Oligo::Oligo(string val, int quantity) {
	this->val = val;
	oligoClass = new OligoClass(quantity);
	baseQuantity = quantity;
}

OligoClass::OligoEnum OligoClass::getOligoClass(int quantity) {
	if (quantity == 0) {
		return First;
	}
	else if (quantity > 0 && quantity < 3) {
		return Second;
	}
	else if (quantity > 2 && quantity < 5) {
		return Third;
	}
	else {
		return Fourth;
	}
}

void OligoClass::setOligoClass(int quantity) {
	oligoClass = getOligoClass(quantity);
}

OligoClass::OligoClass(int quantity) {
	baseOligoClass = getOligoClass(quantity);
	oligoClass = baseOligoClass;
}

int Oligo::operator==(const Oligo &o){
	return val == o.val;
}

int Oligo::valToInt(){
	int iValue = 0;
	//A=0,C=1,G=2,T=3
	for (int i = 0; i < val.size();i++){
		switch (val[i]){
		case 'A':
			iValue += pow(4, i) * 0;
			break;
		case 'C':
			iValue += pow(4, i) * 1;
			break;
		case 'G':
			iValue += pow(4, i) * 2;
			break;
		case 'T':
			iValue += pow(4, i) * 3;
			break;
		}
	}
	return iValue;
}