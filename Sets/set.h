#define AIV_INT_ITEM(x) &(x.list_item)

typedef struct aiv_list_item Aiv_list_item;
typedef struct aiv_int_item Aiv_int_item;

Aiv_list_item* aiv_list_get_tail(Aiv_list_item* head);

Aiv_list_item* aiv_list_append(Aiv_list_item** head, Aiv_list_item* item);

Aiv_list_item* aiv_list_pop(Aiv_list_item** head);

Aiv_list_item* aiv_list_get_item(Aiv_list_item** head, unsigned int index);

void Reverse_aiv_list(Aiv_list_item** head);