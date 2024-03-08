#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include "table.h"

using namespace std;

class DataBase{
private:
    string m_path;
    string m_name;

    map<string, Table*> tables;
    int tb_capacity;
    int tb_num;

public:
    DataBase(string db_name);
    ~DataBase();
    void ShowInfo();
    string GetName();
    void Rename(string new_name);
    void UpdatePath(string new_path);
    string GetPath();
    void ExpandDB();

    void create_tb(string name);
    void select_tb(string name);
    bool exist_tb(string name);
    void insert_into_tb(string name);
    void show_tb();
    void drop_tb(string name);
    void alter_tb(string name, string new_name);
    void delete_tb_data(string name);
    void update_tb_data(string name);
};

class DataBases{
private:
    string db_path;
    string db_name;
    int db_num;
    int db_capacity;

    map<string, DataBase*> databases;
    
public:
    DataBases();
    ~DataBases();
    void ExpandDBMS();

    void create_db(string name);
    void drop_db(string name);
    void show_db();
    void alter_db(string name, string new_name);
    void select_db(string name);
    bool exist_db(string name);
    void use_db(string name);

    void create_tb_port();
    void select_tb_port();
    void insert_into_tb_port();
    void show_tb_port();
    void drop_tb_port();
    void alter_tb_port();
    void delete_tb_port();
    void update_tb_port();
};



#endif