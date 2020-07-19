
#ifndef _PFRAME_H_
#define _PFRAME_H_

struct physicaltable
{
	 int framepage[8];
	 int globalcount[8];
	 int pagefault;
};


int physicaltable_init(struct physicaltable *ppt);

int getpagefault(struct physicaltable *ppt);

#endif