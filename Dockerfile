FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive
ENV GO_VERSION=1.23.2
WORKDIR /workspaces/c-debugging

RUN apt-get update && apt-get install -y \
    build-essential \
    gnupg \
    iproute2 \
    clang \
    gdb \
    cmake \
    git \
    curl \
    vim \
    lldb \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# setup tailscale
RUN curl -fsSL https://tailscale.com/install.sh | sh
RUN mkdir -p /var/lib/tailscale
COPY entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]

# # setup python
# RUN pip3 install --upgrade pip
# RUN update-alternatives --install /usr/bin/python python /usr/bin/python3 10
# setup python
RUN pip3 install --upgrade pip
RUN update-alternatives --install /usr/bin/pip pip /usr/bin/pip3 10
RUN update-alternatives --install /usr/bin/python python /usr/bin/python3 10


# setup golang
RUN curl -LO https://golang.org/dl/go$GO_VERSION.linux-amd64.tar.gz \
    && tar -C /usr/local -xzf go$GO_VERSION.linux-amd64.tar.gz \
    && rm go$GO_VERSION.linux-amd64.tar.gz
ENV GOPATH=/go
ENV PATH=$PATH:/usr/local/go/bin:$GOPATH/bin
RUN go version
# export PATH=$PATH:/usr/local/go/bin:/go/bin