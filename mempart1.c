#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include"pagetable.h"

int main(int argc, char *argv[])
{

   unsigned long int pagetable[32];
   int i=0,j=0,fd,fdw;
   unsigned long int address,p,p1,o,phy[5000],p2;
  
    
   pagetable[0]=2;
   pagetable[1]=4;
   pagetable[2]=1;
   pagetable[3]=7;
   pagetable[4]=3;
   pagetable[5]=5;
   pagetable[6]=6;
     
     

      fd=open(argv[1],O_RDONLY);
       //printf("%d\n",fd);

     fdw=open("part1output",O_WRONLY | O_CREAT |O_RDONLY , 0666);
     // printf("%d\n",fdw);
    
     while(read(fd,&address,sizeof(unsigned long))!=0)
     {
    
        p= address>>7;
        p1=pagetable[p];
        p2=p1<<7;
        o=address & 0x7F;
       // printf("%lx:%lx  %lu\n",p,p1,o);
        phy[i]=p2 | o;

       // printf("%lx\n",phy[i]);
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

 close(fdw);
 close(fd);
     
	return 0;
}