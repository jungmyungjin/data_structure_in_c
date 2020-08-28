#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
    int data;
    struct s_node *next;
}   t_node;

t_node *list_create(int data)
{
    t_node *new_node = (t_node*) malloc(sizeof(t_node));

    new_node->data = data;
    new_node->next = NULL;

    return (new_node);
}

int list_append(t_node *begin_list, int data)
{
    t_node *new_node = list_create(data);
    t_node *last_node;
    int index = 1;
   
    last_node = begin_list;
    while(last_node->next != NULL)
    {
        last_node = last_node->next;
    }
    last_node->next = new_node;

    return (index);
}

int list_size(t_node *begin_list)
{
    int size;

    size = 1;
    if (begin_list == NULL)
    {
        return (0);
    }
    while (begin_list->next != NULL)
    {
        printf("data : %d\n",begin_list->data);
        begin_list = begin_list->next;
        size++;
    }
    return (size);
}

int main(void)
{
    t_node *my_list;

    my_list = list_create(5);
    printf("create : %d\n",my_list->data);

    printf("befor address : %p\n",my_list);
    list_append(my_list, 1);
    printf("append : %d\n",my_list->next->data);
    printf("after address : %p\n",my_list);

    printf("list size = %d\n",list_size(my_list));

    return (0);
}
