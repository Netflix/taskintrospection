#!/bin/bash


set -euo pipefail
cat << EOF
PACKAGE_NAME="taskintrospection"
PACKAGE_VERSION="${VERSION}"
CLEAN="make clean"
MAKE[0]="make -C \${kernel_source_dir} M=\${dkms_tree}/\${PACKAGE_NAME}/\${PACKAGE_VERSION}/build"
CLEAN="make -C \${kernel_source_dir} M=\${dkms_tree}/\${PACKAGE_NAME}/\${PACKAGE_VERSION}/build clean"
BUILT_MODULE_NAME[0]="taskintrospection"
DEST_MODULE_LOCATION[0]="/extra"
AUTOINSTALL="yes"
EOF



