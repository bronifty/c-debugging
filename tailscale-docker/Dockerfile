# Use Ubuntu 22.04 as the base image
FROM ubuntu:22.04

# Set environment variables to non-interactive to avoid prompts
ENV DEBIAN_FRONTEND=noninteractive

# Update package lists and install necessary dependencies
RUN apt-get update && apt-get install -y \
    curl \
    gnupg \
    lsb-release \
    sudo \
    iptables \
    python3 \
    systemd \
    && rm -rf /var/lib/apt/lists/*

# Add Tailscale's official GPG key
RUN curl -fsSL https://pkgs.tailscale.com/stable/ubuntu/jammy.gpg | sudo gpg --dearmor -o /usr/share/keyrings/tailscale-archive-keyring.gpg

# Add Tailscale's repository to APT sources
RUN echo "deb [signed-by=/usr/share/keyrings/tailscale-archive-keyring.gpg] https://pkgs.tailscale.com/stable/ubuntu jammy main" | sudo tee /etc/apt/sources.list.d/tailscale.list

# Update package lists again and install Tailscale
RUN apt-get update && apt-get install -y tailscale && rm -rf /var/lib/apt/lists/*

# Create Tailscale state directory and set permissions
RUN mkdir -p /var/lib/tailscale && chown -R root:root /var/lib/tailscale

# Copy the entrypoint script into the container
COPY entrypoint.sh /entrypoint.sh

# Make sure the entrypoint script is executable
RUN chmod +x /entrypoint.sh

# Expose necessary ports (e.g., web server on 8000 and Tailscale SOCKS5 proxy on 1055)
EXPOSE 8000 1055

# Use the entrypoint script as the container's entrypoint
ENTRYPOINT ["/entrypoint.sh"]

