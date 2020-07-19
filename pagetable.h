#ifndef _PAGETABLE_H_
#define _PAGETABLE_H_

#include"phyframe.h"

struct virtualpagetable
{
	 int pno[32];// used to hold frame number
	 
};


int pagetable_init(struct virtualpagetable *vpt);

unsigned long getframenumber(struct virtualpagetable *vpt, struct physicaltable *ppt,unsigned long pagenumber,int count);



#endif