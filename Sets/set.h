#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define HASHMAP_SIZE 2

typedef struct list_item LIST_ITEM;
typedef struct Int_item Int_item;

struct list_item
{
    LIST_ITEM* next;
    unsigned int count;
    int index_in_list;
};

struct  Int_item
{
    LIST_ITEM list_item;
    const char *key;
    size_t key_len;
    int index_in_set;
};

typedef struct Set
{
    LIST_ITEM* hashmap[HASHMAP_SIZE];
} SET;

LIST_ITEM* List_append(LIST_ITEM** head, LIST_ITEM* item);

LIST_ITEM* Remove_list_item(LIST_ITEM** head, unsigned int index);