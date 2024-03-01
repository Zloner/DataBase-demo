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
    tables.reserve(tb_capacity);
    tb_num = 0;

}

DataBase::~DataBase(){
    for(int i = 0; i < tables.size(); i++){
        delete(tables[i]);
    }

    vector<Table*>().swap(tables);
}

void DataBase::Show_Info(){
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Name" << "|" << std::left << setw(50) << name << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Index" << "|" << std::left << setw(50) << index << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Path" << "|" << std::left << setw(50) << path << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Table capacity" << "|" << std::left << setw(50) << tb_capacity << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Table num" << "|" << std::left << setw(50) << tb_num << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
}

string DataBase::GetName(){
    return name;
}

void DataBase::ModifyIndex(char mode, int x){
    if(mode == 'J'){
        index = index + x;
    }
    else if(mode == 'Z'){
        index = x;
    }
}

void DataBase::Rename(string new_name){
    name = new_name;
    return;
}

void DataBase::UpdatePath(string new_path){
    path = new_path;
}

string DataBase::GetPath(){
    return path;
}

void DataBase::ExpandDB(){
    tb_capacity *= 2;
    tables.reserve(tb_capacity);
}

void DataBase::create_tb(string name){
    if(tb_num == tb_capacity)
        this->ExpandDB();
    
    string tmp = name;
    while(tb_names.find(tmp) != tb_names.end()){
        tmp = name;
        tb_names[tmp]++;
        tmp = tmp + '(' + to_string(tb_names[tmp]) + ')';
    }
    name = tmp;

    tb_names[name] = 0;

    Table* tb = new Table(name);
    tb->Create();
    tb->UpdatePath(this->GetPath() + '/' + name);

    tables[tb_num] = tb;
    tb_num++;

    cout << "Table \"" << name << "\" has been created!" << endl;
}




DataBases::DataBases(){
    db_num = 0;
    db_capacity = INIT_CAPACITY;
    db_names.clear();
    databases.reserve(db_capacity);
    db_path = "";
}

DataBases::~DataBases(){
    for(int i = 0; i < databases.size(); i++){
        delete(databases[i]);
    }
    vector<DataBase*>().swap(databases);
}

void DataBases::ExpandDBMS(){
    db_capacity *= 2;
    databases.reserve(db_capacity);
}

void DataBases::create_db(string name){

    if(db_num == db_capacity)
        this->ExpandDBMS();
    
    string tmp = name;
    while(db_names.find(tmp) != db_names.end()){
        tmp = name;
        db_names[tmp]++;
        tmp = tmp + '(' + to_string(db_names[tmp]) + ')';
    }
    name = tmp;

    db_names.insert(map<string, int>::value_type(name, 0));

    DataBase* db = new DataBase(name);
    db->ModifyIndex('Z', db_num + 1);

    databases[db_num] = db;
    db_num++;

    cout << "Database \"" << name << "\" has been created!" << endl;
}

void DataBases::drop_db(string name){
    if(!this->exist_db(name)){
        cout << "Database \"" << name << "\" doesn't exist!" << endl;
        return;
    }
    
    db_names.erase(name);
    for(int i = 0; i < db_num; i++){
        if(databases[i]->GetName() == name){
            databases[i]->~DataBase();
            int j;
            for(j = i; j < db_num-1; j++){
                databases[j] = databases[j+1];
                databases[j]->ModifyIndex('J', -1);
            }
            databases[j] = NULL;
            db_num--;

            cout << "Database \"" << name << "\" has been deleted!" << endl;
            return;
        }
    }

    cout << "Operation failure!(Delete)" << endl;
}
    

void DataBases::alter_db(string name, string new_name){
    if(!this->exist_db(name)){
        cout << "Database \"" << name << "\" doesn't exist!" << endl;
        return;
    }
    
    string tmp = name;
    while(db_names.find(tmp) != db_names.end()){
        tmp = name;
        db_names[tmp]++;
        tmp = tmp + '(' + to_string(db_names[tmp]) + ')';
    }
    name = tmp;

    db_names[new_name] = 0;
    db_names.erase(name);

    for(int i = 0; i < db_num; i++){
        if(databases[i]->GetName() == name){
            databases[i]->Rename(new_name);

            char* db_path;
            db_path = (char*)malloc(sizeof(char) * 64);
            getcwd(db_path, 64);

            databases[i]->UpdatePath(db_path + '/' + new_name);
            free(db_path);

            cout << "Database \"" << name << "\" has been renamed as \"" << new_name << "\"" << endl;

            return;
        }
    }
    cout << "Operation failure!(Alter)" << endl;
}

void DataBases::select_db(string name){
    if(!this->exist_db(name)){
        cout << "Database \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    for(int i = 0; i < db_num; i++){
        if(databases[i]->GetName() == name){
            databases[i]->Show_Info();
            break;
        }
    }
}

void DataBases::show_db(){
    cout << "There are " << db_num << " databases now." << endl;
    map<string, int>::iterator it;
    for (it = db_names.begin(); it != db_names.end(); it++){
        cout << it->first << endl;
    }
}

bool DataBases::exist_db(string name){
    return !(db_num == 0 || db_names.find(name) == db_names.end());
}

void DataBases::use_db(string name){
    if(!this->exist_db(name)){
        cout << "Database \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    for(int i = 0; i < db_num; i++){
        if(databases[i]->GetName() == name){
            databases[i]->UpdatePath(db_path);
            cout << "The currently used database is \"" << name << "\"!" << endl;
            return;
        }
    }
}

void DataBases::create_tb_port(){
    for(int i = 0; i < db_num; i++){
        if(databases[i]->GetPath() == db_path){
            string name;
            cin >> name;
            databases[i]->create_tb(name);
            return;
        }
    }

    cout << "No database is currently in use!" << endl;
}