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
        table_head[i] = tmp;
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

