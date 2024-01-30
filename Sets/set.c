#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define HASHMAP_SIZE 64
#define HASHMAP_SIZE_LIST 1

typedef struct Set_item
{
    const char *key;
    size_t key_len;
    
} SET_ITEM;

typedef struct Set
{
    SET_ITEM hashmap[HASHMAP_SIZE][HASHMAP_SIZE_LIST];
} SET;

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

SET_ITEM* Find_in_set(SET *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        // controllo se nell'indice e' presente un'altra chiave
        if (set->hashmap[index][i].key_len > 0)
        {
            // comparo prima la lunghezza e poi in caso carattere per carattere
            if (set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                // sono uguali quindi ritorno l'item cercato
                return &set->hashmap[index][i];
            }
        }
    }

    return NULL;
}

void Insert_in_set(SET *set, const char *key)
{
    // controllo se e' unico/presente nel set
    SET_ITEM* item = Find_in_set(set,key);

    if (item)
    {
        // se non e' unico esco dalla funzione e non lo inserisco
        return;
    }

    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len == 0)
        {
            // aggiungo i suoi valori nel set
            set->hashmap[index][i].key = key;
            set->hashmap[index][i].key_len = key_len;
            return;
        }
    }
    printf("Unable to insert the element, the index was already busy\n");
}

void Removal_item_in_set(SET *set, const char *key)
{
    // controllo se l'elemento e' presente
    SET_ITEM* item = Find_in_set(set,key);

    if (!item)
    {
        // l'elemento non e' presente quindi esco
        return;
    }

    //annullo l'elemento
    item->key = NULL;
    item->key_len = 0;

    return;
}

int main(int argc, char **argv)
{
    SET myset;
    memset(&myset, 0, sizeof(SET));

    Insert_in_set(&myset, "Hello");
    Insert_in_set(&myset, "Hello2");
    Insert_in_set(&myset, "Test");
    Insert_in_set(&myset, "Foobar");
    Insert_in_set(&myset, "XYZ");
    Insert_in_set(&myset, "AAAAAA");
    Insert_in_set(&myset, "AAAAAa");
    
    Removal_item_in_set(&myset, "Hello");

    return 0;
}
