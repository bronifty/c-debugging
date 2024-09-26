# Use the official Ubuntu 22.04 as the base image
FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update and install necessary packages
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

# Upgrade pip to the latest version
RUN pip3 install --upgrade pip

# Install Python packages required for data visualization
RUN pip3 install matplotlib numpy

# [Optional] Create a non-root user (e.g., vscode) with sudo privileges
# This step is optional and can be omitted for minimal setups
# RUN apt-get update && apt-get install -y sudo \
#     && useradd -ms /bin/bash vscode \
#     && adduser vscode sudo \
#     && echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers \
#     && rm -rf /var/lib/apt/lists/*

# Set Python 3 as the default python
RUN update-alternatives --install /usr/bin/python python /usr/bin/python3 10

# Set the default command to bash
CMD ["bash"]

