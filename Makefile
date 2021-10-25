KDIR = /lib/modules/`uname -r`/build
VERSION := $(shell git describe --tags)
export VERSION

.PHONY: kbuild
kbuild:
	make -C $(KDIR) M=`pwd`/src

.PHONY: clean
clean:
	make -C $(KDIR) M=`pwd`/src clean
	rm -r root

.PHONY:
fmt:
	clang-format -i src/*.c src/*.h
	jsonnetfmt -i nfpm.jsonnet

.PHONY: package
package: dkms.conf nfpm.yaml tmp/postInstall.sh tmp/preRemove.sh
	mkdir -p build/
	nfpm package --packager deb --target build/

tmp:
	mkdir -p tmp

.PHONY: tmp/postInstall.sh
tmp/postInstall.sh: tmp
	./mkpostInstall.sh > tmp/postInstall.sh
	chmod 755 tmp/postInstall.sh

.PHONY: tmp/preRemove.sh
tmp/preRemove.sh: tmp
	./mkpreRemove.sh > tmp/preRemove.sh
	chmod 755 tmp/preRemove.sh


nfpm.yaml: nfpm.jsonnet VERSION
	jsonnet --ext-str version=$(VERSION) --ext-str srcdir=/usr/src/taskintrospection-${VERSION} -S nfpm.jsonnet > nfpm.yaml

.PHONY: dkms.conf tmp
dkms.conf:
	./mkdkms.sh > tmp/dkms.conf
