#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include"pagetable.h"
#include"phyframe.h"


int main(int argc, char *argv[])
{

   unsigned long pagetable[32];
   int i=0,j=0,count=0,fd,fdw;
   unsigned long address,p,p1,offset,phy[5000],p2;
   struct virtualpagetable vpt;
   struct physicaltable ppt;
     
     
      fd=open(argv[1],O_RDONLY);
     //  printf("%d\n",fd);

     fdw=open("part2output",O_WRONLY | O_CREAT |O_RDONLY , 0666);
      //printf("%d\n",fdw);

     if(fd!=-1 && fdw !=-1)
      {
       // printf("executed in mem\n");
       
        pagetable_init(&vpt);
        physicaltable_init(&ppt);
      }
    
     while(read(fd,&address,sizeof(unsigned long))!=0)
     {
    
        p= address>>7;
        //p1=pagetable[p];
        
       // printf("executed in while");
       // printf("address :%lx\n",address);
        count++;
       p1=getframenumber(&vpt,&ppt,p,count);
     //  printf("frame number before shifting:%lx\n",p1);
       
      //printf("%d\n",count);
        //p1=getframenumber(&vpt,p);
        
        offset=address & 0x7F;
     //  printf("page Num: frame number offset%lx:%lx  %lu\n",p,p1,offset);
        p2=p1<<7;
        phy[i]=p2 | offset;

       // printf("phy addr:%lx\n",phy[i]);
        i++;
    
     }
   
    while(i>0)
     {

        if(write(fdw,&phy[j],sizeof(phy[j])) != -1)
        {
         //printf("executed\n");
            i--;
           j++;
        }
      }

getpagefault(&ppt);
 close(fdw);
 close(fd);
     
  return 0;
}