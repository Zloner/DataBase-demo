#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <iostream>
#include "database.h"
#include "table.h"

using namespace std;

void Create(DataBases* dbms);
void Drop(DataBases* dbms);
void Alter(DataBases* dbms);
void Select(DataBases* dbms);
void Show(DataBases* dbms);
void Use(DataBases* dbms);
void InsertInto(DataBases* dbms);
void Delete(DataBases* dbms);
void Update(DataBases* dbms);

#endif