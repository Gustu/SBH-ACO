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