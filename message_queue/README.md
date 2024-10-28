# MESSAGE QUEUE 

## What is Message Queue?

Message queue is a IPC (Interprocess Communication) that uses a buffer to send/receive messages from one process to another. Messages can be sent/received asynchronously as the IPC decouples the sender and receiver, meaning that it does not care about who is receiving and sending the message. This type of IPC is useful in the following scenarios: -

1. **Asynchronous Communication**: Processes that don't need to operate in lockstep (processes can send messages and continue with their work).
2. **Communication between unrelated Processes**: Unlike *pipes*, message queues do not need a parent-child relationship which allows to send/receive messages from any process.
3. **Orderly Messaging**: Messages can have priorities and the more urgent message can be prioritized.
4. **Decoupling Sender and Receiver**: The sender and receiver don't need to know each other's states and only depend on the message queue as a middle man.
5. **Data exchange with Defined Structure**: Message queues can send specific types of data such as control commands or config data.

The Linux Kernel uses two types of message queues:-

- **System V IPC Messages**: Implements messages as *linked lists*, the **sender process invokes the `msgsnd()` function to send a message**. It takes the IPC identifier of the receiving message queue, message size, and message structure containing the message type and text. The **receviver process invokes the `msgrcv()` function to receive a message**. It requires the IPC identifier, buffer to store the message, buffer size and a value t(message returned from the queue). 
**NOTE: The functions `msgsnd()` and `msgrcv()` can be found in *include/linux/msg.h*
- **POSIX Message Queue**: Simple file-based interface that makes it easy for applications to interact with message queues. It is located in *ipc/mqueue.c* and offers the feature to support message priorities to receive messages in a specific order based on their importance.

An example of how to write a message queue sender and receiver is shown in [message send](/message_queue/msg_send.c) and [message receive](/message_queue/msg_recv.c) respectively.