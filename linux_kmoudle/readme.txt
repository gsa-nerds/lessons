sudo apt-get install linux-headers-`uname -r`   
    - install headers package needed for compiling modules for my kernel
create file kmain.c
create Makefile with obj-m += ...
   echo  > Makefile
add the Makefile the command that runs the kernel build system Makefile, which looks in present-work-directory (pwd) for the Makefile with obj-m

sudo dmesg -c   - show kernel log AND clear it

sudo insmod kmain.ko    - load the module to the kernel
sudo rmmod kmain   -remove the module
sudo modinfo kmain  -show info about loaded module
lsmod  - show .kos that are currently loaded
sudo modprobe  - higher level control to add/remove modules


develpemt cycle:
- change code
- make all  in code directory
- sudo rmmod kmain   - remove the old loaded module
    - /sys/module/kmain/parameters  - will be deleted, if you are in there, there will be a deleted folder you are in, 
    - cd ../..  to get to /sys/module
    - cd kmain/parameters to get to the newly created folder for the newly loaded module
- sudo insmod kmain  - load the newly compiled
- cd /sys/module/kmain/parameters  - parameters directory for module
- sudo chmod a+w param_name - make it writable to normal user (not root)

