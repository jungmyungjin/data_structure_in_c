#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
    int data;
    struct s_node *next;
}   t_node;

t_node *list_create(int data)
{
    t_node new_node;
    t_node *node_address;

    new_node.data = data;
    new_node.next = NULL;
    node_address = &new_node;
    return (node_address);
}

int list_append(t_node **begin_list, int data)
{
    t_node new_node;
    int index = 1;

    // data to be appended
    new_node.data = data;
    new_node.next = NULL;

    // change existing list address
    (*begin_list)->next = &new_node;

    printf("old address2 : %p\n", (*begin_list)->next->next);
    printf("new address2 : %p\n", new_node.next);

    return (index);
}

int list_size(t_node *begin_list)
{
    int index;

    index = 0;
    if (begin_list->data)
    {
        index = 1;
        while(begin_list->next != NULL)
        {
            printf("data : %d\n",begin_list->data);
            begin_list = begin_list->next;
            index++;
        }
    }
    return (index);
}

int main(void)
{
    t_node *my_list;

    my_list = list_create(5);
    printf("create : %d\n",my_list->data);

    list_append(&my_list, 1);
    printf("append : %d\n",my_list->next->data);
    printf("last address : %p\n",my_list->next->next);

    //printf("list size = %d\n",list_size(my_list));

    return (0);
}
