#!/bin/bash

echo "Docker para ft_ping..."

docker run -it --rm \
  --cap-add=NET_RAW \
  -v $(pwd):/workspace \
  -w /workspace \
  ubuntu:22.04 \
  bash -c "apt update && apt install -y build-essential && apt install -y iputils-ping && bash"