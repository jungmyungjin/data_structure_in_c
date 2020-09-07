#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
    int data;
    struct s_node *prev;
    struct s_node *next;
}   t_node;

typedef struct s_head
{
    t_node *head;
}   t_head;

void show_list(t_head *list)
{
    t_node *current_node;
    int index;

    current_node = list->head;
    index = 0;
    while(current_node != NULL)
    {
        printf("%p [%d] data = %d\nprev : %p\nnext : %p\n\n",current_node,index, current_node->data, current_node->prev, current_node->next);
        if (current_node->next == list->head)
        {
            break;
        }
            index++;
            current_node = current_node->next;
    }
    printf("\n");
}

t_node *create_node(int data)
{
    t_node *new_node;

    new_node = (t_node *) malloc(sizeof(t_node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return (new_node);
}

t_node *find_node (t_head *list, int target_index)
{
    t_node *current_node;
    int index;

    current_node = list->head;
    index = 0;
    while(current_node != NULL && index != target_index)
    {
        if(current_node->next == list->head)
            break;
        current_node = current_node->next;
        index++;
    }
    return (current_node);
}

void list_add(t_head **list, int target_index, int data)
{
    int index;
    t_node *new_node;
    t_node *current_node;

    index = 0;
    new_node = create_node(data);
    current_node = (*list)->head;
    while(current_node != NULL && index != target_index)
    {
        if(current_node->next == (*list)->head)
            break;
        current_node = current_node->next;
        index++;
    }
    if (target_index == 0)
    {    
        if ((*list)->head == NULL)
        {
            (*list)->head = new_node;
            new_node->prev = new_node;
            new_node->next = new_node;
        }
        else
        {
            new_node->next =(*list)->head;
            (*list)->head->prev->next = new_node;
            new_node->prev = (*list)->head->prev;
            (*list)->head->prev = new_node;
            (*list)->head = new_node;
        }
    }
    else if(index < target_index)
    {
        current_node->next = new_node;
        new_node->prev = current_node;
        new_node->next = current_node->prev;
        (*list)->head->prev = new_node;
    }
    else
    {
        new_node->next = current_node;
        new_node->prev = current_node->prev;
        current_node->prev->next = new_node;
        current_node->prev = new_node;
    }
}

void free_node (t_node *target_node)
{
    target_node->data = 0;
    target_node->prev = NULL;
    target_node->next = NULL;
    free(target_node);
}

void list_remove (t_head **list, int target_index)
{
    t_node *current_node;
    
    current_node = find_node(*(list), target_index);
    if (target_index == 0)
    {
        if ((*list)->head->next == (*list)->head)
        {
            // free current_node
        }
        else
        {
            (*list)->head = current_node->next;
            current_node->next->prev = current_node->prev;
            current_node->prev->next = current_node->next;
        }
    }
    else
    {
        current_node->prev->next = current_node->next;
        current_node->next->prev = current_node->prev;
    }
    free_node(current_node);
}

int main(void)
{
    t_head *my_list;

    //initialize head;
    my_list = (t_head *) malloc(sizeof(t_head));
    my_list->head = NULL;

    list_add(&my_list, 0, 5);
    show_list(my_list);

    list_add(&my_list, 0, 1);
    show_list(my_list);

    list_add(&my_list, 2, 3);
    show_list(my_list);

    list_add(&my_list, 2, 7);
    show_list(my_list);

    printf("-------- remove --------\n");

    list_remove(&my_list, 0);
    show_list(my_list);
    
    list_remove(&my_list, 1);
    show_list(my_list);

    list_remove(&my_list, 5);
    show_list(my_list);

    list_remove(&my_list, 0);
    show_list(my_list);

    return (0);
}
