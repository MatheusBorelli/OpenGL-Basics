#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <limits.h>
#include "HashTable.h"

bool InitTempData(Data** pData){
    *pData = (Data*) malloc(sizeof(Data));
    return (*pData != NULL);
} 

List* InitLists(){
    List *list =(List*) malloc(sizeof(List));
    
    list->start = NULL;
    list->end = NULL;
    list->size = 0;
    return list;
}

HashTable InitHashTable(){
    HashTable hashTable;
    for(unsigned int i = 0; i < MAXDATA ; i++)
    {
        hashTable.storage[i] = InitLists();
    }

    hashTable.count_lists = 0;
    hashTable.count_data  = 0;

    return hashTable;
}

unsigned int HashCode(char* name){
    unsigned int index = 0;
    for(unsigned i = 0 ; i < strlen(name); i++)
    {
        index = index + name[i] + name[i];
        index = index % UINT_MAX;
        index = index % MAXDATA;
    }
    return index;
}

bool AddHashTable(Data data,HashTable *hashTable){
    if(hashTable == NULL) return false;

    Data* temp;
    if(!InitTempData(&temp)) return false;

    temp->text = data.text;
    temp->number = data.number;

    unsigned int index = HashCode(data.text);
    
    temp->next = hashTable->storage[index]->start;
    
    hashTable->storage[index]->start = temp;
    if(hashTable->storage[index]->end == NULL)
    {    
        hashTable->storage[index]->end = temp;

        hashTable->count_lists++;
    }
    hashTable->storage[index]->size++;
    hashTable->count_data++;
    
    return true;
}

bool SearchHashTable(char *text, HashTable HashTable){
    Data* temp;
    if(!InitTempData(&temp)) return false;

    unsigned int index = HashCode(text);
    if(HashTable.storage[index]->start == NULL ) return false;
    
    temp = HashTable.storage[index]->start;
    for(unsigned int i = 0; (i < HashTable.storage[index]->size) || (temp == NULL); i++){
        if(strcmp(text,temp->text) == 0)
            return true;
        temp = temp->next;
    }
    
    return false;
}

int ReturnNumberData(char *text, HashTable HashTable){
    Data* temp;
    if(!InitTempData(&temp)) return false;

    unsigned int index = HashCode(text);
    if(HashTable.storage[index]->start == NULL ) return false;
    
    temp = HashTable.storage[index]->start;
    for(unsigned int i = 0; (i < HashTable.storage[index]->size) || (temp == NULL); i++){
        if(strcmp(text,temp->text) == 0)
            return temp->number;
        temp = temp->next;
    }
    
    return false;
}

void PrintTable(HashTable hashTable){
    Data *temp;
    InitTempData(&temp);
    printf("Start\n");
    for(unsigned int i = 0; i < MAXDATA ; i++){
        printf("%d - ",i);
        temp = hashTable.storage[i]->start;
        while(temp != NULL){
            printf("%s - ",temp->text);
            temp = temp->next;
        }
        printf("NULL\n");
    }
    free(temp);
}