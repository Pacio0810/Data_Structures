#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define HASHMAP_SIZE 64
#define HASHMAP_SIZE_LIST 1

typedef struct aiv_set_item
{
    const char *key;
    size_t key_len;
    
} AIV_SET_ITEM;

typedef struct aiv_set
{
    AIV_SET_ITEM hashmap[HASHMAP_SIZE][HASHMAP_SIZE_LIST];
} AIV_SET;

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

int aiv_set_find(AIV_SET *set, const char *key)
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

int is_unique(AIV_SET *set, const char *key)
{
    if (aiv_set_find(set, key))
    {
        return 1;
    }

    return 0;
}

void aiv_set_insert(AIV_SET *set, const char *key)
{

    if (is_unique(set, key))
    {
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
            return;
        }
    }
}

void removal_set_item(AIV_SET *set, const char *key)
{
    if (aiv_set_find(set,key))
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
                printf("Item rimosso");
                return;
            }
            
        }
    }

    return;
}

int main(int argc, char **argv)
{
    AIV_SET myset;
    memset(&myset, 0, sizeof(AIV_SET));
    /*
    myset.hashmap[0].key = NULL;
    myset.hashmap[0].key_len = 0;
    myset.hashmap[1].key = NULL;
    myset.hashmap[1].key_len = 0;
    myset.hashmap[2].key = NULL;
    myset.hashmap[2].key_len = 0;*/

    aiv_set_insert(&myset, "Hello");
    aiv_set_insert(&myset, "Hello2");
    aiv_set_insert(&myset, "Test");
    aiv_set_insert(&myset, "Foobar");
    aiv_set_insert(&myset, "XYZ");
    aiv_set_insert(&myset, "AAAAAA");
    aiv_set_insert(&myset, "AAAAAa");
    
    aiv_set_insert(&myset, "Hello");

    //removal_set_item(&myset, "Hello");


    return 0;
}