#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_COLLISION 3 // numero massimo di collisioni prima di eseguire un realloc
#define SET_VALUE(set, index, i, value) set->hashmap[index][i].value = (void *)&value;
#define Max_elements 100

typedef struct Dictionary_item
{
    const char *key;
    int value;
    size_t key_len;
    
} DICTIONARY_ITEM;

typedef struct Dictionary
{
    DICTIONARY_ITEM** hashmap;
    int Collision_count;
    int HASHMAP_SIZE;
} DICTIONARY;

int HASHMAP_SIZE_LIST = 3;

void Dictionary_Realloc(DICTIONARY *Dictionary);

void dictionary_insert_int(DICTIONARY *Dictionary, const char *key, const int value);

void initialize_dictionary(DICTIONARY* Dictionary, const size_t Initial_hashmap_size) 
{
    Dictionary->Collision_count = 0;
    Dictionary->HASHMAP_SIZE = Initial_hashmap_size;
    
    // alloco memoria per il dizionario
    Dictionary->hashmap = (DICTIONARY_ITEM **)malloc(sizeof(DICTIONARY_ITEM*) * Dictionary->HASHMAP_SIZE);

    for (size_t i = 0; i < Dictionary->HASHMAP_SIZE; i++) 
    {
        // mi alloco altra memoria
        Dictionary->hashmap[i] = (DICTIONARY_ITEM *)malloc(sizeof(DICTIONARY_ITEM) * HASHMAP_SIZE_LIST);

        for (size_t j = 0; j < HASHMAP_SIZE_LIST; j++) {
            Dictionary->hashmap[i][j].key = NULL;
            Dictionary->hashmap[i][j].key_len = 0;
            // Inizializzare altri campi se necessario
        }
    }
}

// Deallocazione del dizionario
void free_dictionary(DICTIONARY *Dictionary) 
{
    for (size_t i = 0; i < Dictionary->HASHMAP_SIZE; i++) 
    {
        //libero prima la memoria degli indici
        free(Dictionary->hashmap[i]);
    }
    // poi libero la memoria del dizionario
    free(Dictionary->hashmap);
    Dictionary->hashmap = NULL;
}

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

DICTIONARY_ITEM* dictionary_find(DICTIONARY* Dictionary, const char *key)
{
    // setto tutte le varie variabili che mi servono
    
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % Dictionary->HASHMAP_SIZE;
    
    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        // se nell'indice e' presente una chiave
        if (Dictionary->hashmap[index][i].key_len > 0)
        {
            // prima confrtonto la loro lunghezza e poi in caso vado carattere per carattere
            if (Dictionary->hashmap[index][i].key_len == key_len && !memcmp(Dictionary->hashmap[index][i].key, key, key_len))
            {
                return &Dictionary->hashmap[index][i];
            }
        }
    }

    
    return NULL;
}

DICTIONARY_ITEM* Removal_dictionary_item(DICTIONARY *Dictionary, const char *key)
{
    // controllo la presenza della chiave nel dictionary
    DICTIONARY_ITEM* item = dictionary_find(Dictionary,key);
    if (!item)
    {
        // la chiave non e' presente quindi non la posso rimuovere
        return NULL;
    }

    item->key = NULL;
    item->key_len = 0;
    item->value = 0;
    return item;
}

void Dictionary_Realloc(DICTIONARY *Dictionary)
{
    DICTIONARY_ITEM Elements[Max_elements];             // inizializzo un array per contenere gli elementi all'interno del dizionario

    int index = 0;
    for (int i = 0; i < Dictionary->HASHMAP_SIZE; i++)
    {
        for (int j = 0; j < HASHMAP_SIZE_LIST; j++)
        {
            if (Dictionary->hashmap[i][j].key != NULL)
            {
                Elements[index].key = Dictionary->hashmap[i][j].key;                // mi scorro il dizionario e poi mi salvo i vari valori
                Elements[index].key_len = Dictionary->hashmap[i][j].key_len;
                Elements[index].value = Dictionary->hashmap[i][j].value;
                index ++;
            }
        }
    }

    // Modifico la dimensione del dizionario
    Dictionary->HASHMAP_SIZE *= 2;

    // riinizializzo il dizionario con la nuova dimensione
    initialize_dictionary(Dictionary, Dictionary->HASHMAP_SIZE);
    
    printf("REALLOC MEMORY WITH SIZE: %d \n", Dictionary->HASHMAP_SIZE);

    for (int i = 0; i < index; i++)
    {
        // reinserisco gli elementi che mi ero salvato nell'array
        dictionary_insert_int(Dictionary, Elements[i].key, Elements[i].value);
    }

    return;
}

void dictionary_insert_int(DICTIONARY *Dictionary, const char *key, const int value)
{
    // controllo la presenza della chiave nel dictionary

    DICTIONARY_ITEM* item = dictionary_find(Dictionary,key);

    if (item != NULL)
    {
        // la chiave e' presente quindi non la inserisco
        printf("ERROR, %s is already present\n", key);
        return;
    }

    if (Dictionary->Collision_count + 1 > MAX_COLLISION)
    {
        Dictionary_Realloc(Dictionary);
    }

    const size_t key_len = strlen(key);
    
    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % Dictionary->HASHMAP_SIZE;


    if (Dictionary->hashmap[index]->key_len !=0)
    {
        Dictionary->Collision_count ++;
    }

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (Dictionary->hashmap[index][i].key_len == 0)
        {
            // setto l'item nel dizionario
            Dictionary->hashmap[index][i].key = key;
            Dictionary->hashmap[index][i].key_len = key_len;
            Dictionary->hashmap[index][i].value = value;
           
            printf("Chiave : %s , valore : %d, indice %zu, posto %zu \n", Dictionary->hashmap[index][i].key, Dictionary->hashmap[index][i].value, index, i);
            return;
        }
    }
    
    // si potrebbe fare un realloc anche qui in caso non sia stato possibile aggiungere l'elemento
    printf("Indice gia occupato, %s non inserito\n", key);
    return;    
}

int main(int argc, char **argv)
{
    DICTIONARY MyDictionary;

    initialize_dictionary(&MyDictionary, 4);  // Inizializza il dizionario

    dictionary_insert_int(&MyDictionary, "Hello", 2);
    dictionary_insert_int(&MyDictionary, "Hello2", 56);
    dictionary_insert_int(&MyDictionary, "Test", 57);
    dictionary_insert_int(&MyDictionary, "Foobar", 98);
    dictionary_insert_int(&MyDictionary, "XYZ", 87);
    dictionary_insert_int(&MyDictionary, "AAAAAA", 65);
    dictionary_insert_int(&MyDictionary, "BBBB", 65);
    dictionary_insert_int(&MyDictionary, "CCCCDDAAA", 65);
    dictionary_insert_int(&MyDictionary, "DDDDDFFFFF", 65);
    dictionary_insert_int(&MyDictionary, "GGGGG", 65);


    free_dictionary(&MyDictionary);  // Dealloca il dizionario

    return 0;
}