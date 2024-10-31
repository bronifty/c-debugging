#!/bin/bash
set -e

# Function to clean up on exit
cleanup() {
    echo "Shutting down Tailscale..."
    tailscale down
    kill $TAILSCALED_PID
    exit 0
}

# Trap SIGINT and SIGTERM to gracefully shutdown
trap cleanup SIGINT SIGTERM

# Start Tailscale daemon in the background
echo "Starting Tailscale..."
tailscaled --tun=userspace-networking --socks5-server=localhost:1055 &
TAILSCALED_PID=$!

# Wait for tailscaled to initialize
sleep 5

# Authenticate and connect Tailscale
echo "Authenticating Tailscale..."
tailscale up --authkey=${TAILSCALE_AUTHKEY} --hostname=${TAILSCALE_HOSTNAME:-lambda-container}

echo "Tailscale started successfully."

# Start the Lambda runtime in the foreground
echo "Starting Lambda Runtime..."
exec /var/runtime/bootstrap "$@"