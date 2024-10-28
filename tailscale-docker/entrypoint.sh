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
tailscale up --authkey=${TAILSCALE_OAUTH_SECRET} --hostname=${TAILSCALE_HOSTNAME:-tailscale-container}

echo "Tailscale started successfully."

# Start your main service (e.g., a web server)
# Here, we're starting a simple Python HTTP server on port 8000
echo "Starting web server..."
python3 -m http.server 8000 &

# Wait indefinitely to keep the container running
wait