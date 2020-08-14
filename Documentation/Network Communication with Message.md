# Network Communication with Message
Messages are one-way information containers used by both a client (Control Station) and server (the rover). They are one-way containers of information. Messages can not be replied to directly.
## Client-side Operation

## Constructing a Message
The `Message` object has a `char * data` and `const char * typeName`, which are accompanied by `size_t dataLen` and `size_t typeNameLen`, respectively. `typeName` is used by the interpreting party to find the right handler for a Message type and should be a human-readable c-string *without* null-termination. It is a `const` pointer since most type names will be determined at compilation and dynamic allocation is not necessary. `data` is the data to be sent with the message. It should be dynamically allocated, and freeing the memory is unnecessary since it is handled internally. Manually freeing the memory may lead to exceptions since the queue is asynchronous and the memory must be available when it is sent.

