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
    iproute2 \
    curl

RUN curl -fsSL https://tailscale.com/install.sh | sh


# Start Tailscale in userspace networking mode with SOCKS5 proxy
RUN tailscaled --tun=userspace-networking --socks5-server=localhost:1055 &


# Install Python dependencies
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Copy the Lambda function code
COPY lambda_function.py .

# Copy the entrypoint script
COPY entrypoint.sh .
RUN chmod +x entrypoint.sh

# Expose necessary ports if needed (e.g., Tailscale SOCKS5 proxy)
EXPOSE 1055

# Set the entrypoint to initialize Tailscale and start Lambda runtime
ENTRYPOINT ["/entrypoint.sh"]

# Specify the Lambda handler
CMD ["lambda_function.handler"]
