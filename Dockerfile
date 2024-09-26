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
    && rm -rf /var/lib/apt/lists/*

# [Optional] Create a non-root user (e.g., vscode) with sudo privileges
# This step is optional and can be omitted for minimal setups
# RUN apt-get update && apt-get install -y sudo \
#     && useradd -ms /bin/bash vscode \
#     && adduser vscode sudo \
#     && echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers \
#     && rm -rf /var/lib/apt/lists/*

# Set the default command to bash
CMD ["bash"]