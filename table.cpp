#include "table.h"
Table::Table(string name){
    this->m_name = name;
    this->m_path = "";
    column_capacity = INIT_CAPACITY;
    row_capacity = INIT_CAPACITY;

    table_head.reserve(column_capacity);
    tuples.reserve(row_capacity);
}

Table::~Table(){
    vector<string>().swap(table_head);

    for(int i = 0; i < tuples.size(); i++){
        delete(tuples[i]);
    }
    vector<Tuple*>().swap(tuples);
}

void Table::Create(){
    int stat_num = 0;
    cin >> stat_num;

    if(stat_num > column_capacity)
        ExpandTableHead(stat_num);

    string tmp;
    for(int i = 0; i < stat_num; i++){
        cin >> tmp;
        table_head.push_back(tmp);
    }

}

void Table::ExpandTableHead(int x){
    column_capacity = x;
    table_head.reserve(column_capacity);
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
    for (int i = 0; i < table_head.size(); i++){
        cout << std::left << setw(20) << table_head[i] << "|";
    }
    cout << endl;
}

void Table::PrintTable(){
    string frame(21 * table_head.size() + 1, '-');

    cout << frame << endl;
    PrintTableHead();
    cout << frame << endl;

    for(int i = 0; i < tuples.size(); i++){
        tuples[i]->PrintLine();
        cout << frame << endl;
    }
}

void Table::Insert(){
    if(tuples.size() == row_capacity)
        ExpandTuples(2 * row_capacity);

    Tuple* tmp = new Tuple(table_head.size());

    tmp->Create(table_head.size());
    tmp->ModifyIndex(tuples.size()+1);

    tuples.push_back(tmp);
}

void Table::DeleteData(){
    int target_row;
    cin >> target_row;

    if(target_row > tuples.size()){
        cout << "The specified row was not found!" << endl;
        return;
    }

    tuples[target_row - 1]->~Tuple();
    for(int i = target_row - 1; i < tuples.size() - 1; i++){
        tuples[i] = tuples[i+1]; 
        int t = tuples[i]->GetIndex();
        tuples[i]->ModifyIndex(t-1);
    }
    tuples.pop_back();

    cout << "The " << target_row << "row of data has been deleted." << endl;
}

void Table::UpdateData(){
    int target_row;
    cin >> target_row;

    if(target_row > tuples.size()){
        cout << "The specified row was not found!" << endl;
        return;
    }

    tuples[target_row - 1]->Update();

    cout << "The data in row " << target_row << " is modified successfully." << endl;

}

void Table::PrintTargetRow(string attr, string val){
    int key = -1;
    for(int i = 0; i < table_head.size(); i++){
        if(table_head[i] == attr){
            key = i;
            break;
        }
    }
    if(key == -1){
        cout << "Specified attribute not found. " << endl;
        return; 
    }

    string frame(21 * table_head.size() + 1, '-');

    cout << frame << endl;
    PrintTableHead();
    cout << frame << endl;

    for(int i = 0; i < tuples.size(); i++){
        if(tuples[i]->data[key] == val){
            tuples[i]->PrintLine();
            cout << frame << endl;
        }
    }
}





Tuple::Tuple(int col_num){
    data.reserve(col_num);
    data.clear();
    m_index = 0;
}

Tuple::~Tuple(){
    vector<string>().swap(data);
}

void Tuple::PrintLine(){
    cout << "|";
    for (int i = 0; i < data.size(); i++){
        cout << std::left << setw(20) << data[i] << "|";
    }
    cout << endl;
}

void Tuple::Create(int col_num){
    string data_in;
    for(int i = 0; i < col_num; i++){
        cin >> data_in;
        data.push_back(data_in);
    }
}

void Tuple::Update(){
    string data_in;
    for(int i = 0; i < data.size(); i++){
        cin >> data_in;
        data[i] = data_in;
    }
}

int Tuple::GetIndex(){
    return m_index;
}

void Tuple::ModifyIndex(int x){
    m_index = x;
}

