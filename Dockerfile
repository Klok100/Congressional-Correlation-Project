FROM james9909/cs225-autograder:latest
RUN yum install -y gdb
ENTRYPOINT bash