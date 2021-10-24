KDIR = /lib/modules/`uname -r`/build

.PHONY: kbuild
kbuild:
	make -C $(KDIR) M=`pwd`

.PHONY: clean
clean:
	make -C $(KDIR) M=`pwd` clean

.PHONY:
fmt:
	clang-format -i *.c
