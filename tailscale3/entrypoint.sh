#!/bin/bash
set -e

# Start Tailscale daemon
tailscaled &

# Wait for tailscaled to initialize
sleep 5

# Authenticate Tailscale (requires manual interaction)
tailscale up --authkey=${TAILSCALE_AUTHKEY} --hostname=tailscale-container --ssh --reset

# Start a sample service
python3 -m http.server 8000

# Keep the container running
tail -f /dev/null