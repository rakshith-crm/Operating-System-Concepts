#include <stdio.h>
#include <stdlib.h>
#define frame_size 3
struct lru
{
    int array[frame_size];
    int lru_array[frame_size];
    int count;
    int page_faults;
};

typedef struct lru lru;
lru * create_lru()
{
    lru *n=(lru *)malloc(sizeof(lru));
    n->count=0;
    n->page_faults=0;
    return n;
}
lru *pagetable=NULL;
void insert_lru(int page)
{
    if(pagetable==NULL)
    {
        pagetable=create_lru();
        pagetable->array[0]=page;
        pagetable->lru_array[0]=0;
        pagetable->count++;
        pagetable->page_faults++;
        return;
    }
    int count=pagetable->count,i;
    int max=0;
    int replace_index=0;
    int flag=0;
    for(i=0;i<count;i++)
    {
        if(pagetable->array[i]==page)
        {
            pagetable->lru_array[i]=0;
            flag=1;
        }
        else
        {
            pagetable->lru_array[i]++;
        }
        if(max < pagetable->lru_array[i])
        {
            max=pagetable->lru_array[i];
            replace_index=i;
        }
    }
    if(count==frame_size && flag==0)
    {
        pagetable->array[replace_index]=page;
        pagetable->lru_array[replace_index]=0;
        pagetable->page_faults++;
    }
    else if(flag==0 && count<frame_size)
    {
        pagetable->array[count]=page;
        pagetable->lru_array[count]=0;
        pagetable->count++;
        pagetable->page_faults++;
    }
    
}
void display_lru()
{
    if(pagetable==NULL)
    {
        int i;
        for(i=0;i<frame_size;i++)
        {
            printf("$-");
        }
        printf("NULL\n");
        return;
    }
    int i;
    for(i=0;i<pagetable->count;i++)
    {
        printf("%d-",pagetable->array[i]);
    }
    for(i=0;i<(frame_size-pagetable->count);i++)
    {
        printf("$-");
    }
    printf("NULL\n");
    for(i=0;i<pagetable->count;i++)
    {
        printf("%d-",pagetable->lru_array[i]);
    }
    for(i=0;i<(frame_size-pagetable->count);i++)
    {
        printf("$-");
    }
    printf("NULL\n");
}
int get_lru_page_fault()
{
    return pagetable->page_faults;
}