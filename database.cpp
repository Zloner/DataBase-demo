#include "database.h"

using namespace std;


DataBase::DataBase(string db_name){
    char* db_path;
    db_path = (char*)malloc(sizeof(char) * 64);
    getcwd(db_path, 64);

    m_path = db_path;
    m_path.push_back('/');
    m_path = m_path + db_name;

    free(db_path);

    m_name = db_name;

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

void DataBase::ShowInfo(){
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Name" << "|" << std::left << setw(50) << m_name << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Index" << "|" << std::left << setw(50) << m_index << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Path" << "|" << std::left << setw(50) << m_path << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Table capacity" << "|" << std::left << setw(50) << tb_capacity << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Table num" << "|" << std::left << setw(50) << tb_num << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
}

string DataBase::GetName(){
    return m_name;
}

void DataBase::ModifyIndex(char mode, int x){
    if(mode == 'J'){
        m_index = m_index + x;
    }
    else if(mode == 'Z'){
        m_index = x;
    }
}

void DataBase::Rename(string new_name){
    m_name = new_name;
    return;
}

void DataBase::UpdatePath(string new_path){
    m_path = new_path;
}

string DataBase::GetPath(){
    return m_path;
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

    tables.push_back(tb);
    tb_num++;

    cout << "Table \"" << name << "\" has been created!" << endl;
}

void DataBase::select_tb(string name){
    if(!this->exist_tb(name)){
        cout << "Table \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    for(int i = 0; i < tb_num; i++){
        if(tables[i]->GetName() == name){
            tables[i]->PrintTable();
            return;
        }
    }
}

bool DataBase::exist_tb(string name){
    return !(tb_num == 0 || tb_names.find(name) == tb_names.end());
}

void DataBase::insert_into_tb(string name){
    if(!this->exist_tb(name)){
        cout << "Table \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    for(int i = 0; i < tb_num; i++){
        if(tables[i]->GetName() == name){
            tables[i]->Insert();
            return;
        }
    }
}

void DataBase::show_tb(){
    cout << "There are " << tb_num << " tables now." << endl;
    map<string, int>::iterator it;
    for (it = tb_names.begin(); it != tb_names.end(); it++){
        cout << it->first << endl;
    }
}

void DataBase::drop_tb(string name){
    if(!this->exist_tb(name)){
        cout << "Table \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    tb_names.erase(name);

    for(int i = 0; i < tb_num; i++){
        if(tables[i]->GetName() == name){
            tables[i]->~Table();
            int j;
            for(j = i; j < tb_num-1; j++)
                tables[j] = tables[j+1];
            tables.pop_back();
            tb_num--;

            cout << "Table \"" << name << "\" has been deleted!" << endl;
            return;
        }
    }
}

void DataBase::alter_tb(string name, string new_name){
    if(!exist_tb(name)){
        cout << "Table \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    string tmp;
    tmp = new_name;
    while(tb_names.find(tmp) != tb_names.end()){
        tmp = new_name;
        tb_names[tmp]++;
        tmp = tmp + '(' + to_string(tb_names[tmp]) + ')';
    }
    new_name = tmp;

    tb_names[new_name] = 0;
    tb_names.erase(name);

    for(int i = 0; i < tb_num; i++){
        if(tables[i]->GetName() == name){
            char* tpath = (char*)malloc(sizeof(char) * 64);
            getcwd(tpath, 64);

            tables[i]->UpdatePath(tpath + '/' + new_name);
            tables[i]->Rename(new_name);

            free(tpath);
            cout << "Table \"" << name << "\" has rename as \"" << new_name << "\"." << endl;
            return;
        }
    }
}

void DataBase::delete_tb_data(string name){
    if(!exist_tb(name)){
        cout << "Table \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    for(int i = 0 ; i < tb_num; i++){
        if(tables[i]->GetName() == name){
            tables[i]->DeleteData();
        }
    }
}

void DataBase::update_tb_data(string name){
    if(!exist_tb(name)){
        cout << "Table \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    for(int i = 0 ; i < tb_num; i++){
        if(tables[i]->GetName() == name){
            tables[i]->UpdateData();
        }
    }
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

    databases.push_back(db);
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
            databases.pop_back();
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
    
    string tmp = new_name;
    while(db_names.find(tmp) != db_names.end()){
        tmp = new_name;
        db_names[tmp]++;
        tmp = tmp + '(' + to_string(db_names[tmp]) + ')';
    }
    new_name = tmp;

    db_names[new_name] = 0;
    db_names.erase(name);

    for(int i = 0; i < db_num; i++){
        if(databases[i]->GetName() == name){
            databases[i]->Rename(new_name);

            char* dpath;
            dpath = (char*)malloc(sizeof(char) * 64);
            getcwd(dpath, 64);

            databases[i]->UpdatePath(dpath + '/' + new_name);
            free(dpath);

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
            databases[i]->ShowInfo();
            return;
        }
    }
    cout << "Operation failure!(Select)" << endl;
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
            db_path = databases[i]->GetPath();
            cout << "The currently used database is \"" << name << "\"!" << endl;
            return;
        }
    }
    cout << "Operation failure!(Use)" << endl;
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

void DataBases::select_tb_port(){
    for(int i = 0; i < db_num; i++){
        if(databases[i]->GetPath() == db_path){
            string name;
            cin >> name;
            databases[i]->select_tb(name);
            return;
        }
    }

    cout << "No database is currently in use!" << endl;
}

void DataBases::insert_into_tb_port(){
    for(int i = 0; i < db_num; i++){
        if(databases[i]->GetPath() == db_path){
            string name;
            cin >> name;
            databases[i]->insert_into_tb(name);
            return;
        }
    }

    cout << "No database is currently in use!" << endl;
}

void DataBases::show_tb_port(){
    for(int i = 0; i < db_num; i++){
        if(databases[i]->GetPath() == db_path){
            databases[i]->show_tb();
            return;
        }
    }

    cout << "No database is currently in use!" << endl;
}

void DataBases::drop_tb_port(){
    for(int i = 0; i < db_num; i++){
        if(databases[i]->GetPath() == db_path){
            string name;
            cin >> name;
            databases[i]->drop_tb(name);
            return;
        }
    }

    cout << "No database is currently in use!" << endl;
}

void DataBases::alter_tb_port(){
    for(int i = 0; i < db_num; i++){
        if(databases[i]->GetPath() == db_path){
            string name, new_name;
            cin >> name >> new_name;
            databases[i]->alter_tb(name, new_name);
            return;
        }
    }
}

void DataBases::delete_tb_port(){
    for(int i = 0; i < db_num; i++){
        if(databases[i]->GetPath() == db_path){
            string name;
            cin >> name;
            databases[i]->delete_tb_data(name);
            return;
        }
    }
}

void DataBases::update_tb_port(){
    for(int i = 0; i < db_num; i++){
        if(databases[i]->GetPath() == db_path){
            string name;
            cin >> name;
            databases[i]->update_tb_data(name);
            return;
        }
    }
}