#!/bin/bash

# Build the docker image
docker build -t ubuntu22-debug-c .

# Set the current directory
CURRENT_DIR=$(pwd)

# Create a temporary directory for modified files
TEMP_DIR="$CURRENT_DIR/overlays/dev-temp"
mkdir -p "$TEMP_DIR"

# Copy the original kustomization file to the temp directory
cp overlays/dev/kustomization.yaml $TEMP_DIR/kustomization.yaml

# Create the modified volume-patch file in the temp directory
sed "s|/absolute/path/to/desired/directory|$CURRENT_DIR|g" overlays/dev/volume-patch.yaml > $TEMP_DIR/volume-patch-temp.yaml

# Update the kustomization file to use the temporary volume-patch file
sed -i '' 's/volume-patch.yaml/volume-patch-temp.yaml/' $TEMP_DIR/kustomization.yaml

# Print the contents of the modified kustomization file
echo "Contents of modified kustomization.yaml:"
cat $TEMP_DIR/kustomization.yaml

# Build and apply the kustomization using the temporary directory with verbose output
kustomize build $TEMP_DIR | kubectl apply -f -

# Clean up: remove the temporary directory
rm -rf $TEMP_DIR

# Verify the deployment
kubectl get pods