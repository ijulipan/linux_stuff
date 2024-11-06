# SHARED MEMORY IPC



## SHARED MEMORY USAGE
With referring to the example in [shared_memory](/shared_memory/shared_memory.c):-

The commonly used system calls to use memory segments are:- 

- **shmget**: Creates a shared memory segment.
- **shmat**: Attaches the shared memory segment to the process’s address space.
- **shmdt**: Detaches the shared memory segment.
- **shmctl**: Controls operations on the shared memory segment, including deletion.


1. **shmget**
The *shmget* function creates a shared memory segment or accesses an existing one.

```C
int shmget(key_t key, size_t size, int shmflg);
```
- *key*: This is a unique identifier for the shared memory segment. If you pass IPC_PRIVATE, a new shared memory segment is created without a unique key (it won’t be accessible to other programs).
- *size*: This is the size of the shared memory segment in bytes. In this program, MEM_SIZE is defined as 1024, which allocates 1 KB of shared memory.
- *shmflg*: This is a flag that sets the permissions and behavior for the memory segment.
- *IPC_CREAT*: Creates the segment if it doesn't already exist.
- *0666*: Sets read and write permissions for the owner, group, and others.


2. **shmat**
The *shmat* function attaches the shared memory segment to the process’s address space.

```C
void* shmat(int shmid, const void *shmaddr, int shmflg);
```
- *shmid*: The shared memory segment ID returned by shmget.
- *shmaddr*: This is the address where the segment should be attached. If set to NULL, the system chooses an appropriate address.
- *shmflg*: Flags for attaching. Most commonly, 0 is used here, indicating default read and write access. The function returns a pointer to the shared memory. If it fails, it returns (void *) -1.


3. **snprintf**
The *snprintf* function writes formatted data to a string.

```C
int snprintf(char *str, size_t size, const char *format, ...);
```
- *str*: The destination buffer, where the formatted string will be stored.
- *size*: The maximum number of bytes to write, including the null terminator.
- *format*: A format string similar to printf, specifying how the remaining arguments are converted.


4. **shmdt**
The *shmdt* function detaches the shared memory segment from the process's address space.

```c
int shmdt(const void *shmaddr);
```
- *shmaddr*: The address of the shared memory segment, which was returned by shmat. Detaching helps clean up after the process finishes using the shared memory.


5. **shmctl**
The *shmctl* function performs various operations on the shared memory segment, such as deletion.

```c
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```
- *shmid*: The shared memory ID, returned by shmget.
- *cmd*: The command specifying the action to perform. IPC_RMID removes the segment, marking it for deletion once no process is attached to it.
- *buf*: A pointer to a shmid_ds structure that holds information about the shared memory. For IPC_RMID, this is typically NULL since no additional information is needed.
