#ifndef __SDS_H__
#define __SDS_H__

#include <iostream>
#include <string.h>
#include "type.h"

using namespace std;

#define SDS_TYPE_5 0
#define SDS_TYPE_8 1
#define SDS_TYPE_16 2
#define SDS_TYPE_32 3
#define SDS_TYPE_64 4

typedef char* sds;

class __attribute__((__packed__)) Sdshdr{
protected:
    unsigned char flag;     //低3位存类型，sdshdr5的高5位存长度
    char* buf;
public:
    Sdshdr(){}
    ~Sdshdr(){}

    int sdsHdrSize();
    char* sdsReqBuf();
    char sdsReqType();
    void sdsSetType(size_t initlen);

    virtual uint64_t sdsReqLen(){};
    virtual uint64_t sdsReqAlloc(){};
    virtual void sdsSetLen(size_t len){};
    virtual void sdsSetAlloc(size_t alloc){};

    virtual void sdsCreate(){};
    virtual void sdsMakeRoom(){};
    virtual void sdsFree(){};
    virtual void sdsClear(){};

    void sdscatsds();
};

class __attribute__((__packed__)) Sdshdr5 : public Sdshdr{
public:
    uint64_t sdsReqLen();
    void sdsSetLen(size_t len_v);

    void sdsCreate();
    void sdsMakeRoom(size_t addlen);
    void sdsFree();
    void sdsClear();
};

class __attribute__((__packed__)) Sdshdr8 : public Sdshdr{
private:
    uint8_t len;        //以使用长度
    uint8_t alloc;      //总长度
public:
    uint64_t sdsReqLen();
    uint64_t sdsReqAlloc();
    void sdsSetLen(size_t len_v);
    void sdsSetAlloc(size_t alloc_v);

    void sdsCreate();
    void sdsMakeRoom(size_t addlen);
    void sdsFree();
    void sdsClear();
};

class __attribute__((__packed__)) sdshdr16 : public Sdshdr{
private:
    uint16_t len;        //以使用长度
    uint16_t alloc;      //总长度
public:
    uint64_t sdsReqLen();
    uint64_t sdsReqAlloc();
    void sdsSetLen(size_t len);
    void sdsSetAlloc(size_t alloc);

    void sdsCreate();
    void sdsMakeRoom();
    void sdsFree();
    void sdsClear();
};

class __attribute__((__packed__)) sdshdr32 : public Sdshdr{
private:
    uint32_t len;        //以使用长度
    uint32_t alloc;      //总长度
public:
    uint64_t sdsReqLen();
    uint64_t sdsReqAlloc();
    void sdsSetLen(size_t len);
    void sdsSetAlloc(size_t alloc);

    void sdsCreate();
    void sdsMakeRoom();
    void sdsFree();
    void sdsClear();
};

class __attribute__((__packed__)) sdshdr64 : public Sdshdr{
private:
    uint64_t len;        //以使用长度
    uint64_t alloc;      //总长度
public:
    uint64_t sdsReqLen();
    uint64_t sdsReqAlloc();
    void sdsSetLen(size_t len);
    void sdsSetAlloc(size_t alloc);

    void sdsCreate();
    void sdsMakeRoom();
    void sdsFree();
    void sdsClear();
};

char sdsReqType(size_t len);
int sdsHdrSize(char type);
sds sdsnewlen(const void* init, size_t initlen);
void sdssetlen(sds s, size_t s_len);
void freesds(sds s);
void clearsds(sds s);
sds sdscatsds(sds s, const sds t);
sds sdscatlen(sds s, const void *t, size_t len);
sds sdsMakeRoomFor(sds s, size_t addlen);

#endif