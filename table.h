#ifndef __TABLE_H__
#define __TABLE_H__

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <string.h>

using namespace std;

#define INIT_CAPACITY 5

class Stats{
public:
    int m_index;
    string m_type;
};

class CustomData{
private:
    void* ptr{nullptr};
public:
    
    CustomData(){}
    ~CustomData(){
        free(ptr);
    }
    template<class T>
    void AssignValue(T data){
        ptr = &data;
    }
    template<class T>
    T GetValue(){
        T *result = (T*)ptr;
        return *result;
    }
    template <class T>
    T ReadValue(std::istream &stream){
        T i;
        stream >> i;
        return i;
    }
};

class Tuple{
public:
    vector<string> data;
    int m_index;

    Tuple(int col_num);
    ~Tuple();
    void PrintLine(map<string, Stats*>* tbh);
    void PrintData(string type, int index);
    void Create(map<string, Stats*>* tbh);
    void Update(map<string, Stats*>* tbh);
    int GetIndex();
    void ModifyIndex(int x);
};

class Table{
private:
    string m_path;
    string m_name;

    map<string, Stats*> table_head;
    vector<Tuple*> tuples;
    int column_capacity;
    int row_capacity;
    

public:
    Table(string name);
    ~Table();
    bool Create();
    void ExpandTableHead(int x);
    void ExpandTuples(int x);
    void UpdatePath(string new_path);
    void Rename(string new_name);
    string GetName();
    void PrintTableHead();
    void PrintTable();
    void ShowInfo();
    void Insert();
    void DeleteData(string stats, string val);
    void UpdateData(string stats, string val);
    vector<int> SelectRow(string stats, string val);
    void PrintTargetRow(string stats, string val);

};

void analyse(char* expression, char* attr, char* type);

#endif