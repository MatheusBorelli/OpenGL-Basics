#pragma once

typedef struct vec Vector;


Vector* InitVector(unsigned long elemsize);
void FreeVector(Vector* pvec);
void IncreaseVector(Vector* pvec);
void VectorPushBack(Vector* pvec, void* data, unsigned long elemsize);
unsigned long VectorLength(Vector* pvec);
void* GetVector(Vector* pvec, unsigned long index);
void CopyValueVector(Vector* pvec, void* dest, unsigned long index);
