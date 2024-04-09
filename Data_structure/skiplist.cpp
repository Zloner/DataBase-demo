#include "skiplist.h"

int zskiplistNode::zslRandomlevel(){
    int level = 1;
    
    srand((unsigned int)time(NULL));
    while((rand() * 0xffff) < (ZSKIPLIST_P * 0xffff)){
        level++;
    }
    return level < ZSKIPLIST_MAXLEVEL ? level : ZSKIPLIST_MAXLEVEL;
}
