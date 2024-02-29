#include <iostream>
#include "function.h"

using namespace std;

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
            Delete(DBMS);
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
        else if(op == "EXIT" || op == "exit"){
            cout << "== EXIT DBMS ==" << endl;
            ClearDBMS(DBMS);
            free(DBMS);
            DBMS = NULL;
            break;
        }
        else{
            cout << "illegal instruction" << endl;
        }
        
    }
}