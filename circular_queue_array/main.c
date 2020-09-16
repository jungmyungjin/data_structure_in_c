#include <stdio.h>
#include <stdlib.h>
#define QUEUE_SIZE 5

typedef struct s_queue
{
    int data[QUEUE_SIZE];
    int front;
    int rear;
}   t_queue;

t_queue *create_queue(void)
{
    t_queue *new;
    
    new = (t_queue*) malloc(sizeof(t_queue));
    new -> front = 0;
    new -> rear = -1;

    return (new);
}

void queue_blank(t_queue queue)
{
    if (queue.front == 0 && queue.rear == -1)
        printf("queue blank : 1\n");
    else
        printf("queue blank : 0\n");
}

void enqueue(t_queue **queue, int data)
{
    (*queue) -> rear = ((*queue)->rear + 1 ) % QUEUE_SIZE;
    (*queue)->data[(*queue) -> rear] = data;
}

void print_front(t_queue queue)
{
    printf("%d\n",queue.data[queue.front]);
}

void show_queue(t_queue queue)
{
    int last_index;

    last_index = QUEUE_SIZE - 1;
    while (last_index >= 0)
    {
        printf("%d ",queue.data[last_index]);
        last_index--;
    }
    printf("\n");
}

void dequeue(t_queue **queue)
{
    int index;

    index = 0;
    while(index < QUEUE_SIZE)
    {
        (*queue)->data[index] = (*queue)->data[index+1];
        index++;
    }
    (*queue)->data[QUEUE_SIZE-1] = 0;
    (*queue)->rear -= 1;
}

int main(void)
{
    t_queue *my_queue;

    my_queue = create_queue();

    queue_blank(*my_queue);

    enqueue(&my_queue, 5);
    print_front(*my_queue);

    enqueue(&my_queue, 7);
    show_queue(*my_queue);

    dequeue(&my_queue);
    show_queue(*my_queue);
    
    enqueue(&my_queue, 1);
    show_queue(*my_queue);
    
    enqueue(&my_queue, 2);
    show_queue(*my_queue);

    enqueue(&my_queue, 3);
    show_queue(*my_queue);

    enqueue(&my_queue, 4);
    show_queue(*my_queue);
    
    enqueue(&my_queue, 5);
    show_queue(*my_queue);

    dequeue(&my_queue);
    show_queue(*my_queue);
    
    dequeue(&my_queue);
    show_queue(*my_queue);
    
    dequeue(&my_queue);
    show_queue(*my_queue);
    
    dequeue(&my_queue);
    show_queue(*my_queue);
    
    dequeue(&my_queue);
    show_queue(*my_queue);

    return (0);
}
