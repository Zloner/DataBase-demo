#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <iostream>
#include <string>
#include <map>
#include <unistd.h>
#include "table.h"

using namespace std;

class DataBase{
public:
    string path;
    string name;
    map<string, int> tb_names;
    Table* tables;
    int tb_capacity;
    int table_num;

    DataBase(string db_name);
    void Delete_Database();
    void Alter_Database();
    Table Find_Table();
};

typedef struct{
    DataBase* databases;
    map<string, int> db_names;
    int db_num;
    int db_capacity;
}DataBases;

void InitDBMS(DataBases* dbms);
void ExpandDBMS(DataBases* dbms);
void create_db(DataBases* dbms, string name);

#endif