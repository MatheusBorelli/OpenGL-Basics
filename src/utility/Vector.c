#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vec
{
    unsigned char* _mem;
    unsigned long _elems;
    unsigned long _elemsize;
    unsigned long _capelems;
    unsigned long _reserve;
}Vector;

Vector* InitVector(unsigned long elemsize)
{
    Vector* pvec = (Vector*)malloc(sizeof(Vector));
    pvec->_reserve = 10;
    pvec->_capelems = pvec->_reserve;
    pvec->_elemsize = elemsize;
    pvec->_elems = 0;
    pvec->_mem = (unsigned char*)malloc(pvec->_capelems * pvec->_elemsize);
    return pvec;
}

void FreeVector(Vector* pvec)
{
    free(pvec->_mem);
    free(pvec);
}

void IncreaseVector(Vector* pvec)
{
    unsigned char* mem = (unsigned char*)malloc((pvec->_capelems + pvec->_reserve) * pvec->_elemsize);
    memcpy(mem, pvec->_mem, pvec->_elems * pvec->_elemsize);
    free(pvec->_mem);
    pvec->_mem = mem;
    pvec->_capelems += pvec->_reserve;
}

void VectorPushBack(Vector* pvec, void* data, unsigned long elemsize)
{
    assert(elemsize == pvec->_elemsize);
    if (pvec->_elems == pvec->_capelems) {
        IncreaseVector(pvec);
    }
    memcpy(pvec->_mem + (pvec->_elems * pvec->_elemsize), (unsigned char*)data, pvec->_elemsize);
    pvec->_elems++;    
}

unsigned long VectorLength(Vector* pvec)
{
    return pvec->_elems;
}

void* GetVector(Vector* pvec, unsigned long index)
{
    assert(index < pvec->_elems);
    return (void*)(pvec->_mem + (index * pvec->_elemsize));
}

void CopyValueVector(Vector* pvec, void* dest, unsigned long index)
{
    memcpy(dest, GetVector(pvec, index), pvec->_elemsize);
}
/*
typedef struct sadad
{
    int x,y;
}ASS;
*/
/*
static void Demo()
{
    Vector* pvec = InitVector(sizeof(ASS));
    ASS test;
    test.x = 1;
    test.y = 2323;
    VectorPushBack(pvec, &test, sizeof(test));
    
    ASS test2;
    CopyValueVector(pvec, &test2, 0);
    printf("vec(%d) = %d\n", 0, test2.x);
    printf("vec(%d) = %d\n", 0, test2.y);

    
    //for (unsigned long index = (int)VectorLength(pvec) - 1; (int)index >= 0; index--) {
    //    int val;
    //    CopyValueVector(pvec, &val, index);
    //    printf("vec(%d) = %d\n", index, val);
    //}

    FreeVector(pvec);
}*/