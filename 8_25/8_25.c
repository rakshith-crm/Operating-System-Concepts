#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define displacement 12
void print_binary(int number)
{
	int i;
	for(i=31;i>=0;i--)
	{
		int temp=number;
		if((temp>>i)&1)
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
	}
	printf(" -> %d\n",number);
}
int main(int argc,char *arg[])
{
	if(argc!=2)
	{
		fprintf(stderr,"expected : 1 argument (integer-type); got %d arguments\n",argc-1);
		return -1;
	}
	int number=atoi(arg[1]);
	int offset_mask=pow(2,displacement)-1;
	int pageno_mask=~offset_mask;
	printf("\n###virtual address in binary###\n");
	print_binary(number);
	printf("###offset mask in binary###\n");
	print_binary(offset_mask);
	printf("###page number mask in binary###\n");
	print_binary(pageno_mask);
	printf("\n\n~Output~\n--------\n");
	printf("The address %d is translated as\n",number);
	printf("page number : %d\n",(pageno_mask&number)>>displacement);
	printf("offset      : %d\n",number&offset_mask);


	return 0;
}
