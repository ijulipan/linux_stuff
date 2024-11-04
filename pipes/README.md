# PIPE

## What is a Pipe?


## Implementing a pipe


**NOTE**: After opening a pipe, make sure to close it on all processes (parent and child) to prevent blocking/hanging as the pipe works to continuously read data from the pipe and without properly closing the pipe, it assumes that there is more data incoming.