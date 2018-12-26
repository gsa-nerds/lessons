obj-m += kmain.o

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
