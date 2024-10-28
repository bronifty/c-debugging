FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV GO_VERSION=1.23.2

RUN apt-get update && apt-get install -y \
    build-essential \
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

RUN pip3 install --upgrade pip

RUN update-alternatives --install /usr/bin/python python /usr/bin/python3 10

RUN curl -LO https://golang.org/dl/go$GO_VERSION.linux-amd64.tar.gz \
    && tar -C /usr/local -xzf go$GO_VERSION.linux-amd64.tar.gz \
    && rm go$GO_VERSION.linux-amd64.tar.gz

ENV GOPATH=/go
ENV PATH=$PATH:/usr/local/go/bin:$GOPATH/bin

RUN go version

RUN apt-get update && apt-get install -y \
    iproute2

# Update the package list and install necessary packages
RUN apt-get update && \
    apt-get install -y bash openssh-server sudo && \
    mkdir /var/run/sshd && \
    echo 'root:your_password_here' | chpasswd && \
    sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config && \
    sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/' /etc/ssh/sshd_config && \
    rm -rf /var/lib/apt/lists/*

# Allow root to use sudo without a password (Optional: For convenience)
RUN echo 'root ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

RUN sed -i 's/PasswordAuthentication yes/PasswordAuthentication no/' /etc/ssh/sshd_config

# Expose SSH port
EXPOSE 22

WORKDIR /workspaces/c-debugging
# Start SSH server and keep the container running
CMD ["/usr/sbin/sshd", "-D"]