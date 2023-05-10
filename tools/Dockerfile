FROM ubuntu:22.04

# Install packages
RUN apt update && apt install -y \
    clang-format-12 \
    cppcheck \
    git \
    make \
    nano \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Create a non-root user named dev (in the root group for GitHub actions)
RUN useradd -rm -d /home/dev -s /bin/bash -g root -G sudo -u 1001 dev
USER dev
WORKDIR /home/dev
