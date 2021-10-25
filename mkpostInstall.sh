#!/bin/bash

cat <<EOF
#!/bin/bash
dkms add -m taskintrospection -v ${VERSION}
dkms build -m taskintrospection -v ${VERSION} && dkms install -m taskintrospection -v ${VERSION} || true
EOF