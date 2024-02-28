#include "database.h"

using namespace std;


DataBase::DataBase(string db_name){
    char* db_path;
    db_path = (char*)malloc(sizeof(char) * 64);
    getcwd(db_path, 64);

    path = db_path;
    free(db_path);

    name = db_name;
}
void DataBase::Delete_Database(){

}
void DataBase::Alter_Database(){

}
Table DataBase::Find_Table(){

}

void InitDBMS(DataBases* dbms){
    dbms->db_num = 0;
    dbms->db_capacity = 5;
    dbms->databases = (DataBase*)malloc(sizeof(DataBase) * dbms->db_capacity);
    if(!dbms->databases){
        cout << "run out of memory" << endl;
        return;
    }
}

void ExpandDBMS(DataBases* dbms){
    dbms->db_capacity *= 2;
    dbms->databases = (DataBase*)realloc(dbms->databases, sizeof(DataBase) * dbms->db_capacity);
    if(!dbms->databases){
        cout << "run out of memory" << endl;
        return;
    }
}

void create_db(DataBases* dbms, string name){

    if(dbms->db_num == dbms->db_capacity)
        ExpandDBMS(dbms);
    
    if(dbms->db_names[name] != 0){
        dbms->db_names[name]++;
        name = name + '(' + to_string(dbms->db_names[name]-2) + ')';
    }

    dbms->db_names[name]++;
    DataBase db(name);


    dbms->databases[dbms->db_num] = db;
    dbms->db_num++;

    cout << "Database \"" << name << "\" has been created!" << endl;
}