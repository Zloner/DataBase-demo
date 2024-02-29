#include "function.h"

void Create(DataBases* dbms){
    string object;
    cin >> object;
    if(object == "database" || object == "DATABASE") {
        string name;
        cin >> name;
        create_db(dbms, name);
    }
    else if(object == "table" || object == "TABLE"){

    }
    else{
        cout << "illegal instruction" << endl;
    }
    return;
}

void Delete(DataBases* dbms){
    string object;
    cin >> object;
    if(object == "database" || object == "DATABASE") {
        string name;
        cin >> name;
        delete_db(dbms, name);
    }
    else if(object == "table" || object == "TABLE"){

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
        alter_db(dbms, name, new_name);
    }
    else if(object == "table" || object == "TABLE"){

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
        select_db(dbms, name);
    }
    else if(object == "table" || object == "TABLE"){

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
        show_db(dbms);
    }
    else if(object == "table" || object == "TABLE"){

    }
    else{
        cout << "illegal instruction" << endl;
    }
    return;
}