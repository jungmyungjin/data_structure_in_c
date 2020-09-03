#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_node
{
    int data;
    struct s_node *link;
}   t_node;

typedef struct s_head
{
    t_node *head;
}   t_head;

t_node *create_node(int data)
{
    t_node *new_node;

    new_node = (t_node*) malloc(sizeof(t_node));
    new_node->data = data;
    new_node->link = NULL;
    return (new_node);
}

void show_list(t_head *list_head)
{
    t_node *current_node;

    current_node = list_head->head;
    while(current_node != NULL)
    {
        printf("%p : [%d]->[%p]", current_node, current_node->data, current_node->link);
        current_node = current_node->link;
        if (current_node == list_head->head)
            break;
        printf(",   ");
    }
    printf("\n\n");
}

t_node *find_node (t_head *list_head, int target_index)
{
    int index;
    t_node *target_node;
    t_node *current_node;

    index = 1;
    target_node = NULL;
    current_node = list_head->head;
    if(target_index == 0)
    {
        return (current_node);
    }
    else if(target_index > 0 && current_node != NULL)
    {
        current_node = current_node->link;
        while(index < target_index)
        {
            if(current_node->link == list_head->head)
                break;
            current_node = current_node->link;
            index++;
        }
        target_node = current_node;
    }
    return (target_node);
}

void list_add(t_head **list_head, int target_index, int data)
{
    t_node *new_node;
    t_node *nth_node;
    t_node *nth_prev_node;
    t_node *last_node;

    new_node = create_node(data);
    last_node = find_node(*list_head, INT_MAX);
    nth_node = find_node(*list_head, target_index);
    nth_prev_node = find_node(*list_head, target_index - 1);
    // target is first in list
    if( target_index == 0 )
    {
        // add first node
        if((*list_head)->head == NULL)
        {
            (*list_head)->head = new_node;
            new_node->link = new_node;
        }
        // insert first node
        else
        {
            new_node->link = (*list_head)->head;
            last_node = find_node(*list_head, INT_MAX);
            last_node -> link = new_node;
            (*list_head)->head = new_node;
        }
    }
    // target is last in list
    else if (nth_node == last_node)
    {
        nth_node->link = new_node;
        new_node->link = (*list_head)->head;
    }
    // target is between in list
    else
    {
        new_node->link = nth_node;
        nth_prev_node->link = new_node;
    }
}

void free_node(t_node *target_node)
{
    target_node->data = 0;
    target_node->link = NULL;
    free(target_node);
}

void list_remove(t_head **list_head, int target_index)
{
    t_node *nth_node;
    t_node *nth_prev_node;
    t_node *nth_next_node;
    t_node *last_node;

    nth_node = find_node(*list_head, target_index);
    nth_next_node = find_node(*list_head, target_index+1);
    last_node = find_node(*list_head, INT_MAX);
    nth_prev_node = NULL;
    // list have only one node
    if ((*list_head)->head->link == (*list_head)->head)
    {
        (*list_head)->head = NULL;
    }
    // target is first node
    else if(target_index == 0)
    {
        (*list_head)->head = nth_next_node;
        last_node->link = (*list_head)->head;
    }
    else
    {
        nth_prev_node = find_node(*list_head, target_index-1);
        nth_prev_node->link = nth_node->link;
    }
    free_node(nth_node);
}

int main (void)
{
    t_head *my_list;

    //*my_list create and initialize
    my_list = (t_head*) malloc(sizeof(t_head));
    my_list->head = NULL;

    list_add(&my_list,0,5);
    show_list(my_list);
    
    list_add(&my_list,0,1);
    show_list(my_list);

    list_add(&my_list,10,10);
    show_list(my_list);
    
    list_add(&my_list,1, 7);
    show_list(my_list);

    printf("============== remove ==================\n");
    list_remove(&my_list,0);
    show_list(my_list);

    list_remove(&my_list,1);
    show_list(my_list);

    list_remove(&my_list,1);
    show_list(my_list);

    list_remove(&my_list,0);
    show_list(my_list);

    return (0);
}
