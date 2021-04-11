#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fifo.h"
#include "lru.h"
#include "optimal.h"
#define page_limit_number 7
#define reference_string_size 15

void generate_reference_string(int *array,int len)
{
    int i;
    srand(time(0));
    for(i=0;i<len;i++)
    {
        int number;
        if(i>0)
        {
            number=(rand()%page_limit_number)+1;
            while(number==array[i-1])
            {
                number=(rand()%page_limit_number)+1;
            } 
        }
        
        array[i]=number;
    }
}

int main()
{
    int ref_string[reference_string_size],i;
    generate_reference_string(ref_string,reference_string_size);

    for(i=0;i<reference_string_size;i++)
    {
        printf("%d",ref_string[i]);
    }
    printf("\n");

    for(i=0;i<reference_string_size;i++)
    {
        enqueue(ref_string[i]);
    }

    for(i=0;i<reference_string_size;i++)
    {
        insert_lru(ref_string[i]);
    }

    calculate_optimal(ref_string,reference_string_size);
/*
    while(1)
    {
        int opt,ele;
        printf("\n1)Enqueue\n2)get pagefault count\n3)Display\n4)End\n\nEnter Choice : ");
        scanf("%d",&opt);
        if(opt==1)
        {
            printf("Enter ele: ");
            scanf("%d",&ele);
            insert_lru(ele);
        }
        else if(opt==2)
        {
            printf("\npagefault : %d\n",get_lru_page_fault());
        }
        else if(opt==3)
        {
            display_lru();
        }
        else
        {
            break;
        }
    }
*/
    printf("\nNumber of page faults (FIFO)= %d",get_page_fault_count());
    printf("\nNumber of page faults  (LRU)= %d\n",get_lru_page_fault());
    printf("\nNumber of page faults  (OPT)= %d\n",get_page_faults_optimal());
    return 0;
}