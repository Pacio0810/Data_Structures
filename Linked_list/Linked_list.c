#include <stddef.h>
#include<stdio.h>

#define INT_ITEM(x) &(x.list_item)

typedef struct List_item List_item;
typedef struct Int_item Int_item;

struct  List_item
{
    List_item* next;
    unsigned int count;
};

struct  Int_item
{
    List_item list_item;
    int value;
};

List_item* Get_tail_list(List_item* head)
{
    if (!head)
    {
        return NULL;
    }

    List_item* current_item = head;
    List_item* last_item = head;

    while (current_item)
    {
        // scorro la lista finche non arrivo all'ultimo elemento che w' diventato null
        last_item = current_item;
        current_item = current_item->next;
    }
    return last_item;
}

List_item* List_append(List_item** head, List_item* item)
{
    List_item* tail = Get_tail_list(*head);
    
    if (!tail)
    {
        // la lista e' vuota quindi lo aggiungo come primo elemento
        *head = item;
        (*head)->count = 1;

    }
    else
    {
        // lo aggiungo alla coda
        tail->next = item;
        (*head)->count++;
    }

    item->next = NULL;
    return item;
}

List_item* List_pop(List_item** head)
{
    if(!*head)
    {
        // lista vuota
        return NULL;
    }

    // mi salvo la testa in una variabile
    List_item* current_head = *head;
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

List_item* Remove_list_item(List_item** head, unsigned int index)
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
    
    
    List_item* current_item = *head;
    List_item* parent_of_wanted_item = *head;
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

unsigned int Get_lenght_list(List_item* head)
{
    // Funzione che ritorna la lungezza della lista
    return head->count;
};

void Reverse_list(List_item** head)
{
    if(!*head)
    {
        printf("Lista vuota");
        return;
    }

    // mi creo delle variabili per salvarmi i vari prev e next
    List_item* current_item = *head;
    List_item* prev_item = NULL;
    List_item* next_item = NULL;
 
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
    List_item* head = NULL;

    Int_item int_item;
    int_item.value = 100;
    List_append(&head, INT_ITEM(int_item));

    Int_item int_item2;
    int_item2.value = 101;
    List_append(&head, INT_ITEM(int_item2));

    Int_item int_item3;
    int_item3.value = 102;
    List_append(&head, INT_ITEM(int_item3));

    Int_item int_item4;
    int_item4.value = 104;
    List_append(&head, INT_ITEM(int_item4));

    unsigned int index = 2;
    Int_item* returned_item = (Int_item*)Remove_list_item(&head, index);

    //Reverse_list(&head);
    
    //unsigned int index2 = 0;
    //Int_item* returned_item2 = (Int_item*)Remove_list_item(&head, index2);

    //printf("Il valore dell'elemento all' indice %d e' %u\n", index, returned_item->value);

    //Int_item* returned_item3 = (Int_item*)Remove_list_item(&head, index2);

    //printf("Il valore dell'elemento all' indice %d e' %u\n", index, returned_item2->value);

    //printf("count: %u", Get_lenght_list(head));
    
    return 0;
}