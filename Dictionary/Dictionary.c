#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define HASHMAP_SIZE 64
#define HASHMAP_SIZE_LIST 1

#define SET_VALUE(set, index, i, value) set->hashmap[index][i].value = (void *)&value;


typedef struct Dictionary_item
{
    const char *key;
    void* value;
    size_t key_len;
    
} DICTIONARY_ITEM;

typedef struct Dictionary
{
    DICTIONARY_ITEM hashmap[HASHMAP_SIZE][HASHMAP_SIZE_LIST];
} DICTIONARY;

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

int dictionary_find(DICTIONARY *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len > 0)
        {
            if (set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                return 1;
            }
        }
    }

    return 0;
}

int is_unique(DICTIONARY *set, const char *key)
{
    if (dictionary_find(set, key))
    {
        return 1;
    }

    return 0;
}

void dictionary_insert_int(DICTIONARY *set, const char *key, const int value)
{

    if (is_unique(set, key))
    {
        //printf("la chiave : %s con valore : %d non e' unica\n", key, value);
        return;
    }
    
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len == 0)
        {
            set->hashmap[index][i].key = key;
            set->hashmap[index][i].key_len = key_len;

            SET_VALUE(set, index, i, value);

            //printf("Chiave : %s , valore : %d\n", set->hashmap[index][i].key, *(int*)set->hashmap[index][i].value);

        }
    }
}

void dictionary_insert_string(DICTIONARY *set, const char *key, char *string)
{

    if (is_unique(set, key))
    {
        //printf("la chiave : %s con valore : %s non e' unica\n", key, string);
        return;
    }
    
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len == 0)
        {
            set->hashmap[index][i].key = key;
            set->hashmap[index][i].key_len = key_len;
            set->hashmap[index][i].value = string;

            //printf("Chiave : %s , valore : %s\n", set->hashmap[index][i].key, (char*)set->hashmap[index][i].value);
        }

        return;
        
    }
}

void removal_set_item(DICTIONARY *set, const char *key)
{
    if (dictionary_find(set,key))
    {
        
        const size_t key_len = strlen(key);

        const size_t hash = djb33x_hash(key, key_len);

        const size_t index = hash % HASHMAP_SIZE;

        for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
        {
            if (set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                set->hashmap[index][i].key = NULL;
                set->hashmap[index][i].key_len = 0;
                set->hashmap[index][i].value = 0;
                //printf("Rimossa la chiave : %s \n", key);
                return;
            }
            
        }
    }

    return;
}

int main(int argc, char **argv)
{
    DICTIONARY myset;
    memset(&myset, 0, sizeof(DICTIONARY));

    dictionary_insert_int(&myset, "Hello",2);
    dictionary_insert_int(&myset, "Hello2", 56);
    dictionary_insert_int(&myset, "Test", 57);
    dictionary_insert_int(&myset, "Foobar", 98);
    dictionary_insert_int(&myset, "XYZ", 87);
    dictionary_insert_int(&myset, "AAAAAA", 65);
    dictionary_insert_int(&myset, "AAAAAa", 54);
    
    dictionary_insert_int(&myset, "Hello", 344);
    dictionary_insert_string(&myset, "Babbo", "Natale");
    dictionary_insert_string(&myset, "Babbo", "Natale");
    
    removal_set_item(&myset, "Hello");
    dictionary_insert_int(&myset, "Hello", 344);

    return 0;
}