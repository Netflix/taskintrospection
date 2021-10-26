FROM ubuntu:bionic
RUN apt-get update && apt-get install --install-recommends -y dkms git wget linux-headers-generic-hwe-18.04
RUN wget https://github.com/goreleaser/nfpm/releases/download/v2.7.1/nfpm_amd64.deb && dpkg -i nfpm_amd64.deb && rm nfpm_amd64.deb
RUN wget https://github.com/google/go-jsonnet/releases/download/v0.17.0/jsonnetfmt-go_0.17.0_linux_amd64.deb https://github.com/google/go-jsonnet/releases/download/v0.17.0/jsonnet-go_0.17.0_linux_amd64.deb && \
	dpkg -i jsonnet-go_0.17.0_linux_amd64.deb jsonnetfmt-go_0.17.0_linux_amd64.deb && \
	rm jsonnetfmt-go_0.17.0_linux_amd64.deb jsonnet-go_0.17.0_linux_amd64.deb
