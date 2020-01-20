/*
 * Util.h
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "Model.h"
#include <string>
using namespace std;

class Util {
public:
	static string xyToA1(int x, int y);
	static void a1ToXy(string a1, int* x, int* y);
	static string leftPad(string s, unsigned int finalSize);
	static string rghtPad(string s, unsigned int finalSize);
	static string trim(string s);
	static bool isValidCoords(string s);
	static bool isValidAction(string action);
	static bool isIncluded(char e, char* arr, int size);
	static bool isIncluded(int e, int* arr, int size);
};

#endif /* UTIL_H_ */
