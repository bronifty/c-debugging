#!/bin/bash
set -e

echo "--authkey=\"${TS_AUTHKEY}\""

echo "Entrypoint script started."

# Redirect logs to stdout for Docker logging
exec > >(tee -i /var/log/entrypoint.log)
exec 2>&1

# Start tailscaled daemon
echo "Starting tailscaled..."
tailscaled --state=/var/lib/tailscale/tailscaled.state --tun=userspace-networking --socks5-server=localhost:1055 &
TAILSCALED_PID=$!

# Wait for tailscaled to initialize
echo "Waiting for tailscaled to initialize..."
sleep 5

# Check if tailscaled is running
if ! pgrep tailscaled > /dev/null; then
    echo "Error: tailscaled failed to start."
    exit 1
fi
echo "tailscaled is running with PID $TAILSCALED_PID."

# Authenticate and bring up Tailscale
echo "Bringing up Tailscale..."
# tailscale up --authkey="${TS_AUTHKEY}" --ssh --reset
tailscale up --authkey="${TS_AUTHKEY}" --ssh --advertise-tags=tag:container --reset

# Verify Tailscale status
echo "Verifying Tailscale status..."
tailscale status

# Keep the container running
echo "Tailscale up completed successfully. Keeping the container alive..."
wait $TAILSCALED_PID