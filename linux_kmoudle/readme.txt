sudo apt-get install linux-headers-`uname -r`   
    - install headers package needed for compiling modules for my kernel
create file kmain.c
create Makefile with obj-m += ...
   echo  > Makefile
add the Makefile the command that runs the kernel build system Makefile, which looks in present-work-directory (pwd) for the Makefile with obj-m

sudo dmesg -c   - show kernel log AND clear it

sudo insmod kmain.ko    - load the module to the kernel
