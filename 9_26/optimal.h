#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define frame_size 3
struct optimal
{
    int *array;
    int pages[frame_size];
    int page_faults;
    int reference_string_size;
    int count;
};
int get_first_non_zero_element_index(int *,int);
void copy_array(int *,int *,int);
typedef struct optimal optimal;
optimal *pages=NULL;

optimal * create_optimal(int *A,int ref_s_size)
{
    optimal *n = (optimal *) malloc(sizeof(optimal));
    n->array = (int *) malloc(sizeof(int)*ref_s_size);
    int i;
    for(i=0; i<ref_s_size; i++)
    {
        n->array[i]=A[i];
    }
    n->reference_string_size=ref_s_size;
    n->page_faults=0;
    n->count=0;
    return n;
}
void display_reference_string_optimal()
{
    if(pages==NULL) return;

    int i,n=pages->reference_string_size;
    for(i=0;i<n;i++)
    {
        printf("%d",pages->array[i]);
    }
    printf("\n");
}
int in_array(int,int*,int);
int find_last_element(int);
void display_optimal();
void calculate_optimal(int *A,int ref_s_size)
{
    if(pages==NULL)
    {
        pages=create_optimal(A,ref_s_size);
    }
    int *array=pages->array;
    int *frames=pages->pages;
    int i,n=pages->reference_string_size;
    for(i=0;i<n;i++)
    {
//        printf("entering element %d\n",array[i]);
        if(pages->count<frame_size)
        {
            pages->pages[pages->count]=array[i];
            pages->count++;
            pages->page_faults++;
//            display_optimal();
            continue;
        }
        if(in_array(array[i],frames,frame_size)==-1)
        {
            pages->page_faults++;
            pages->pages[find_last_element(i)]=array[i];
        }
//        display_optimal();
//        sleep(10);
    }
}

void display_optimal()
{
    int i;
    for(i=0;i<frame_size;i++)
    {
        printf("%d-",pages->pages[i]);
    }
    printf("NULL\n\n");
}
int in_array(int ele,int *array,int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        if(array[i]==ele)
        {
            return i;
        }
    }
    return -1;
}

int find_last_element(int index)
{
    int i,ref_s_size=pages->reference_string_size;
    int temp_frames[frame_size];
    int *ref_string=pages->array;
    copy_array(pages->pages,temp_frames,frame_size);
    int no_zeroes=0;
    for(i=index;i<ref_s_size;i++)
    {
        int index=in_array(ref_string[i],temp_frames,frame_size);
        if(index!=-1)
        {
            temp_frames[index]=0;
            no_zeroes++;
        }
        if(no_zeroes==frame_size-1)
        {
            break;
        }
    }
    return get_first_non_zero_element_index(temp_frames,frame_size);

}

void copy_array(int *array,int *into,int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        into[i]=array[i];
    }
}
int count_zeroes(int *array,int size)
{
    int count,i;
    for(i=0;i<size;i++)
    {
        if(array[i]==0)
        {
            count++;
        }
    }
    return count;
}

int get_first_non_zero_element_index(int *array,int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        if(array[i]!=0)
        {
            return i;
        }
    }
    return 0;
}
int get_page_faults_optimal()
{
    return pages->page_faults;
}