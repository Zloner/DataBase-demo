#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <iostream>
#include "database.h"

using namespace std;

void Create(DataBases* dbms);
void Delete(DataBases* dbms);
void Alter(DataBases* dbms);
void Select(DataBases* dbms);
void Show(DataBases* dbms);

#endif