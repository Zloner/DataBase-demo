#ifndef __TABLE_H__
#define __TABLE_H__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define INIT_CAPACITY 5

class Tuple{
public:
    vector<string> data;

    Tuple(){};
    ~Tuple(){};
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

};

#endif