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
private:
    unsigned char flag;     //低3位存类型，sdshdr5的高5位存长度
    char* buf;
public:
    Sdshdr(){}
    ~Sdshdr(){}

    char sdsReqType();
    int sdsHdrSize();
    char* sdsReqBuf();
    virtual void sdsReqLen();
    virtual void sdsReqAlloc();

    void sdsSetType(size_t initlen);
    virtual void sdsSetLen();
    virtual void sdsSetAlloc();

    virtual void sdsCreate();
    virtual void sdsMakeRoom();
    virtual void sdsFree();
    virtual void sdsClear();
};

class __attribute__((__packed__)) Sdshdr5 : public Sdshdr{
};

class __attribute__((__packed__)) sdshdr8 : public Sdshdr{
private:
    uint8_t len;        //以使用长度
    uint8_t alloc;      //总长度
};

class __attribute__((__packed__)) sdshdr16 : public Sdshdr{
private:
    uint16_t len;        //以使用长度
    uint16_t alloc;      //总长度
};

class __attribute__((__packed__)) sdshdr32 : public Sdshdr{
private:
    uint32_t len;        //以使用长度
    uint32_t alloc;      //总长度
};

class __attribute__((__packed__)) sdshdr64 : public Sdshdr{
private:
    uint64_t len;        //以使用长度
    uint64_t alloc;      //总长度
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
