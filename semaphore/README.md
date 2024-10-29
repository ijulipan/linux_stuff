# SEMAPHORE

## Definition

It is a concept to control multiple processes from accessing the same share resource. It implements a lock and key concept where if the resource is being used by a process, it will 'lock' the resource so that other processes cannot access it. Once the process is done with the resource, it 'unlocks' the resource for the next process to use.

There are two types of semaphores: -

1. **Binary semaphores**: (0 or 1) used to control access to a single resource
2. **Counting semaphores**: (>1) used to control access to multiple resources, the number indicates the available number of resources.

## Implementation

A semaphore variable is created and is used to control access to the resource. One semaphore variable can be used to control multiple resources. The operations of the variable are: -

- **Increment** (post or signal): increments the value of the semaphore to indicate that a resource is available
- **Decrement** (wait or acquire): Decrement the value of the semaphore indicating that a resource is in use, if its zero it indicates that the resource is not available