#include <stdio.h>
#include <stdlib.h>
#define QUEUE_MAX 1000

typedef struct s_queue
{
    int data[QUEUE_MAX];
    int front;
    int rear;
}   t_queue;

t_queue *create_queue(void)
{
    t_queue *new;

    new = (t_queue*) malloc( sizeof(t_queue) );
    new -> front = 0;
    new -> rear = -1;

    return (new);
}

void enqueue(t_queue *queue, int data)
{
    queue -> rear = queue -> rear + 1;
    queue -> data[queue -> rear] = data;
}

void dequeue(t_queue *queue)
{
    int index;

    index = 0;
    while(index < queue->rear)
    {
        queue -> data[index] = queue -> data[index + 1];
        index++;
    }
    queue -> data [queue -> rear] = 0;
    queue -> rear -= 1;

}

void print_front(t_queue queue)
{
    printf("%d\n",queue.data[0]);
}

void show_queue(t_queue queue)
{
    int last_index;

    last_index = queue.rear;
    while(0 <= last_index)
    {
        printf("%d ", queue.data[last_index]);
        last_index--;
    }
    printf("\n");
}

int main (void)
{
    t_queue *my_queue;
    
    my_queue = create_queue();

    enqueue(my_queue, 5);
    print_front(*my_queue);

    enqueue(my_queue, 7);
    show_queue(*my_queue);
    
    enqueue(my_queue, 1);
    show_queue(*my_queue);
    
    dequeue(my_queue);
    show_queue(*my_queue);

    dequeue(my_queue);
    show_queue(*my_queue);
    return (0);
}
