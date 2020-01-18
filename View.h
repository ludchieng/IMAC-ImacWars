/*
 * View.h
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "Model.h"
#include <iostream>
#include <string>
using namespace std;

class View {
public:
    View();
    void show(Model *m);
    string mapToString(Model *m);
};

#endif /* VIEW_H_*/
