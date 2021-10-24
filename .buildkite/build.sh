#!/bin/bash -x
VERSION=$(git describe --tags)

cat > dkms.conf <<EOF
PACKAGE_NAME="taskintrospection"
PACKAGE_VERSION="${VERSION}"
CLEAN="make clean"
MAKE[0]="make -C \${kernel_source_dir} M=\${dkms_tree}/\${PACKAGE_NAME}/\${PACKAGE_VERSION}/build"
CLEAN="make -C \${kernel_source_dir} M=\${dkms_tree}/\${PACKAGE_NAME}/\${PACKAGE_VERSION}/build clean"
BUILT_MODULE_NAME[0]="taskintrospection"
DEST_MODULE_LOCATION[0]="/updates"
AUTOINSTALL="yes"
EOF

cat dkms.conf
mkdir -p dkms
mkdir -p src
dkms add . --dkmstree $PWD/dkms --sourcetree $PWD/src
dkms mkdeb -m taskintrospection -v 0.1 --dkmstree $PWD/dkms --sourcetree $PWD/src

