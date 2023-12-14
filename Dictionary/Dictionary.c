#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define HASHMAP_SIZE 64
#define HASHMAP_SIZE_LIST 2

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

DICTIONARY_ITEM* dictionary_find(DICTIONARY *set, const char *key)
{
    // setto tutte le varie variabili che mi servono
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        // se nell'indice e' presente una chiave
        if (set->hashmap[index][i].key_len > 0)
        {
            // prima confrtonto la loro lunghezza e poi in caso vado carattere per carattere
            if (set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                return &set->hashmap[index][i];
            }
        }
    }

    return NULL;
}

void dictionary_insert_int(DICTIONARY *set, const char *key, const int value)
{
    // controllo la presenza della chiave nel dictionary
    DICTIONARY_ITEM* item = dictionary_find(set,key);
    if (item)
    {
        // la chiave e' presente quindi non la inserisco
        printf("ERROR, %s is already present\n", key);
        return;
    }
    
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len == 0)
        {
            // setto l'item nel dizionario
            set->hashmap[index][i].key = key;
            set->hashmap[index][i].key_len = key_len;

            SET_VALUE(set, index, i, value);

            //printf("Chiave : %s , valore : %d, indice %zu, posto %zu \n", set->hashmap[index][i].key, *(int*)set->hashmap[index][i].value, index, i);
            return;
        }
    }
    
    printf("Indice gia occupato, %s non inserito\n", key);    
}

void dictionary_insert_string(DICTIONARY *set, const char *key, char *string)
{
    // controllo la presenza della chiave nel dictionary
    DICTIONARY_ITEM* item = dictionary_find(set,key);
    if (item)
    {
        // la chiave e' presente quindi non la inserisco
        return;
    }
    
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len == 0)
        {
             // setto l'item nel dizionario
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
    // controllo la presenza della chiave nel dictionary
    DICTIONARY_ITEM* item = dictionary_find(set,key);
    if (!item)
    {
        // la chiave non e' presente quindi non la posso rimuovere
        return;
    }

    item->key = NULL;
    item->key_len = 0;
    item->value = 0;
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