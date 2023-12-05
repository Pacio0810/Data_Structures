#include <stddef.h>
#include<stdio.h>

#define ITEM(x) &(x.node)

typedef struct list_node LIST_NODE;
typedef struct node_item NODE_ITEM;

struct list_node
{
    LIST_NODE *prev;
    LIST_NODE *next;
    unsigned int count;
};

struct node_item
{
    LIST_NODE node;
    int value;
};

void insert_after_item(LIST_NODE* node_before, LIST_NODE* new_node)
{
    if (!node_before)
    {
        return;
    }

    if (!node_before->next)
    {
        node_before->next = new_node;
        new_node->prev = node_before;
        new_node->next = NULL;
        return;
    }
    
    new_node->next = node_before->next;              // setto il next del nuovo item come il next del item precedente
    node_before->next->prev = new_node;             // setto il nuovo prev del successivo
    node_before->next = new_node;                   // setto il next del precedente verso il nuovo item
    new_node->prev = node_before;                   // setto il prev del nuovo item verso l'item precedente
}

void insert_before_item(LIST_NODE* next_node, LIST_NODE* new_node)
{
    if (!next_node)
    {
        return;
    }

    if (!next_node->prev)
    {
        next_node->prev = new_node;
        new_node->next = next_node;
        new_node->prev = NULL;
    }

    next_node->prev->next = new_node;              // setto il next del precedente verso l'item nuovo
    new_node->prev = next_node->prev;                // setto il prev del nuovo item verso 
    next_node->prev = new_node;                     // setto il prev del item successivo verso il nuovo item
    new_node->next = next_node;                     // setto il next del nuovo item verso l'item successivo
}

LIST_NODE *list_get_tail(LIST_NODE **head)
{
    if (!*head)
    {
        return NULL;
    }

    LIST_NODE * current_item = *head;
    LIST_NODE * last_item = *head;

    while (current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }

    return last_item;
    
}

LIST_NODE *list_append (LIST_NODE **head, LIST_NODE *item)
{
    struct list_node *tail = list_get_tail(head);

    if (!tail)
    {
        * head = item;
    }
    else
    {
        tail->next = item;
    }

    (*head)->count++;
    item->prev = tail;
    item->next = NULL;
    return item;
}

LIST_NODE *remove_node(LIST_NODE **head, unsigned int index)
{
    if(!*head || index >= (*head)->count)
    {
        return NULL;
    }

    LIST_NODE * current_item = *head;
    int i = 0;
    
    while (current_item != NULL)
    {
        if (i == index)
        {
            current_item->prev->next = current_item->next;
            current_item->next->prev = current_item->prev;
            current_item->prev = NULL;
            current_item->next = NULL;

            (*head)->count--;
            return current_item;
        }
        
        current_item = current_item->next;
        i++;
    }

    return NULL;
}

int main()
{
    LIST_NODE *head = NULL;

    NODE_ITEM Item0;
    Item0.value = 1;
    list_append(&head, ITEM(Item0));

    NODE_ITEM Item1;
    Item1.value = 2;
    list_append(&head, ITEM(Item1));

    NODE_ITEM Item2;
    Item2.value = 3;
    list_append(&head, ITEM(Item2));

    NODE_ITEM Item3;
    Item3.value = 4;
    list_append(&head, ITEM(Item3));

    unsigned int index = 1;
    NODE_ITEM* removed_node = (NODE_ITEM*)remove_node(&head, index);

    NODE_ITEM Item4;
    Item4.value = 10;
    insert_after_item(&Item2.node, ITEM(Item4));

    printf("L'item con valore %u e' stato inserito correttamente con prev %u e next %u \n", Item4.value, ((NODE_ITEM*)Item4.node.prev)->value, ((NODE_ITEM*)Item4.node.next)->value);
    printf("Il next dell'item precedente e' diventato %u \n", ((NODE_ITEM*)Item2.node.next)->value);
    printf("Il prev dell'item successivo e' diventato %u \n", ((NODE_ITEM*)Item3.node.prev)->value);

    NODE_ITEM Item5;
    Item5.value = 15;
    insert_before_item(&Item4.node, ITEM(Item5));

    printf("L'item con valore %u e' stato inserito correttamente con next %u. \n", Item5.value, ((NODE_ITEM*)Item5.node.next)->value);
    printf("Il prev dell'item successivo e' diventato %u \n", ((NODE_ITEM*)Item4.node.prev)->value);
    printf("Il next dell'item precedente e' diventato %u", ((NODE_ITEM*)Item2.node.next)->value);
}