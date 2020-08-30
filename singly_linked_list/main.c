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

int list_append(t_node **begin_list, int data)
{
    t_node *new_node;
    t_node *last_node;
    int index;

    index = 0;
    if (begin_list == NULL)
    {
        return (-1);
    }
    new_node = list_create(data);
    last_node = *begin_list;
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

t_node *list_get(t_node *begin_list, int n)
{
    int index;
    t_node *node;

    index = 0;
    node = begin_list;
    if(n < 0)
    {
        return (NULL);
    }
    while(index != n && index <= n)
    {
        node = node->next;
        index++;
    }
    if (index < n)
    {
        return (NULL);
    }
    return (node);
}

int list_find(t_node *begin_list, int data)
{
    int found_index;

    found_index = 0;
    while(begin_list != NULL)
    {
        if (begin_list->data == data)
        {
            return (found_index);
        }
        begin_list = begin_list->next;
        found_index++;
    }
    return (-1);
}

int list_remove(t_node **begin_list, int n)
{
    int index;
    t_node *previous_node;
    t_node *current_node;
    t_node *next_node;

    index = 0;
    current_node = *begin_list;
    while(current_node != NULL && index < n)
    {
        previous_node = current_node;
        current_node = current_node->next;
        index++;
    }
    next_node = current_node->next;

    if (index == n)
    {
        // target is first node
        if (n == 0)
        {
         *begin_list = next_node;
         free(current_node);
        }
        // target is last node
        else if(current_node->next == NULL)
        {
            previous_node->next = NULL;
            free(current_node);
        }
        // target is between node
        else
        {
            previous_node->next = current_node->next;
            free(current_node);
        }
        return (1);
    }
    return (0);
}

int list_insert(t_node **begin_list, int data, int n)
{
    int index;
    t_node *previous_node;
    t_node *current_node;
    t_node *new_node;

    if (n < 0)
        return (-1);
    new_node = list_create(data);
    index = 0;
    current_node = *begin_list;
    while(current_node != NULL && index < n)
    {
        previous_node = current_node;
        current_node = current_node->next;
        index++;
    }
    // target is first node
    if (n == 0)
    {
        new_node->next = (*begin_list)->next;
        *begin_list = new_node;
    }
    // target is last node
    else if(index < n)
    {
        previous_node->next = new_node;
    }
    // target is between node
    else
    {
        previous_node->next = new_node;
        new_node->next = current_node;
    }
    return (index);
}

void show_list(t_node *begin_list)
{
    int index;
    
    index = 0;
    while(begin_list != NULL)
    {
        printf("[%d]%p : %d", index, begin_list, begin_list->data);
        if (begin_list->next != NULL)
            printf(" => ");
        begin_list = begin_list->next;
        index++;
    }
   printf("\n");
}

int main(void)
{
    t_node *my_list;

    my_list = list_create(5);
    show_list(my_list);

    list_append(&my_list, 1);
    show_list(my_list);

    printf("list size = %d\n",list_size(my_list));

    printf("list_get(0) data = %d\n",list_get(my_list, 0)->data);

    list_append(&my_list, 3);

    printf("list_find(1) index = %d\n",list_find(my_list, 1));
    show_list(my_list);

    printf("list_remove(1) result = %d\n",list_remove(&my_list, 1));
    show_list(my_list);

    list_insert(&my_list, 7, 1);
    show_list(my_list);

    return (0);
}
