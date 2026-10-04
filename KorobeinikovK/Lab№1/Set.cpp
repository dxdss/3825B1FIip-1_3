#include "C:\includes\Lab1\tset.h"
#include <iostream>

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {
	if (mp < 0) {
		std::cerr << "Negative power of a set!\n";
		MaxPower = 0;
		BitField = TBitField(0);
		return;
	}
}
TSet::TSet(const TSet& s): MaxPower(s.MaxPower), BitField(s.BitField) {}
TSet::TSet(const TBitField& bf): MaxPower(bf.GetLength()),BitField(bf){}
TSet::operator TBitField() { 
	return BitField; 
}
int TSet::GetMaxPower() const {
	return MaxPower;
}
void TSet::InsElem(const int Elem) {
	if (Elem < 0 || Elem >= MaxPower) {
		std::cerr << "Element outside the set!\n";
		return;
	}
	BitField.SetBit(Elem);
}
void TSet::DelElem(const int Elem) {
	if (Elem < 0 || Elem >= MaxPower) {
		std::cerr << "Element outside the set!\n";
		return;
	}
	BitField.ClrBit(Elem);
}
int TSet::IsMember(const int Elem) const {
	if (Elem < 0 || Elem >= MaxPower) {
		std::cerr << "Element outside the set!\n";
		return 0;
	}
	return BitField.GetBit(Elem);
}
int TSet::operator==(const TSet& s) const {
	if (MaxPower != s.MaxPower) {
		return 0;
	}
	if (BitField != s.BitField) {
		return 0;
	}
	return 1;
 }
int TSet::operator!=(const TSet& s) const {
	if (*this == s) {
		return 0;
	}
	return 1;
}
TSet& TSet::operator=(const TSet& s) {
	if (this != &s) {
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}
TSet TSet::operator+(const int Elem) {
	TSet ob(*this);
	ob.InsElem(Elem);
	return ob;
}
TSet TSet::operator-(const int Elem) {
	TSet ras(*this);
	ras.DelElem(Elem);
	return ras;
}
TSet TSet::operator+(const TSet& s) {
	if (MaxPower != s.MaxPower) {
		std::cerr << "Different universes!\n";
		return TSet(0);
	}
	TSet res(*this);
	res.BitField = BitField | s.BitField;
	return res;
}
TSet TSet::operator*(const TSet& s) {
	if (MaxPower != s.MaxPower) {
		std::cerr << "Different universes!\n";
		return TSet(0);
	}
	TSet res(*this);
	res.BitField = BitField & s.BitField;
	return res;
}
TSet TSet::operator~() {
	TSet res(*this);
	res.BitField = ~BitField;
	return res;
}
std::istream& operator>>(std::istream& istr, TSet& bf) {
	char ch;
	for (size_t i = 0; i < bf.MaxPower; ++i) {
		istr >> ch;
		if (ch == '1') {
			bf.BitField.SetBit(i);
		}
		else if (ch == '0') {
			bf.BitField.ClrBit(i);
		}
		else {
			std::cerr << "Error: Invalid number (must be 1 or 0)!\n";
			return istr;
		}
	}
	return istr;
}
std::ostream& operator<<(std::ostream& ostr, const TSet& bf) {
	for (size_t i = 0; i < bf.MaxPower; ++i) {
		ostr << bf.BitField.GetBit(i);
	}
	return ostr;
}