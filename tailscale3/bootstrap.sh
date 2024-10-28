#!/bin/bash 

docker build -t ubuntu-tailscale .

export TS_AUTHKEY=tskey-auth-kbU3GrC76A11CNTRL-trhqmsuvDBjsDUJk4E5xFjWSdgzwY1Te


docker run -it --name tailscale-container --privileged \
     -e TAILSCALE_AUTHKEY=$TS_AUTHKEY \
     ubuntu-tailscale