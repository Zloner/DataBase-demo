#include "table.h"

Table::Table(string name){
    this->m_name = name;
    this->m_path = "";
    column_capacity = INIT_CAPACITY;
    row_capacity = INIT_CAPACITY;

    table_head.clear();
    tuples.reserve(row_capacity);
}

Table::~Table(){
    map<string, Stats*>::iterator it;
    for(it = table_head.begin(); it != table_head.end(); it++)
        delete(it->second);
    
    table_head.clear();

    for(int i = 0; i < tuples.size(); i++){
        delete(tuples[i]);
    }
    vector<Tuple*>().swap(tuples);
}

bool Table::Create(){
    int stat_num = 0;
    cin >> stat_num;

    if(stat_num > column_capacity)
        ExpandTableHead(stat_num);

    char *expression, *stats, *type;
    expression = (char*)malloc(20 * sizeof(char));
    stats = (char*)malloc(20 * sizeof(char));
    type = (char*)malloc(20 * sizeof(char));
    string str_stats, str_type;

    for(int i = 0; i < stat_num; i++){
        cin >> expression;
        Stats* st = (Stats*)malloc(sizeof(Stats));
        analyse(expression, stats, type);
        str_stats = stats;
        str_type = type;

        if(table_head.find(str_stats) != table_head.end()){
            cout << "The same property name is not allowed" << endl;
            return 0;
        }

        if(str_type == "int" || str_type == "INT") 
            st->m_type = "int";
        else if(str_type == "bigint" || str_type == "BIGINT")
            st->m_type = "bigint";
        else if(str_type == "char" || str_type == "CHAR")
            st->m_type = "char";
        else if(str_type == "string" || str_type == "STRING")
            st->m_type = "string";
        else if(str_type == "float" || str_type == "FLOAT")
            st->m_type = "float";
        else{cout << "Undefined data type!" << endl; return 0;}

        st->m_index = i;
        table_head[str_stats] = st;
    }

    free(expression);
    free(stats);
    free(type);
    return 1;
}

void Table::ExpandTableHead(int x){
    column_capacity = x;
}

void Table::ExpandTuples(int x){
    row_capacity = x;
    tuples.reserve(row_capacity);
}

void Table::UpdatePath(string new_path){
    m_path = new_path;
}

void Table::Rename(string new_name){
    m_name = new_name;
}

string Table::GetName(){
    return m_name;
}

void Table::ShowInfo(){
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Name" << "|" << std::left << setw(50) << m_name << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Path" << "|" << std::left << setw(50) << m_path << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Column" << "|" << std::left << setw(50) << table_head.size() << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Line" << "|" << std::left << setw(50) << tuples.size() << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
}

void Table::PrintTableHead(){
    cout << "|";
    map<string, Stats*>::iterator it;
    for (it = table_head.begin(); it != table_head.end(); it++){
        cout << std::left << setw(20) << it->first << "|";
    }
    cout << endl;
}

void Table::PrintTable(){
    string frame(21 * table_head.size() + 1, '-');

    cout << frame << endl;
    PrintTableHead();
    cout << frame << endl;
    
    for(int i = 0; i < tuples.size(); i++){
        tuples[i]->PrintLine(&table_head);
        cout << frame << endl;
    }
}

void Table::Insert(){
    if(tuples.size() == row_capacity)
        ExpandTuples(2 * row_capacity);

    Tuple* tmp = new Tuple(table_head.size());

    tmp->Create(&table_head);
    /*map<string, Stats*>::iterator it;
    string type_t;
    int index_t;
    string str;

    for(it = table_head.begin(); it != table_head.end(); it++){
        type_t = it->second->m_type;
        index_t = it->second->m_index;
        cin >> str;
        tmp->data[index_t] = str;
    }*/

    int index = tuples.size();
    tmp->ModifyIndex(index);
    tuples.push_back(tmp);
    
}

void Table::DeleteData(string stats, string val){

    vector<int> target_row = SelectRow(stats, val);

    for(int k = 0; k < target_row.size(); k++){
        tuples[target_row[k]]->~Tuple();
        for(int i = target_row[k]; i < tuples.size() - 1; i++){
            tuples[i] = tuples[i+1]; 
            int t = tuples[i]->GetIndex();
            tuples[i]->ModifyIndex(t-1);
        }
        tuples.pop_back();

        cout << "The " << target_row[k] + 1 << " row of data has been deleted." << endl;
    }
}

void Table::UpdateData(string stats, string val){
    
    vector<int> target_row = SelectRow(stats, val);

    string op; 
    cin >> op;

    if(op == "set" || op == "SET"){
        for(int i = 0; i < target_row.size(); i++){
            tuples[target_row[i]]->Update(&table_head);
        }
    }
    else{
        cout << "illigal instruction" << endl;
        return;
    }

    //cout << "The data in row " << target_row << " is modified successfully." << endl;

}

vector<int> Table::SelectRow(string stats, string val){
    vector<int> res;
    res.reserve(10);

    if(table_head.find(stats) == table_head.end()){
        cout << "Specified attribute not found. " << endl;
        return res; 
    }
    int col_index = table_head[stats]->m_index;
    for(int i = 0; i < tuples.size(); i++)
        if(tuples[i]->data[col_index] == val)
            res.push_back(i);
/*
    int col_index = table_head[stats]->m_index;
    string type = table_head[stats]->m_type;
    if(type == "int"){
        int tmp;
        sscanf(val.c_str(), "%d", &tmp);
        for(int i = 0; i < tuples.size(); i++)
            if(tuples[i]->data[col_index].GetValue<int>() == tmp)
                res.push_back(i);gdb 
    }
    else if(type == "bigint"){
        long tmp;
        sscanf(val.c_str(), "%ld", &tmp);
        for(int i = 0; i < tuples.size(); i++)
            if(tuples[i]->data[col_index].GetValue<long>() == tmp)
                res.push_back(i);
    }
    else if(type == "char"){
        char tmp;
        sscanf(val.c_str(), "%c", &tmp);
        for(int i = 0; i < tuples.size(); i++)
            if(tuples[i]->data[col_index].GetValue<char>() == tmp)
                res.push_back(i);
    }
    else if(type == "string"){
        for(int i = 0; i < tuples.size(); i++)
            if(tuples[i]->data[col_index].GetValue<string>() == val)
                res.push_back(i);
    }
    else if(type == "float"){
        float tmp;
        sscanf(val.c_str(), "%f", &tmp);
        for(int i = 0; i < tuples.size(); i++)
            if(tuples[i]->data[col_index].GetValue<float>() == tmp)
                res.push_back(i);
    }
*/
    return res;
}


void Table::PrintTargetRow(string stats, string val){
    if(table_head.find(stats) == table_head.end()){
        cout << "Specified attribute \"" << stats << "\" not found. " << endl;
        return; 
    }

    string frame(21 * table_head.size() + 1, '-');

    cout << frame << endl;
    PrintTableHead();
    cout << frame << endl;
    
    vector<int> target_row = SelectRow(stats, val);
    
    for(int i = 0; i < target_row.size(); i++){
        tuples[target_row[i]]->PrintLine(&table_head);
        cout << frame << endl;
    }
}











Tuple::Tuple(int col_num){
    data.resize(col_num, "");
    m_index = 0;
}

Tuple::~Tuple(){
    vector<string>().swap(data);
}

void Tuple::PrintLine(map<string, Stats*>* tbh){
    cout << "|";
    map<string, Stats*>::iterator it;
    for(it = tbh->begin(); it != tbh->end(); it++){
        cout << std::left << setw(20) << data[it->second->m_index] << "|";
    }
    /*for(; begin != end; begin++){
        if(begin->second->m_type == "int")
            cout << std::left << setw(20) << data[begin->second->m_index].GetValue<int>() << "|";
        else if(begin->second->m_type == "bigint")
            cout << std::left << setw(20) << data[begin->second->m_index].GetValue<long>() << "|";
        else if(begin->second->m_type == "char")
            cout << std::left << setw(20) << data[begin->second->m_index].GetValue<char>() << "|";
        else if(begin->second->m_type == "string")
            cout << std::left << setw(20) << data[begin->second->m_index].GetValue<string>() << "|";
        else if(begin->second->m_type == "float")
            cout << std::left << setw(20) << data[begin->second->m_index].GetValue<float>() << "|";
    }
    */
}

void Tuple::Create(map<string, Stats*>* tbh){
    map<string, Stats*>::iterator it;
    string type_t;
    string new_data;
    int i = 0;

    for(it = tbh->begin(); it != tbh->end(); it++, i++){
        type_t = it->second->m_type;
        cin >> new_data;
        data[i] = new_data;
        /*if(type_t == "int")
            data[index_t].AssignValue(data[index_t].ReadValue<int>(cin));
        else if(type_t == "bigint")
            data[index_t].AssignValue(data[index_t].ReadValue<long>(cin));
        else if(type_t == "char")
            data[index_t].AssignValue(data[index_t].ReadValue<char>(cin));
        else if(type_t == "string")
            data[index_t].AssignValue(data[index_t].ReadValue<string>(cin));
        else if(type_t == "flaot")
            data[index_t].AssignValue(data[index_t].ReadValue<float>(cin));
    */
    }
    /*map<string, Stats*>::iterator it;
    string type_t;
    int index_t;
    string str;

    for(it = table_head.begin(); it != table_head.end(); it++){
        type_t = it->second->m_type;
        index_t = it->second->m_index;
        cin >> str;
        tmp->data[index_t] = str;
    }*/
}

void Tuple::Update(map<string, Stats*>* tbh){

    int index_t;
    string type_t;

    string condition;
    string tar_attr;
    string tar_val;

    cin >> condition;
    for(int i = 0; i < condition.size(); i++){
        if(condition[i] == '='){
            tar_attr = condition.substr(0, i);
            tar_val = condition.substr(i+1, condition.size()-1);
            break;
        }
    }
    index_t = tbh->find(tar_attr)->second->m_index;
    type_t = tbh->find(tar_attr)->second->m_type;

    data[index_t] = tar_val;

    /*
    if(type_t == "int")
        data[index_t].AssignValue(data[index_t].ReadValue<int>(cin));
    else if(type_t == "bigint")
        data[index_t].AssignValue(data[index_t].ReadValue<long>(cin));
    else if(type_t == "char")
        data[index_t].AssignValue(data[index_t].ReadValue<char>(cin));
    else if(type_t == "string")
        data[index_t].AssignValue(data[index_t].ReadValue<string>(cin));
    else if(type_t == "flaot")
        data[index_t].AssignValue(data[index_t].ReadValue<float>(cin));
        */
}

int Tuple::GetIndex(){
    return m_index;
}

void Tuple::ModifyIndex(int x){
    m_index = x;
}

void Tuple::PrintData(string type, int index){
    cout << std::left << setw(20) << data[index] << "|";
    /*
    if(type == "int")
        cout << std::left << setw(20) << data[index].GetValue<int>() << "|";
    else if(type == "bigint")
        cout << std::left << setw(20) << data[index].GetValue<long>() << "|";
    else if(type == "char")
        cout << std::left << setw(20) << data[index].GetValue<char>() << "|";
    else if(type == "string")
        cout << std::left << setw(20) << data[index].GetValue<string>() << "|";
    else if(type == "float")
        cout << std::left << setw(20) << data[index].GetValue<float>() << "|";
        */
}

void analyse(char* expression, char* attr, char* type){
    int flag = 0, count = 0;

    for(int i = 0; i < strlen(expression); i++){
        if(expression[i] == '('){
            flag = 1;
            count = i+1;
            attr[i] = '\0';
            continue;
        }
        else if(expression[i] == ')'){
            type[i-count] = '\0';
            count = 0;
            break;
        }
        if(count == 0)
            attr[i] = expression[i];
        else if(count != 0)
            type[i-count] = expression[i];
    }
    if(flag == 0 || count != 0){
        cout << "Illigal expression!" << endl;
    }

}