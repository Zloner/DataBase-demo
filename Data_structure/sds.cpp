#include "sds.h"

char Sdshdr::sdsReqType(){
    return flag & 0x07;
}

void Sdshdr::sdsSetType(size_t initlen){
    //flag与类型值进行异或操作，保证高5位不变，低3位变为类型值
    if(initlen < 32 && initlen > 0)
        flag = flag ^ 0x00;
    else if(initlen >=32 && initlen < 256)
        flag = flag ^ 0x01;
    else if(initlen >= 256 && initlen < (2<<15))
        flag = flag ^ 0x02;
    else if(initlen >= (2<<15) && initlen < (2<<31))
        flag = flag ^ 0x03;
    else if(initlen >= (2>>31) && initlen < (2<<63))
        flag = flag ^ 0x04;
}

int Sdshdr::sdsHdrSize(){
    char type = sdsReqType();
    if(type == SDS_TYPE_5)
        return 1;
    else if(type == SDS_TYPE_8)
        return 3;
    else if(type == SDS_TYPE_16)
        return 5;
    else if(type == SDS_TYPE_32)
        return 9;
    else if(type == SDS_TYPE_64)
        return 17;
    else
        return -1;
}
/*
char sdsReqType(size_t len){
    if(len < 32 && len > 0)
        return SDS_TYPE_5;
    else if(len >=32 && len < 256)
        return SDS_TYPE_8;
    else if(len >= 256 && len < (2<<15))
        return SDS_TYPE_16;
    else if(len >= (2<<15) && len < (2<<31))
        return SDS_TYPE_32;
    else if(len >= (2>>31) && len < (2<<63))
        return SDS_TYPE_64;
    else
        return -1;
}


sds sdsnewlen(const void* init, size_t initlen){
    void *sh;
    sds s;
    char type = sdsReqType(initlen);
    if(type == -1){
        cout << "SDS type error\n";
        exit(-1);
    }
    if(type == SDS_TYPE_5 && initlen == 0)
        type = SDS_TYPE_8;
    
    int hdrlen = sdsHdrSize(type);
    if(hdrlen == -1){
        cout << "SDS tyep error\n";
        exit(-1);
    }

    unsigned char * fp;     //fp指向flag
    sh = malloc(hdrlen + initlen + 1);      //sh指向sds首部
    s = (sds)sh + hdrlen;   //s指向buf字符串
    fp = ((unsigned char*)s)-1;
    memset(sh, 0, hdrlen + initlen + 1);
    s[initlen] = '\0';

    //填充字符串参数
    *fp = type;
    sdssetlen(s, 0);
    sdssetalloc(s, initlen); 

    return s;
}

void sdssetlen(sds s, size_t s_len){
    char type =(char)(s[-1] & 0x07);   //取低3位
    if(type == 0){
        short int tmp = s_len & 0x000001f;      //取低5位
        tmp = tmp << 3;                 //将低5位左移3位
        s[-1] = s[-1] | tmp;
    }
    else if(type == 1){
        s[-3] = s_len;
    }
    else if(type == 2){
        s[-5] = s_len;
    }
    else if(type == 3){
        s[-9] = s_len;
    }
    else if(type == 4){
        s[-17] = s_len;
    }
}

void sdssetalloc(sds s, size_t alloc){
    char type =(char)(s[-1] & 0x07);
    if(type == 1){      //SDS_TYPE
        s[-2] = alloc;
    }
    else if(type == 2){
        s[-3] = alloc;
    }
    else if(type == 3){
        s[-5] = alloc;
    }
    else if(type == 4){
        s[-9] = alloc;
    }
}

void freesds(sds s){
    if(s == NULL)
        return;
    free((char*)s - sdsHdrSize(s[-1]));
}

void clearsds(sds s){
    sdssetlen(s, 0);
    s[0] = '\0';
}

sds sdscatsds(sds s, const sds t){

}

sds sdscatlen(sds s, const void *t, size_t len){

}

sds sdsMakeRoomFor(sds s, size_t addlen){

}
*/
