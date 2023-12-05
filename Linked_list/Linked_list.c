#include <stddef.h>
#include<stdio.h>

#define AIV_INT_ITEM(x) &(x.list_item)

typedef struct aiv_list_item Aiv_list_item;
typedef struct aiv_int_item Aiv_int_item;

struct  aiv_list_item
{
    Aiv_list_item* next;
    unsigned int count;
};

struct  aiv_int_item
{
    Aiv_list_item list_item;
    int value;
};

Aiv_list_item* aiv_list_get_tail(Aiv_list_item* head)
{
    if (!head)
    {
        return NULL;
    }

    Aiv_list_item* current_item = head;
    Aiv_list_item* last_item = head;

    while (current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }

    return last_item;
}

Aiv_list_item* aiv_list_append(Aiv_list_item** head, Aiv_list_item* item)
{
    Aiv_list_item* tail = aiv_list_get_tail(*head);
    
    if (!tail)
    {
        *head = item;
        (*head)->count = 1;

    }
    else
    {
        tail->next = item;
        (*head)->count++;
    }

    item->next = NULL;
    return item;
}

Aiv_list_item* aiv_list_pop(Aiv_list_item** head)
{
    if(!*head)
    {
        return NULL;
    }

    Aiv_list_item* current_head = *head;
    const unsigned int current_count = current_head->count;
    *head = (*head)->next;
    if(*head)
    {
        (*head)->count = current_count - 1;
    }

    current_head->next = NULL;
    return current_head;
};

Aiv_list_item* aiv_list_get_item(Aiv_list_item** head, unsigned int index)
{
    if (!*head || index >= (*head)->count)
    {
        printf("Indice non valido\n");
        return NULL;
    }
    if (index == 0)
    {
        return aiv_list_pop(head);
    }
    
    
    Aiv_list_item* current_item = *head;
    Aiv_list_item* parent_of_wanted_item = *head;
    int i = 0;

    while(current_item != NULL && i < index)
    {
        current_item = current_item->next;
        i++;
        if (i == index - 1)
        {
            parent_of_wanted_item = current_item;
        }
    }
    
    parent_of_wanted_item->next = current_item->next;
    current_item->next = NULL;
    (*head)->count--;

    return current_item;
    
}

unsigned int aiv_list_lenght(Aiv_list_item* head)
{
    return head->count;
};

void Reverse_aiv_list(Aiv_list_item** head)
{
    if(!*head)
    {
        printf("Lista vuota");
        return;
    }

    Aiv_list_item* current_item = *head;
    Aiv_list_item* prev_item = NULL;
    Aiv_list_item* next_item = NULL;
 
    while (current_item != NULL) 
    {
        // mi salvo il next del current_item                          // primo ciclo                                                     // secondo ciclo                                        //  terzo ciclo
        next_item = current_item->next;                              //ipotetico next_item = item all'indice 1                          // next_time = item all'indice 2                        // netx time = item indice 3 = NULL
                                                                                                                                                                                                
        // il next diventa quello precedente
        current_item->next = prev_item;                             // current item(indice 0) punta a null                              // current_item(indice 1) punta al prev(indice 0)      // current item(2) punta al prev (indice 1)
        
        prev_item = current_item;                                   // il prev_item diventa l'indice 0                                  // il prev diventa indice 1                            // il prev diventa indice 2
        current_item = next_item;                                   // current_item = next_item(indice 1)                               // current diventa indice 2                            // current diventa indice 3 (NULL)
    }

    // cambio la testa con il prev finale ovvero l'ultimo elemento e gli assegno il count
    prev_item->count = (*head)->count;                              
    *head = prev_item;
}


int main()
{
    Aiv_list_item* head = NULL;

    Aiv_int_item int_item;
    int_item.value = 100;
    aiv_list_append(&head, AIV_INT_ITEM(int_item));

    Aiv_int_item int_item2;
    int_item2.value = 101;
    aiv_list_append(&head, AIV_INT_ITEM(int_item2));

    Aiv_int_item int_item3;
    int_item3.value = 102;
    aiv_list_append(&head, AIV_INT_ITEM(int_item3));

    // unsigned int index = 1;
    // Aiv_int_item* returned_item = (Aiv_int_item*)aiv_list_get_item(&head, index);

    // printf("Il valore dell'elemento all' indice %d e' %u\n", index, returned_item->value);

    // Aiv_int_item* returned_item2 = (Aiv_int_item*)aiv_list_get_item(&head, index);

    // printf("Il valore dell'elemento all' indice %d e' %u\n", index, returned_item2->value);
    // printf("count: %u", aiv_list_lenght(head));

    Reverse_aiv_list(&head);
    
    unsigned int index = 0;
    Aiv_int_item* returned_item = (Aiv_int_item*)aiv_list_get_item(&head, index);

    printf("Il valore dell'elemento all' indice %d e' %u\n", index, returned_item->value);

    Aiv_int_item* returned_item2 = (Aiv_int_item*)aiv_list_get_item(&head, index);

    printf("Il valore dell'elemento all' indice %d e' %u\n", index, returned_item2->value);

    printf("count: %u", aiv_list_lenght(head));
    
    return 0;
}