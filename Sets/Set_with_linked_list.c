#include "set.h"

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

Int_item* Find_in_set(SET *set, Int_item* item)
{
    const size_t key_len = strlen(item->key);

    const size_t hash = djb33x_hash(item->key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    if (!set->hashmap[index])
    {
        // testa vuota quindi la chiave e' univoca
        return NULL;
    }

    LIST_ITEM *current_node = set->hashmap[index];
    while(current_node)
    {
        if (((Int_item*)current_node)->key_len > 0)
        {
            if (((Int_item*)current_node)->key_len == key_len && !memcmp(((Int_item*)current_node)->key, item->key, key_len))
            {
                return ((Int_item*)current_node);
            }
            
        }
        current_node = current_node->next;
    }

    return NULL;
}

void Removal_item_in_set(SET *set, Int_item* item)
{
    // controllo se l'elemento e' presente
    Int_item* find_item = Find_in_set(set , item);

    if (!find_item)
    {
        // l'elemento non e' presente quindi esco
        return;
    }

    //annullo l'elemento
    printf("Rimuovo chiave: %s\n", item->key);

    Remove_list_item(&set->hashmap[find_item->index_in_set], ((LIST_ITEM*)find_item)->index_in_list);
    
    find_item->key = NULL;
    find_item->key_len = 0;

    return;
}

void Insert_in_set(SET *set, Int_item* item)
{
    //controllo se e' unico/presente nel set

    Int_item* find_item = Find_in_set(set , item);

    if (find_item)
    {
        // se non e' unico esco dalla funzione e non lo inserisco
        printf("Impossibile inserire la chiave %s perche e' gia presente nel SET\n", item->key);
        return;
    }

    const size_t key_len = strlen(item->key);
    item->key_len = key_len;

    const size_t hash = djb33x_hash(item->key, key_len);

    const size_t index = hash % HASHMAP_SIZE;
    item->index_in_set = index;


    List_append(&set->hashmap[index], &item->list_item);
}

int main(int argc, char **argv)
{
    SET myset;
    memset(&myset, 0, sizeof(SET));

    Int_item int_item;
    int_item.key = "Ferrari";
    Insert_in_set(&myset, &int_item);


    Int_item int_item2;
    int_item2.key = "Mercedes";
    Insert_in_set(&myset, &int_item2);

    Int_item int_item3;
    int_item3.key = "Redbull";
    Insert_in_set(&myset, &int_item3);

    Int_item int_item4;
    int_item4.key = "Mclaren";
    Insert_in_set(&myset, &int_item4);

    printf("Il next di %s e': %s\n", int_item2.key,((Int_item*)int_item2.list_item.next)->key);
    

    Removal_item_in_set(&myset, &int_item3);


    Int_item int_item5;
    int_item5.key = "Redbull";
    Insert_in_set(&myset, &int_item5);

    printf("Ora il next di %s e': %s\n", int_item2.key,((Int_item*)int_item2.list_item.next)->key);

    Insert_in_set(&myset, &int_item);
    return 0;
}