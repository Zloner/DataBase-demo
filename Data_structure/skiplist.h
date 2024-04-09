#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <type.h>
#include "sds.h"

using namespace std;

#define ZSKIPLIST_MAXLEVEL 64
#define ZSKIPLIST_P 0.25

class zskiplist{
private:
    zskiplistNode* header, *tail;
    unsigned long length;
    int level;
public:
    int zslReqlevel();
    zskiplistNode* zslReqHeader();
    zskiplistNode* zslReqTail();
    unsigned long zslReqLen();

    void zslSetlength(unsigned long length_v);

};

class zskiplistNode{
private:
    Sdshdr ele;
    double score;
    zskiplistNode* backword;
    struct zskiplistLevel{
        zskiplistNode* forword;
        unsigned int span;
    }*level;
public:
    int zslRandomlevel();
};

#endif