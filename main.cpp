#include <iostream>
#include "function.h"

using namespace std;

int main(){

    string op;
    
    DataBases *DBMS = new DataBases();
    if(!DBMS){
        cout << "run out of memory" << endl;
        return 0;
    }
    
    cout << "<<DBMS demo1>>" << endl;

    while(1){
        
        cout << ">";
        cin >> op;
        if(op == "CREATE" || op == "create"){
            Create(DBMS);
        }
        else if(op == "DROP" || op == "drop"){
            Drop(DBMS);
        }
        else if(op == "ALTER" || op == "alter"){
            Alter(DBMS);
        }
        else if(op == "SELECT" || op == "select"){
            Select(DBMS);
        }
        else if(op == "SHOW" || op == "show"){
            Show(DBMS);
        }
        else if(op == "USE" || op == "use"){
            Use(DBMS);
        }
        else if(op == "INSERT" || op == "insert"){
            InsertInto(DBMS);
        }
        else if(op == "DELETE" || op == "delete"){
            Delete(DBMS);
        }
        else if(op == "UPDATE" || op == "update"){
            Update(DBMS);
        }
        else if(op == "EXIT" || op == "exit"){
            cout << "== EXIT DBMS ==" << endl;
            delete(DBMS);
            break;
        }
        else{
            cout << "illegal instruction" << endl;
        }
        
        char c;
        while ((c = getchar()) != '\n');
    }
}