#!/bin/bash

echo "TS_AUTHKEY: $TS_AUTHKEY"

set -e

# Function to start Tailscale
start_tailscale() {
    echo "Starting Tailscale..."
    tailscale up --auth-key="$TS_AUTHKEY" --ssh --reset
}

# Function to keep the container running
keep_alive() {
    echo "Tailscale started. Keeping the container alive..."
    tail -f /dev/null
}

# Start Tailscale and keep the container running
start_tailscale
keep_alive