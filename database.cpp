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

    tables.clear();
    tb_capacity = INIT_CAPACITY;
    tb_num = 0;

}

DataBase::~DataBase(){
    map<string, Table*>::iterator it; 
    for(it = tables.begin(); it != tables.end(); it++){
        delete(it->second);
    }

    tables.clear();
}

void DataBase::ShowInfo(){
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Name" << "|" << std::left << setw(50) << m_name << "|" << endl;
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
}

void DataBase::create_tb(string name){
    if(tb_num == tb_capacity)
        this->ExpandDB();
    
    int count = 1;
    string tmp = name;
    while(tables.find(tmp) != tables.end()){
        tmp = name;
        tmp = tmp + '(' + to_string(count) + ')';
        count++;
    }
    name = tmp;

    Table* tb = new Table(name);
    if(!tb->Create()) return;
    tb->UpdatePath(this->GetPath() + '/' + name);

    tables[name] = tb;
    tb_num++;
    cout << "Table \"" << name << "\" has been created!" << endl;
}

void DataBase::select_tb(string name){
    if(!this->exist_tb(name)){
        cout << "Table \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    string condition;
    cin >> condition;
    if(condition == "*"){
        tables[name]->PrintTable();
    }
    else{
        for(int i = 0; i < condition.size(); i++){
            if(condition[i] == '='){
                string tar_attr = condition.substr(0, i);
                string tar_val = condition.substr(i+1, condition.size()-1);
                tables[name]->PrintTargetRow(tar_attr, tar_val);
            }
        }
    }
}

bool DataBase::exist_tb(string name){
    return !(tb_num == 0 || tables.find(name) == tables.end());
}

void DataBase::insert_into_tb(string name){
    if(!this->exist_tb(name)){
        cout << "Table \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    tables[name]->Insert();
}

void DataBase::show_tb(){
    cout << "There are " << tb_num << " tables now." << endl;
    map<string, Table*>::iterator it;
    for (it = tables.begin(); it != tables.end(); it++){
        cout << it->first << endl;
    }
}

void DataBase::drop_tb(string name){
    if(!this->exist_tb(name)){
        cout << "Table \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    tables[name]->~Table();
    tables.erase(name);
    tb_num--;

    cout << "Table \"" << name << "\" has been deleted!" << endl;
    
}

void DataBase::alter_tb(string name, string new_name){
    if(!exist_tb(name)){
        cout << "Table \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    int count = 1;
    string tmp;
    tmp = new_name;
    while(tables.find(tmp) != tables.end()){
        tmp = new_name;
        tmp = tmp + '(' + to_string(count) + ')';
        count++;
    }
    new_name = tmp;

    Table* point = tables[name];
    tables.erase(name);
    tables[new_name] = point;

    char* tpath = (char*)malloc(sizeof(char) * 64);
    getcwd(tpath, 64);
    string new_path = tpath;
    tables[new_name]->UpdatePath(new_path + '/' + new_name);
    
    tables[new_name]->Rename(new_name);

    free(tpath);
    cout << "Table \"" << name << "\" has rename as \"" << new_name << "\"." << endl;
    
}

void DataBase::delete_tb_data(string name){
    if(!exist_tb(name)){
        cout << "Table \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    string condition;
    cin >> condition;
    for(int i = 0; i < condition.size(); i++){
        if(condition[i] == '='){
            string tar_attr = condition.substr(0, i);
            string tar_val = condition.substr(i+1, condition.size()-1);
            tables[name]->DeleteData(tar_attr, tar_val);
        }
    }
}

void DataBase::update_tb_data(string name){
    if(!exist_tb(name)){
        cout << "Table \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    string condition;
    cin >> condition;
    for(int i = 0; i < condition.size(); i++){
        if(condition[i] == '='){
            string tar_attr = condition.substr(0, i);
            string tar_val = condition.substr(i+1, condition.size()-1);
            tables[name]->UpdateData(tar_attr, tar_val);
        }
    }
}









DataBases::DataBases(){
    db_num = 0;
    db_capacity = INIT_CAPACITY;
    databases.clear();
    db_path = "";
    db_name = "";
}

DataBases::~DataBases(){
    map<string, DataBase*>::iterator it;
    for(it = databases.begin(); it != databases.end(); it++){
        delete(it->second);
    }
    //malloc_trim(0);
}

void DataBases::ExpandDBMS(){
    db_capacity *= 2;
}

void DataBases::create_db(string name){

    if(db_num == db_capacity)
        this->ExpandDBMS();
    
    string tmp = name;
    int count = 1;
    while(databases.find(tmp) != databases.end()){
        tmp = name;
        tmp = tmp + '(' + to_string(count) + ')';
        count++;
    }
    name = tmp;

    DataBase* db = new DataBase(name);

    databases.insert(map<string, DataBase*>::value_type(name, db));

    db_num++;

    cout << "Database \"" << name << "\" has been created!" << endl;
}

void DataBases::drop_db(string name){
    if(!this->exist_db(name)){
        cout << "Database \"" << name << "\" doesn't exist!" << endl;
        return;
    }
    
    delete(databases[name]);
    databases.erase(name);
    db_num--;

    cout << "Database \"" << name << "\" has been deleted!" << endl;
    return;
}
    

void DataBases::alter_db(string name, string new_name){
    if(!this->exist_db(name)){
        cout << "Database \"" << name << "\" doesn't exist!" << endl;
        return;
    }
    
    string tmp = new_name;
    int count = 1;
    while(databases.find(tmp) != databases.end()){
        tmp = new_name;
        tmp = tmp + '(' + to_string(count) + ')';
        count++;
    }
    new_name = tmp;

    DataBase* point = databases[name];
    databases.erase(name);
    databases[new_name] = point;

    databases[new_name]->Rename(new_name);

    char* dpath;
    dpath = (char*)malloc(sizeof(char) * 64);
    getcwd(dpath, 64);
    string new_path = dpath;
    databases[new_name]->UpdatePath(new_path + '/' + new_name);
    free(dpath);

    cout << "Database \"" << name << "\" has been renamed as \"" << new_name << "\"" << endl;

    return;
}

void DataBases::select_db(string name){
    if(!this->exist_db(name)){
        cout << "Database \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    databases[name]->ShowInfo();
    return;
}

void DataBases::show_db(){
    cout << "There are " << db_num << " databases now." << endl;
    map<string, DataBase*>::iterator it;
    for (it = databases.begin(); it != databases.end(); it++){
        cout << it->first << endl;
    }
}

bool DataBases::exist_db(string name){
    return !(db_num == 0 || databases.find(name) == databases.end());
}

void DataBases::use_db(string name){
    if(!this->exist_db(name)){
        cout << "Database \"" << name << "\" doesn't exist!" << endl;
        return;
    }

    db_name = name;
    db_path = databases[name]->GetPath();
    cout << "The currently used database is \"" << name << "\"!" << endl;
    return;
}

void DataBases::create_tb_port(){
    if(db_name == ""){
        cout << "No database is currently in use!" << endl;
        return;
    }

    if(databases[db_name]->GetPath() == db_path){
        string name;
        cin >> name;
        databases[db_name]->create_tb(name);
        return;
    }
    else{
        cout << "The database name does not match the path!" << endl;
    }
}

void DataBases::select_tb_port(){
    if(db_name == ""){
        cout << "No database is currently in use!" << endl;
        return;
    }
    
    if(databases[db_name]->GetPath() == db_path){
        string name;
        cin >> name;
        databases[db_name]->select_tb(name);
        return;
    }
    else{
        cout << "The database name does not match the path!" << endl;
    }
}

void DataBases::insert_into_tb_port(){
    if(db_name == ""){
        cout << "No database is currently in use!" << endl;
        return;
    }
    if(databases[db_name]->GetPath() == db_path){
        string name;
        cin >> name;
        databases[db_name]->insert_into_tb(name);
        return;
    }
    else{
        cout << "The database name does not match the path!" << endl;
    }
}

void DataBases::show_tb_port(){
    if(db_name == ""){
        cout << "No database is currently in use!" << endl;
        return;
    }
    
    if(databases[db_name]->GetPath() == db_path){
        databases[db_name]->show_tb();
        return;
    }
    else{
        cout << "The database name does not match the path!" << endl;
    }
}

void DataBases::drop_tb_port(){
    if(db_name == ""){
        cout << "No database is currently in use!" << endl;
        return;
    }
    
    if(databases[db_name]->GetPath() == db_path){
        string name;
        cin >> name;
        databases[db_name]->drop_tb(name);
        return;
    }
    else{
        cout << "The database name does not match the path!" << endl;
    }
}

void DataBases::alter_tb_port(){
    if(db_name == ""){
        cout << "No database is currently in use!" << endl;
        return;
    }
    
    if(databases[db_name]->GetPath() == db_path){
        string name, new_name;
        cin >> name >> new_name;
        databases[db_name]->alter_tb(name, new_name);
        return;
    }
    else{
        cout << "The database name does not match the path!" << endl;
    }
}

void DataBases::delete_tb_port(){
    if(db_name == ""){
        cout << "No database is currently in use!" << endl;
        return;
    }
    
    if(databases[db_name]->GetPath() == db_path){
        string name;
        cin >> name;
        databases[db_name]->delete_tb_data(name);
        return;
    }
    else{
        cout << "The database name does not match the path!" << endl;
    }
}

void DataBases::update_tb_port(){
    if(db_name == ""){
        cout << "No database is currently in use!" << endl;
        return;
    }
    
    if(databases[db_name]->GetPath() == db_path){
        string name;
        cin >> name;
        databases[db_name]->update_tb_data(name);
        return;
    }
    else{
        cout << "The database name does not match the path!" << endl;
    }
}