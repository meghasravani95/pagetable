~~~~~~~~~~~~~~~~~~~~
Project description:
~~~~~~~~~~~~~~~~~~~~
This Project is implemented to Convert virtual address to physical address
   
part1:
     pagetable and frametable are hardcoded.

part2:
   pagetable is implemented with 32 page entries and  physicalmemorytable with 8 page entries using LRU policy.

Given pagesize= 128 bytes= 2^7 bytes , virtual address is 12-bit , physical memory is 1KB= 2^10

So, offset will be 7 bit and pagenumber will be 5 bit(that's why 32 entries in pagetable)

no. of physicaltable entries = 2^10/2^7= 8 entries
no. of pagetable entries= 2^12/2^7 =32 entries

frametable[0] is used by operating system.
In mempart1.c:

To get 7- bit offset: address & 0x7F
To get page number: address should be rightshifted by 7 bit
with this page number corresponding frame number is retrieved and that number and offset are added to get physical address.

pagetable.h:
used to Implemented struct and function declarations

phyframe.h:
used to Implemented struct and function declarations

In pagetable.c:
Implemented page_init and getframenumber function(which takes the page number, count as parameters along with struct variables and returns frame number)

In phyframe.c:
Implemented physicaltable_init and getpagefault funtion.

In mempart2.c : 
similar to mempart1.c but the frame number is received from the pagetable which i implemented using LRU page replacement policy using global count variable.

~~~~~~~~~~~~~~~~~~~~~~
compiling instruction:
~~~~~~~~~~~~~~~~~~~~~~

part1:

%gcc mempart1.c

%./a.out part1input

Output for part1:
//Nothing
//data is written to part1output

% md5sum part1output
ceabc02825a5b908e474b053074ab53c  part1output

part2:

%gcc mempart2.c phyframe.c pagetable.c 

%./a.out part2input

output for part2:
pagefault 3210

% md5sum part2output
c95b27848ae8d4354d87678d075001f7  part2output

~~~~~~~~~~~~~~~~~~
Existing bugs:none
~~~~~~~~~~~~~~~~~~


