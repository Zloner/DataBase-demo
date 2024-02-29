#include "database.h"

using namespace std;


DataBase::DataBase(string db_name){
    char* db_path;
    db_path = (char*)malloc(sizeof(char) * 64);
    getcwd(db_path, 64);

    path = db_path;
    path.push_back('/');
    path = path + db_name;

    free(db_path);

    name = db_name;

    tb_names.clear();
    tb_capacity = INIT_CAPACITY;
    tables = (Table*)malloc(sizeof(Table) * tb_capacity);
    table_num = 0;

}
void DataBase::Delete_Database(){

}
void DataBase::Alter_Database(){

}
Table DataBase::Find_Table(){

}

void InitDBMS(DataBases* dbms){
    dbms->db_num = 0;
    dbms->db_capacity = INIT_CAPACITY;
    dbms->db_names.clear();
    dbms->databases.reserve(dbms->db_capacity);
}

void ExpandDBMS(DataBases* dbms){
    dbms->db_capacity *= 2;
    dbms->databases.reserve(dbms->db_capacity);
}

void ClearDBMS(DataBases* dbms){
    for(int i = 0; i < dbms->databases.size(); i++){
        delete(dbms->databases[i]);
    }
    vector<DataBase*>().swap(dbms->databases);
}

void create_db(DataBases* dbms, string name){

    if(dbms->db_num == dbms->db_capacity)
        ExpandDBMS(dbms);
    
    if(dbms->db_names.find(name) != dbms->db_names.end()){
        dbms->db_names[name]++;
        name = name + '(' + to_string(dbms->db_names[name]) + ')';
    }

    dbms->db_names.insert(map<string, int>::value_type(name, 0));

    DataBase* db = new DataBase(name);
    db->index = dbms->db_num + 1;

    dbms->databases[dbms->db_num] = db;
    dbms->db_num++;

    cout << "Database \"" << name << "\" has been created!" << endl;
}

void delete_db(DataBases* dbms, string name){
    if(dbms->db_num == 0 || dbms->db_names.find(name) == dbms->db_names.end()){
        cout << "Database \"" << name << "\" doesn't exist!" << endl;
        return;
    }
    
    dbms->db_names.erase(name);
    for(int i = 0; i < dbms->db_num; i++){
        if(dbms->databases[i]->name == name){
            int j;
            for(j = i; j < dbms->db_num-1; j++){
                dbms->databases[j] = dbms->databases[j+1];
                dbms->databases[j]->index--;
            }
            delete(dbms->databases[j]);
            dbms->db_num--;
            break;
        }
    }
    
}

void alter_db(DataBases* dbms, string name, string new_name){
    if(dbms->db_num == 0 || dbms->db_names.find(name) == dbms->db_names.end()){
        cout << "Database \"" << name << "\" doesn't exist!" << endl;
        return;
    }
    
    if(dbms->db_names.find(new_name) != dbms->db_names.end()){
        dbms->db_names[new_name]++;
        new_name = new_name + '(' + to_string(dbms->db_names[new_name]) + ')';
    }
    dbms->db_names[new_name] = 0;
    dbms->db_names.erase(name);

    for(int i = 0; i < dbms->db_num; i++){
        if(dbms->databases[i]->name == name){
            dbms->databases[i]->name = new_name;

            char* db_path;
            db_path = (char*)malloc(sizeof(char) * 64);
            getcwd(db_path, 64);

            dbms->databases[i]->path = db_path + '/' + new_name;
            free(db_path);

            break;
        }
    }
}

void select_db(DataBases* dbms, string name){
    if(dbms->db_num == 0 || dbms->db_names.find(name) == dbms->db_names.end()){
        cout << "Database \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    for(int i = 0; i < dbms->db_num; i++){
        if(dbms->databases[i]->name == name){
            cout << "------------------------------------------------------------------------" << endl;
            cout << "|" << std::left << setw(20) << "Name" << "|" << std::left << setw(50) << dbms->databases[i]->name << "|" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            cout << "|" << std::left << setw(20) << "Index" << "|" << std::left << setw(50) << dbms->databases[i]->index << "|" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            cout << "|" << std::left << setw(20) << "Path" << "|" << std::left << setw(50) << dbms->databases[i]->path << "|" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            cout << "|" << std::left << setw(20) << "Table capacity" << "|" << std::left << setw(50) << dbms->databases[i]->tb_capacity << "|" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            cout << "|" << std::left << setw(20) << "Table num" << "|" << std::left << setw(50) << dbms->databases[i]->table_num << "|" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            break;
        }
    }
}

void show_db(DataBases* dbms){
    cout << "There are " << dbms->db_num << " databases now." << endl;
    map<string, int>::iterator it;
    for (it = dbms->db_names.begin(); it != dbms->db_names.end(); it++){
        cout << it->first << endl;
    }
}