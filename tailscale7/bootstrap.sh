#!/bin/bash


# works
docker run -it --name tailscale-container --privileged ubuntu:22.04 /bin/bash

# does not work because running not in / as root but rather in userspace, so it does not have access to /dev/net/tun 
docker run -it --name tailscale-container --cap-add=NET_ADMIN --cap-add=SYS_MODULE ubuntu:22.04 /bin/bash

# inside container
apt-get update
apt-get install -y curl gnupg lsb-release
# Add Tailscale's GPG key
curl -fsSL https://pkgs.tailscale.com/stable/ubuntu/jammy.gpg | apt-key add -

# Add Tailscale repository
echo "deb https://pkgs.tailscale.com/stable/ubuntu jammy main" | tee /etc/apt/sources.list.d/tailscale.list

# Update package lists again
apt-get update

# Install Tailscale
apt-get install -y tailscale
# Start Tailscale daemon manually if required
tailscaled & 
wait 10 

export TS_AUTHKEY="tskey-client-knCC6JxJs711CNTRL-g497XJaLxN4fyVjrbWskT48TWmm3G6HR3?ephemeral=false" && tailscale up --authkey="${TS_AUTHKEY}" --ssh --advertise-tags=tag:container --reset

tailscale status

ip a show tailscale0


# exit container
exit 

# outside container
docker volume create tailscale-state

docker run -it --name tailscale-container --cap-add=NET_ADMIN --cap-add=SYS_MODULE -v tailscale-state:/var/lib/tailscale ubuntu:22.04 /bin/bash

# If you're reusing an existing container, ensure that /var/lib/tailscale points to the mounted volume.
ln -s /var/lib/tailscale /var/lib/tailscale

# Let's run a simple web server inside the container to test connectivity.

apt-get install -y python3
python3 -m http.server 8000

# Find the Tailscale IP of your container:
tailscale ip -4

# access the web server from outside container
curl http://100.64.0.1:8000

# T-Shoot

# check for the TUN device
ls -l /dev/net/tun
# if missing, create it inside the container
mkdir -p /dev/net
mknod /dev/net/tun c 10 200
chmod 0666 /dev/net/tun

# network bridge should work, else try it with host mode
docker run -it --name tailscale-container --privileged --network=host ubuntu:22.04 /bin/bash

# check status of tailscale daemon
systemctl status tailscaled

# or if running manually
tailscaled &
tailscale up

# review logs for error messages
journalctl -u tailscaled





## Not Working
# Enable Tailscale to start on boot (optional)
systemctl enable tailscaled

# Start Tailscale daemon
systemctl start tailscaled