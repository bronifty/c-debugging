# Stage 1: Build Stage
FROM public.ecr.aws/lambda/nodejs:20 AS builder
WORKDIR /app

# Copy application files
COPY . ./

# Install dependencies if any (uncomment if needed)
# RUN npm install

# Stage 2: Production Image
FROM public.ecr.aws/lambda/nodejs:20

# Set working directory
WORKDIR /var/task

# Copy Node.js Lambda function from builder
COPY --from=builder /app/index.js .

# Copy Tailscale binaries from the tailscale image on Docker Hub
COPY --from=docker.io/tailscale/tailscale:stable /usr/local/bin/tailscaled /var/runtime/tailscaled
COPY --from=docker.io/tailscale/tailscale:stable /usr/local/bin/tailscale /var/runtime/tailscale

# Ensure Tailscale binaries are executable
RUN chmod +x /var/runtime/tailscaled /var/runtime/tailscale

# Create necessary symlinks to redirect Tailscale directories to /tmp/tailscale
RUN mkdir -p /var/run && ln -s /tmp/tailscale /var/run/tailscale && \
    mkdir -p /var/cache && ln -s /tmp/tailscale /var/cache/tailscale && \
    mkdir -p /var/lib && ln -s /tmp/tailscale /var/lib/tailscale && \
    mkdir -p /var/task && ln -s /tmp/tailscale /var/task/tailscale

# Copy custom entrypoint script
COPY entrypoint.sh /app/entrypoint.sh

# Make sure the entrypoint script is executable
RUN chmod +x /app/entrypoint.sh

# Set the custom entrypoint
ENTRYPOINT ["/app/entrypoint.sh"]

# Specify the Lambda handler
CMD [ "index.handler" ]

# FROM public.ecr.aws/lambda/provided:al2 as builder
# WORKDIR /app
# COPY . ./
# # This is where one could build the application code as well.

# FROM public.ecr.aws/lambda/provided:al2
# # Copy binary to production image.
# COPY --from=builder /app/bootstrap /var/runtime/bootstrap

# # Copy Tailscale binaries from the tailscale image on Docker Hub.
# COPY --from=docker.io/tailscale/tailscale:stable /usr/local/bin/tailscaled /var/runtime/tailscaled
# COPY --from=docker.io/tailscale/tailscale:stable /usr/local/bin/tailscale /var/runtime/tailscale
# RUN mkdir -p /var/run && ln -s /tmp/tailscale /var/run/tailscale && \
#     mkdir -p /var/cache && ln -s /tmp/tailscale /var/cache/tailscale && \
#     mkdir -p /var/lib && ln -s /tmp/tailscale /var/lib/tailscale && \
#     mkdir -p /var/task && ln -s /tmp/tailscale /var/task/tailscale

# # Run on container startup.
# ENTRYPOINT ["/var/runtime/bootstrap"]
