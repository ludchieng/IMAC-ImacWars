/**
 * Util.cpp
 */

#include "Util.h"

string Util::xyToA1(int x, int y) {
	string res;
	res += Model::MAP_COLS_LABEL[x];
	res += to_string(Model::MAP_ROWS_LABEL[y]);
	return res;
}


void Util::a1ToXy(string a1, int* x, int* y) {
	if (!isValidCoords(a1)) {
		IllegalArgument e;
		throw e;
	}
	Util::trim(a1);
	char col = toupper(a1.at(0));
	for (int i = 0; i < Model::MAP_COLS_COUNT; i++) {
		if (Model::MAP_COLS_LABEL[i] == col) {
			*x = i;
		}
	}
	a1.erase(0, 1);
	*y = atoi(a1.c_str())-1;
}


string Util::leftPad(string s, unsigned int finalSize) {
	while (s.size() < finalSize) {
		s = ' ' + s;
	}
	return s;
}


string Util::rghtPad(string s, unsigned int finalSize) {
	while (s.size() < finalSize) {
		s += ' ';
	}
	return s;
}


bool Util::isValidCoords(string s) {
	if (s.size() < 2 || s.size() > 3) {
		return false;
	}
	if (!isalpha(s.at(0))) {
		return false;
	}
	if (!isdigit(s.at(1))) {
		return false;
	}
	if (s.size() == 3 && !isdigit(s.at(2))) {
		return false;
	}
	return true;
}


bool Util::isValidAction(string action) {
	int a = atoi(action.c_str());
	if (a < 1 || a > 3) {
		return false;
	}
	return true;
}


string Util::trim(string s) {
	while (s.at(0) == ' ') {
		s.erase(0, 1);
	}
	while (s.at(s.size()-1) == ' ') {
		s.erase(s.size()-1, 1);
	}
	return s;
}


bool Util::isIncluded(char e, char* arr, int size) {
	for (int i = 0; i < size; i++) {
		if (e == arr[i]) {
			return true;
		}
	}
	return false;
}


bool Util::isIncluded(int e, int* arr, int size) {
	for (int i = 0; i < size; i++) {
		if (e == arr[i]) {
			return true;
		}
	}
	return false;
}
