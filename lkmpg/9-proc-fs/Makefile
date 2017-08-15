module = procfs-1
obj-m += $(module).o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	insmod $(module).ko

remove:
	rmmod $(module)
