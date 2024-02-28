#include <iostream>
#include "database.h"

using namespace std;

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
    cout << "create" << endl;
    return;
}

void Delete(){
    cout << "delete" << endl;
    return;
}

void Alter(){
    cout << "alter" << endl;
    return;
}

void Select(){
    cout << "select" << endl;
    return;
}

int main(){

    string op;
    DataBases* DBMS;

    cout << "<<DBMS demo1>>" << endl;

    DBMS = (DataBases*)malloc(sizeof(DataBases));
    if(!DBMS){
        cout << "run out of memory" << endl;
        return 0;
    }

    InitDBMS(DBMS);

    while(1){
        
        cout << ">";
        cin >> op;
        if(op == "CREATE" || op == "create"){
            Create(DBMS);
        }
        else if(op == "DELETE" || op == "delete"){
            Delete();
        }
        else if(op == "ALTER" || op == "alter"){
            Alter();
        }
        else if(op == "SELECT" || op == "select"){
            Select();
        }
        else if(op == "EXIT" || op == "exit"){
            cout << "exit DBMS" << endl;
            free(DBMS);
            DBMS = NULL;
            break;
        }
        else{
            cout << "illegal instruction" << endl;
        }
        
    }
}