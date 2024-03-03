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
    int m_index;

    Tuple(int col_num);
    ~Tuple();
    void PrintLine();
    void Create(int col_num);
    void Update();
    void ModifyIndex(char mode, int x);
};

class Table{
private:
    string m_path;
    string m_name;
    vector<string> table_head;
    vector<Tuple*> tuples;
    int column_capacity;
    int row_capacity;
    

public:
    Table(string name);
    ~Table();
    void Create();
    void ExpandTableHead(int x);
    void ExpandTuples(int x);
    void UpdatePath(string new_path);
    void Rename(string new_name);
    string GetName();
    void PrintTableHead();
    void PrintTable();
    void ShowInfo();
    void Insert();
    void DeleteData();
    void UpdateData();
};

#endif