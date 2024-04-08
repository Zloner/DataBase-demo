#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sds.h>

using namespace std;

struct zskiplistLevel{

}

class zskiplistNode{
    sds ele;
    double score;
    zskiplistNode* backword;
    zskiplistLevel* level;
}

#endif