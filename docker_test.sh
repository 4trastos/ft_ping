#!/bin/bash

echo "Docker para ft_ping..."

docker run -it --rm \
  --cap-add=NET_RAW \
  -v "$(pwd):/workspace" \
  -w /workspace \
  debian:bullseye \
  bash -c "apt update && apt install -y build-essential inetutils-ping && bash"