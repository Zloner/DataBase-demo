#include "function.h"

void Create(DataBases* dbms){
    string object;
    cin >> object;
    if(object == "database" || object == "DATABASE") {
        string name;
        cin >> name;
        dbms->create_db(name);
    }
    else if(object == "table" || object == "TABLE"){
        dbms->create_tb_port();
    }
    else{
        cout << "illegal instruction" << endl;
    }
    return;
}

void Drop(DataBases* dbms){
    string object;
    cin >> object;
    if(object == "database" || object == "DATABASE") {
        string name;
        cin >> name;
        dbms->drop_db(name);
    }
    else if(object == "table" || object == "TABLE"){
        dbms->drop_tb_port();
    }
    else{
        cout << "illegal instruction" << endl;
    }
    return;
}

void Alter(DataBases* dbms){
    string object;
    cin >> object;
    if(object == "database" || object == "DATABASE") {
        string name, new_name;
        cin >> name >> new_name;
        dbms->alter_db(name, new_name);
    }
    else if(object == "table" || object == "TABLE"){
        dbms->alter_tb_port();
    }
    else{
        cout << "illegal instruction" << endl;
    }
    return;
}

void Select(DataBases* dbms){
    string object;
    cin >> object;
    if(object == "database" || object == "DATABASE") {
        string name;
        cin >> name;
        dbms->select_db(name);
    }
    else if(object == "table" || object == "TABLE"){
        dbms->select_tb_port();
    }
    else{
        cout << "illegal instruction" << endl;
    }
    return;
}

void Show(DataBases* dbms){
    string object;
    cin >> object;
    if(object == "database" || object == "DATABASE") {
        dbms->show_db();
    }
    else if(object == "table" || object == "TABLE"){
        dbms->show_tb_port();
    }
    else{
        cout << "illegal instruction" << endl;
    }
    return;
}

void Use(DataBases* dbms){
    string name;
    cin >> name;
    
    dbms->use_db(name); 
}

void InsertInto(DataBases* dbms){
    dbms->insert_into_tb_port();
}

void Delete(DataBases* dbms){
    dbms->delete_tb_port();
}

void Update(DataBases* dbms){
    dbms->update_tb_port();
}
