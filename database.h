#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include "table.h"

#define INIT_CAPACITY 5

using namespace std;

class DataBase{
public:
    string path;
    string name;
    map<string, int> tb_names;
    Table* tables;
    int tb_capacity;
    int table_num;
    int index;

    DataBase(string db_name);
    void Delete_Database();
    void Alter_Database();
    Table Find_Table();
};

typedef struct{
    vector<DataBase*> databases;
    map<string, int> db_names;
    int db_num;
    int db_capacity;
}DataBases;

void InitDBMS(DataBases* dbms);
void ExpandDBMS(DataBases* dbms);
void ClearDBMS(DataBases* dbms);
void create_db(DataBases* dbms, string name);
void delete_db(DataBases* dbms, string name);
void show_db(DataBases* dbms);
void alter_db(DataBases* dbms, string name, string new_name);
void select_db(DataBases* dbms, string name);

#endif