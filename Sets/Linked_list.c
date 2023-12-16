#include "set.h"

LIST_ITEM* Get_tail_list(LIST_ITEM* head)
{
    if (!head)
    {
        return NULL;
    }

    LIST_ITEM* current_item = head;
    LIST_ITEM* last_item = head;

    while (current_item)
    {
        // scorro la lista finche non arrivo all'ultimo elemento che w' diventato null
        last_item = current_item;
        current_item = current_item->next;
    }
    return last_item;
}

LIST_ITEM* List_append(LIST_ITEM** head, LIST_ITEM* item)
{
    LIST_ITEM* tail = Get_tail_list(*head);
    
    if (!tail)
    {
        // la lista e' vuota quindi lo aggiungo come primo elemento
        *head = item;
        (*head)->count = 1;
        (*head)->index_in_list = 0;
        (*head)->next = NULL;
        
        //printf("Inserito %s come testa \n", ((Int_item*)(*head))->key);
    }
    else
    {
        // lo aggiungo alla coda
        tail->next = item;
        (*head)->count++;
        item->index_in_list = (*head)->count - 1;
    }

    item->next = NULL;

    return item;
}

LIST_ITEM* List_pop(LIST_ITEM** head)
{
    if(!*head)
    {
        // lista vuota
        return NULL;
    }

    // mi salvo la testa in una variabile
    LIST_ITEM* current_head = *head;
    const unsigned int current_count = current_head->count;

    // il secondo elemento diventa il primo
    *head = (*head)->next;
    if(*head)
    {
        // assegno il count
        (*head)->count = current_count - 1;
    }

    current_head->next = NULL;
    return current_head;
};

LIST_ITEM* Remove_list_item(LIST_ITEM** head, unsigned int index)
{
    if (!*head || index >= (*head)->count)
    {
        printf("Indice non valido\n");
        return NULL;
    }
    if (index == 0)
    {
        // Ho rimosso la testa
        return List_pop(head);
    }
    
    
    LIST_ITEM* current_item = *head;
    LIST_ITEM* parent_of_wanted_item = *head;
    int i = 0;

    while(current_item != NULL && i < index)
    {
        // salvo il prossimo elemento come elemento corrente
        current_item = current_item->next;
        i++;
        if (i == index - 1)
        {
            // se entro qui vuol dire che sono nell'elemento prima di quello voluto (parent)
            parent_of_wanted_item = current_item;
        }
    }
    // setto il next del parent con quello del item cercato
    parent_of_wanted_item->next = current_item->next;
    current_item->next = NULL;
    (*head)->count--;

    return current_item;
    
}

unsigned int Get_lenght_list(LIST_ITEM* head)
{
    // Funzione che ritorna la lungezza della lista
    return head->count;
};

void Reverse_list(LIST_ITEM** head)
{
    if(!*head)
    {
        printf("Lista vuota");
        return;
    }

    // mi creo delle variabili per salvarmi i vari prev e next
    LIST_ITEM* current_item = *head;
    LIST_ITEM* prev_item = NULL;
    LIST_ITEM* next_item = NULL;
 
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