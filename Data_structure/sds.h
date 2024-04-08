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

template <class TYPE>
class __attribute__((__packed__)) Sdshdr{
private:
    unsigned char flag;     //低3位存类型，sdshdr5的高5位存长度
    char* buf;
public:
    Sdshdr(){}
    ~Sdshdr(){}

    int sdsHdrSize();
    char* sdsReqBuf();
    char sdsReqType();
    void sdsSetType(size_t initlen);

    virtual TYPE sdsReqLen();
    virtual TYPE sdsReqAlloc();
    virtual void sdsSetLen(size_t len);
    virtual void sdsSetAlloc(size_t alloc);

    virtual void sdsCreate();
    virtual void sdsMakeRoom();
    virtual void sdsFree();
    virtual void sdsClear();
};

class __attribute__((__packed__)) Sdshdr5 : public Sdshdr<uint8_t>{
public:
    uint8_t sdsReqLen();
    void sdsSetLen(uint8_t len);

    void sdsCreate();
    void sdsMakeRoom();
    void sdsFree();
    void sdsClear();
};

class __attribute__((__packed__)) sdshdr8 : public Sdshdr<uint8_t>{
private:
    uint8_t len;        //以使用长度
    uint8_t alloc;      //总长度
public:
    uint8_t sdsReqLen();
    uint8_t sdsReqAlloc();
    void sdsSetLen(size_t len);
    void sdsSetAlloc(size_t alloc);

    void sdsCreate();
    void sdsMakeRoom();
    void sdsFree();
    void sdsClear();
};

class __attribute__((__packed__)) sdshdr16 : public Sdshdr<uint16_t>{
private:
    uint16_t len;        //以使用长度
    uint16_t alloc;      //总长度
public:
    uint16_t sdsReqLen();
    uint16_t sdsReqAlloc();
    void sdsSetLen(size_t len);
    void sdsSetAlloc(size_t alloc);

    void sdsCreate();
    void sdsMakeRoom();
    void sdsFree();
    void sdsClear();
};

class __attribute__((__packed__)) sdshdr32 : public Sdshdr<uint32_t>{
private:
    uint32_t len;        //以使用长度
    uint32_t alloc;      //总长度
public:
    uint32_t sdsReqLen();
    uint32_t sdsReqAlloc();
    void sdsSetLen(size_t len);
    void sdsSetAlloc(size_t alloc);

    void sdsCreate();
    void sdsMakeRoom();
    void sdsFree();
    void sdsClear();
};

class __attribute__((__packed__)) sdshdr64 : public Sdshdr<uint64_t>{
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
