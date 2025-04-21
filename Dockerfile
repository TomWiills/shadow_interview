FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    python3 \
    python3-dev \
    python3-pip \
    g++ \
    git \
    libpython3-dev \
    pkg-config \
    && apt-get clean

RUN pip3 install matplotlib numpy

WORKDIR /docker


