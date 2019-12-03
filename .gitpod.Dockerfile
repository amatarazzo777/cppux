FROM gitpod/workspace-full

USER root

RUN apt-get update \
    && apt-get install -y doxygen

RUN bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"
docker run --cap-add=SYS_PTRACE --security-opt seccomp=unconfined

# Install custom tools, runtime, etc. using apt-get
# For example, the command below would install "bastet" - a command line tetris clone:
#
# RUN apt-get update \
#    && apt-get install -y bastet \
#    && apt-get clean && rm -rf /var/cache/apt/* && rm -rf /var/lib/apt/lists/* && rm -rf /tmp/*
#
# More information: https://www.gitpod.io/docs/42_config_docker/
