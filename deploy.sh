#!/bin/bash

# Ensure deployment.yaml exists
if [ ! -f deployment.yaml ]; then
  echo "Error: deployment.yaml not found!"
  exit 1
fi

# Get the absolute path of the current directory
CURRENT_DIR=$(pwd)

# Replace the placeholder with the current directory path
sed "s|{{C_DEBUGGING_PATH}}|$CURRENT_DIR|g" deployment.yaml > deployment-temp.yaml

# Apply the temporary deployment manifest
kubectl apply -f deployment-temp.yaml

# Check for errors
if [ $? -eq 0 ]; then
  echo "Deployment applied successfully."
else
  echo "Error: Failed to apply deployment."
  exit 1
fi

# Optionally, remove the temporary file
rm deployment-temp.yaml