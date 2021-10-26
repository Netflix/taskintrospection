# Task Introspection
Task introspection is a kernel module that's meant to act as an alternative to /proc/pid/status.
Parsing /proc/pid/status can be difficult.
So far, it only provides a limited subset of the fields in /proc/pid/status.

# Installation

The only supported platform is Ubuntu Bionic running a 5.10+ kernel.

```
curl -s https://packagecloud.io/install/repositories/netflix/titus/script.deb.sh | sudo bash
apt-get install -y taskintrospection
```
