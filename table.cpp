#include "table.h"
Table::Table(string name){
    this->name = name;
    this->path = "";
    column_capacity = INIT_CAPACITY;
    line_capacity = INIT_CAPACITY;

    table_head.reserve(column_capacity);
    tuples.reserve(line_capacity);
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
    line_capacity = x;
    tuples.reserve(line_capacity);
}

void Table::UpdatePath(string new_path){
    path = new_path;
}

string Table::GetName(){
    return name;
}

void Table::ShowInfo(){
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Name" << "|" << std::left << setw(50) << name << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "|" << std::left << setw(20) << "Path" << "|" << std::left << setw(50) << path << "|" << endl;
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
    if(tuples.size() == line_capacity)
        ExpandTuples(2 * line_capacity);

    Tuple* tmp = new Tuple(table_head.size());

    tmp->Create(table_head.size());

    tuples.push_back(tmp);
}


Tuple::Tuple(int col_num){
    data.reserve(col_num);
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
