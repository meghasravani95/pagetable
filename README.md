# pagetable

Overview:
This assignment is related to virtual memory management inside the operating system. Although, typically, an OS can support more than one process, you will only need to handle a single process in this assignment. You will practice multiple memory management concepts inside the user space. Since we cannot operate on real hardware at the OS level, this project aims to design a simulator that simulates memory management inside the user space.


In this assignment, we consider a tiny computing system that supports up to 1KB physical memory, and with 12-bit virtual addresses (4096 bytes). Suppose that the size of a virtual page and a physical frame is 128 bytes (i.e., with 7 address bits representing page offset). Prior to beginning your implementation, please think carefully about the following questions.


Part 1: 30 points
This component will simply get you started. Assume that the page table of the process is like the following picture.

# Refer pagetable.img


Note that only a few entries of the process' page table are listed, as we will only use the first seven entries in Part 1.

 # Write a program called mempart1.c for this part. The program will take only one parameter, the input sequence filename, which contains a sequence of virtual/logic memory accesses. Here, each address is stored as 8 bytes (unsigned long type). Your program should read and analyze each logical/virtual address, and translate it into the corresponding physical address based on the given page table, as shown in the above picture. Note: to simplify it, you can place the fixed page-to-frame mapping (as shown in the figure) into an array, before performing any address translation.

Each memory address is saved in a binary format. To verify that you can read the correct sequence of memory accesses, you can first print the address that you have analyzed. You can test your program with the given simple test sequence file (part1testsequence), where the first address should be 0x00000044, and the second one should be 0x00000224. Physical addresses for these two addresses (after the translation) should be 0x144 and 0x01A4.

For each address in the sequence file, you will use the above given simple page table to perform the address translation, and generate a corresponding physical address. You will output the translated physical addresses into a new file, named output-part1test. This output-part1test file should have a similar format to the given part1testsequence file, as above (i.e., each physical address should use 8 bytes (as an unsigned long value) in the output file). In this assignment, we represent each logical/physical address using 64-bits (8 bytes) to enable the program to be more general.

Once you test your program correctly with the above simple test sequence, which contains only eight memory accesses, you should use the following sequence file (part1input) as the input file for the address sequence used to generate translated physical addresses, placing them in another file called part1output. Then, you can utilize the md5sum utility to compute their corresponding checksum, via running "md5sum part1output", and you only need to write the checksum of part1output into the p1results.txt file.


Part 2: 40 points

# In this part, you will design the page table and handle deal with allocations of physical machiens on the same machine as discussed above. You will create two new source files in this part: phyframes.c and pagetable.c, as well as a new main program, named mempart2.c, plus any necessary header files. Here, phyframes.c is used to manage the physical frames, while pagetable.c will hold all functions that manages the page table for the process.

For this part, we will also assume the first physical frame is reserved for the OS, while other framess are initially available for the process. To manage physical frames, you will use a simple physical page allocation scheme:
You will allocate each physical page in the order of frame number initially, starting from 1, 2, 3, .... If physical frames are available, you will always allocate from these available frames at first.

Once there are no free physical frames, you will need to use one page replacement policy to choose a physical frame to be replaced. Currently, let's use the LRU policy, which means the page that was Least Recently Used (accessed) will be the first to be replaced.

Note that once a frame is selected to be replaced, you should do two things:
First, you should update the old page table entry such that no two virtual pages are pointing to the same physical frame. In reality, it is better to quickly locate which page table entry is actually pointing to this physical frame, typically called as ``reverse mapping''. However, you may search the whole page table of all active processes (one process in the assignment) to find out this, with significant performance overhead.
Second, you should change the page table entry of the target page to point to the frame. If you are using the "reverse mapping" mechanism, you should also set up the reverse mapping correctly.
You can use any mechanism discussed in the class to implement the strict LRU mechanism, such as counter mechanism or stack mechanism (with doubly linked list), but not second-chance algorithm. Importantly, you should update the corresponding information upon each access.

The input sequence of the program is the same as that used in Part 1. Thus, you should be able to utilize the same analyzing function to obtain the corresponding virtual address, then translate it to a physical address with your implemented page table.

In the end, you can use the same function as in Part 1 to output the translated physical address sequence into a file. For the following input sequence part2input, the program should generate output to a file named part2output.

Similar to Part 1, you only need to report the md5sum checksum of output-part2, and write it to p2result.txt file. In addition, your program should record the number of page faults encountered for the given access sequence, and this number should be reported in p2result.txt file too.
