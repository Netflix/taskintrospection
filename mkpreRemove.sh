#!/bin/bash

cat <<EOF
#!/bin/bash
dkms remove -m taskintrospection -v ${VERSION} --all || true
EOF