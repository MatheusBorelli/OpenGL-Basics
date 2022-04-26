#pragma once

#include <stdbool.h>

#define MAXDATA 128

typedef struct data_Hash
{
    char* text;
    int number;
    struct data_Hash *next;
}Data;

typedef struct List_std
{
    Data *start;
    Data *end;
    unsigned int size;
}List;

typedef struct HashTable_std{
    List *storage[MAXDATA];
    unsigned short int count_lists;
    unsigned short int count_data;
}HashTable;

HashTable InitHashTable();
unsigned int HashCode(char* name);
bool AddHashTable(Data data,HashTable *hashTable);
bool SearchHashTable(char *text, HashTable HashTable);
int ReturnNumberData(char *text, HashTable HashTable);
void PrintTable(HashTable hashTable);