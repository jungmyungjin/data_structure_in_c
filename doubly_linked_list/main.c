#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
    int data;
    struct s_node *prev;
    struct s_node *next;
}   t_node;

typedef struct s_linked_list
{
    unsigned int size;
    t_node *head;
    t_node *tail;
}   t_linked_list;

t_linked_list *list_init(void)
{
    t_linked_list *new_list;

    new_list = (t_linked_list*) malloc(sizeof(t_linked_list));
    new_list->size = 0;
    new_list->tail = NULL;
    new_list->head = NULL;
    return (new_list);
}

t_node *list_create(int data)
{
    t_node *new_node;

    new_node = (t_node *) malloc(sizeof(t_node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return (new_node);
}

void show_list(t_node *list)
{
    int index;

    index = 0;
    while (list != NULL)
    {
        printf("{[prev : %p ]\n[currnet : %p] [%d] %d\n[next : %p ]}",list->prev, list, index,list->data,list->next);
        if (list->next != NULL)
            printf("\n-> \n");
        list = list->next;
        index++;
    }
    printf("\n\n");
}

int list_add(t_linked_list *list, int data, int n)
{
    t_node *new_node;
    t_node *current_node;
    int index;

    index = 0;
    new_node = list_create(data);
    current_node = list -> head;
    // target is first
    if (n == 0)
    {
        if (list->head != NULL)
        {
            new_node -> next = list -> head;
            list -> head -> prev = new_node;
        }
        else
        {
            list -> tail = new_node;
        }
        list -> head = new_node;
    }
    // target is last
    else if ((list -> size) - 1 < n)
    {
        new_node -> prev = list -> tail;
        list -> tail -> next = new_node;
        list -> tail = new_node;
        index = (list -> size) - 1;
    }
    // target is between
    else
    {
        while(index < n)
        {
            current_node = current_node -> next;
            index++;
        }
        new_node -> next = current_node;
        new_node -> prev = current_node -> prev;
        current_node -> prev -> next = new_node;
        current_node->prev = new_node;
    }
    list->size++;
    return (index);
}

int list_size(t_linked_list *list)
{
    int size;

    size = list->size;
    return (size);
}

int list_remove(t_linked_list *list, int n)
{
    t_node *remove_target;
    t_node *current_node;
    int index;

    index = 0;
    remove_target = NULL;
    current_node = list->head;
    if (n == 0)
    {
        remove_target = list->head;
        list->head->next->prev = NULL;
        list->head = list->head->next;
    }
    else if((list -> size) - 1 == n)
    {
        remove_target = list -> tail;
        list -> tail = list -> tail -> prev;
        list -> tail -> next = NULL;
    }
    else
    {
        while(current_node != NULL && index != n)
        {
            current_node = current_node->next;
            index++;
        }
        if (index != n)
            return(0);
        remove_target = current_node;
        current_node -> prev -> next = current_node -> next;
        current_node -> next -> prev = current_node -> prev;

    }
    free(remove_target);
    return (1);
}

void list_free(t_linked_list *list)
{
    t_node *target;
    t_node *prev;

    target = list->tail;
    while (target != NULL)
    {
        prev = target->prev;
        target->prev = NULL;
        target->next = NULL;
        target->data = 0;
        free(target);
        target = prev;
    }
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    free(list);
}

int main(void)
{
    t_linked_list *my_list = list_init();

    printf("size = %d\n", list_size(my_list));

    list_add(my_list, 5, 0);
    show_list(my_list->head);

    list_add(my_list, 7, 1);
    show_list(my_list->head);

    list_add(my_list, 6, 1);
    show_list(my_list->head);

    list_add(my_list, 1, 1);
    show_list(my_list->head);

    list_remove(my_list, 2);
    show_list(my_list->head);
    
    printf("remove index %d , result : %d\n", 9, list_remove(my_list, 9));

    printf("list free\n");
    list_free(my_list);
    show_list(my_list->head);


    return (0);
}
