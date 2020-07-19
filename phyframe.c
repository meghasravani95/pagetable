#include"phyframe.h"
#include "pagetable.h"
#include<stdio.h>

int physicaltable_init(struct physicaltable *ppt)
{
	int p;
		
	for(p=0;p<8;p++)
	{
	
		ppt->framepage[p]=-1; // used to hold page number to implement reverse mapping
		ppt->globalcount[p]=0;// will hold at what count the frame in phy memory is accessed
		ppt->pagefault=0;// to hold pagefaults value
	}
}

int getpagefault(struct physicaltable *ppt)
{
	printf("pagefault %d\n",ppt->pagefault);
}
