#ifndef __TABLE_H__
#define __TABLE_H__

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

#define INIT_CAPACITY 5

class Tuple{
public:
    vector<string> data;

    Tuple(int col_num);
    ~Tuple();
    void PrintLine();
    void Create(int col_num);
};

class Table{
private:
    string path;
    string name;
    vector<string> table_head;
    vector<Tuple*> tuples;
    int column_capacity;
    int line_capacity;
    

public:
    Table(string name);
    ~Table();
    void Create();
    void ExpandTableHead(int x);
    void ExpandTuples(int x);
    void UpdatePath(string new_path);
    string GetName();
    void PrintTableHead();
    void PrintTable();
    void ShowInfo();
    void Insert();
};

#endif