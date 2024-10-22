#!/bin/sh
set -e

# Start Tailscale in the background
/var/runtime/tailscaled --tun=userspace-networking --socks5-server=localhost:1055 &
TAILSCALED_PID=$!

# Bring Tailscale up using the provided auth key
/var/runtime/tailscale up --authkey=${TAILSCALE_AUTHKEY} --hostname=aws-lambda-app
echo "Tailscale started"

# Execute the standard Lambda entrypoint
exec /lambda-entrypoint.sh "$@"
