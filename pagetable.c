#include "pagetable.h"
#include "phyframe.h"
#include<stdio.h>

int pagetable_init(struct virtualpagetable *vpt)
{
	
	int k=0;
	for(k=0;k<32;k++)
	{
		vpt->pno[k]=-1;
		
	}
	return 0;
}

unsigned long getframenumber(struct virtualpagetable *vpt,struct physicaltable *ppt,unsigned long pagenumber,int count)
{
	
	int n,l,z,ptoreplace,ftoreplace;
	unsigned long framenumber;

   if(vpt->pno[pagenumber] != -1)
   {
   	// already this page is in phy memory
   	 framenumber=vpt->pno[pagenumber];
   	 ppt->globalcount[framenumber]=count;
   	  

   	
   }
   else
   {
     // check for empty frames in phy memory
   		for(n=1;n<8;n++)
   		{
       		if(ppt->framepage[n] == -1)
       		{
            	// slot is empty
            	vpt->pno[pagenumber]=n;
            	ppt->framepage[n]=pagenumber;
            	framenumber=vpt->pno[pagenumber];
            	ppt->globalcount[framenumber]=count;
            	
            	ppt->pagefault++;
            	goto label;
       		}
      
   		}
     
     //  it comes here when all frames are filled
   	   // printf("executed\n");
   		ppt->pagefault++;

        
        // finds out which frame to be repleced by checking which frame is least recently used 
        ftoreplace=1;

   	   for(z=2;z<8;z++)
   	   {
         if(ppt->globalcount[z] < ppt->globalcount[ftoreplace])
         {
         	ftoreplace=z;
         }
   	   }

        ptoreplace=ppt->framepage[ftoreplace];
		
        // once frame is selected it will initialise the page and frame values

      	ppt->framepage[ftoreplace]=-1;
      	vpt->pno[ptoreplace]=-1;
      	
      	// new page is assigned to frame and page table is updated to particular frame
      	vpt->pno[pagenumber]=ftoreplace;
        framenumber=vpt->pno[pagenumber];
      	ppt->globalcount[ftoreplace]=count;
      	
      	ppt->framepage[ftoreplace]=pagenumber;

   }

	label:
	
		return framenumber;
      
	
}