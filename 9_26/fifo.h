#include <stdio.h>
#include <stdlib.h>
#define frame_size 3
int count;
int page_faults;
struct node
{
    int data;
    struct node *next;
    struct node *prev;
};
typedef struct node node;

node *head;
node *tail;
node * create_node(int data)
{
    node *n=(node *)malloc(sizeof(node));
    n->data=data;
    n->next=NULL;
    n->prev=NULL;
    return n;
}
node* dequeue();
int inqueue(int);
void enqueue(int data)
{
    if(inqueue(data))
    {
        return;
    }
    else
    {
        page_faults++;
    }
    if(count==frame_size)
    {
        dequeue();
        count--;
    }
    if(head==NULL)
    {
        head=create_node(data);
        tail=head;
    }
    else
    {
        tail->next=create_node(data);
        tail->next->prev=tail;
        tail = tail->next;
    }
    count++;
}
void display_node(node *n)
{
    if(n!=NULL)
    printf("node-data:%d\n",n->data);
    else
    perror("node-empty-error\n");
}
node* dequeue()
{
    if(head==NULL)
    {
        perror("queue-empty\n");
        return NULL;
    }
    else
    {
        if(head==tail)
        {
            node *temp=head;
            head=NULL;
            tail=NULL;
            return temp;
        }
        else
        {
            node *temp=head;
            head=head->next;
            head->prev=NULL;
            return temp;
        }
    }
    return NULL;
}

void display_queue()
{
    node *ptr=head;
    while(ptr!=NULL)
    {
        printf("%d->",ptr->data);
        ptr=ptr->next;
    }
    printf("NULL\n");
}
int inqueue(int data)
{
    node *ptr=head;
    while(ptr!=NULL)
    {
        if(ptr->data==data)
        {
            return 1;
        }
        ptr=ptr->next;
    }
    return 0;

}
int get_page_fault_count()
{
    return page_faults;
}