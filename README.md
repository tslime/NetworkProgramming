# Network Programming - Under the Hood

## Introduction

This project demonstrates how different programming languages interact with operating system primitives to achieve network communication and concurrency. The aim is to dive into what happens "under the hood" when servers handle multiple client connections.

Node.js highlights how high-level frameworks can abstract lower-level system primitives such as `epoll` (Linux) or `kqueue` (macOS). In contrast, languages like C and C++ provide direct access to these system-level mechanisms for fine-grained control, enabling superior performance at the cost of developer complexity. Implementations in Python and Java show additional abstractions with different trade-offs.

The project includes:
- **Simple implementations**: Managing one connection at a time for basic understanding.
- **Fork-like concurrency**: Handling multiple clients via a unique thread/process for each connection.
- **Robust event-driven concurrency**: Using OS mechanisms like `epoll`, `select`, or modern asynchronous Python libraries for efficient client handling.

---

## Project Structure

The repository showcases implementations across multiple languages with concurrency models such as event-driven architecture (`epoll`, `Selector`), non-blocking I/O, and asynchronous event loops tailored for efficient client handling and scalability. I now discuss the implementation of each succinctly.

### 1. Node.js
- **Simple Implementation**: A basic `createServer`-based server for responding to client requests.
- **Concurrency Model**: Node.js uses `libuv` to abstract `epoll` or `kqueue` and implements concurrency with its non-blocking event loop.

**Advantages:**
- High-level abstraction over OS networking features like `epoll`.
- Ideal for fast prototyping and development.

**Code Example:**
```javascript
const net = require('net');
const server = net.createServer((socket) => {
  socket.on('data', (data) => socket.write('Message received'));
});

server.listen(8080, () => console.log('Server listening on port 8080'));
```

[Node.js Server](BasicClientServerProgram/Nodejs/Server.js)

---

### 2. C
- **Simple Implementation**: Directly uses low-level sockets for single client handling.
- **Fork-like Concurrency**: Creates child processes using `fork` for each client for concurrent handling.
- **Robust Concurrency**: Implements event-driven concurrency with `epoll` for efficient handling of multiple clients.

**Advantages:**
- Direct access to OS mechanisms like `epoll`.
- Unmatched performance when fine-tuned for specific use cases.

**Code Example (epoll-based server):**
```c
int fd_manager = epoll_create1(0);
if (fd_manager == -1) {
    perror("Failed to create epoll instance");
    exit(EXIT_FAILURE);
}

struct epoll_event events[MAX_EVENTS];
int num_events = epoll_wait(fd_manager, events, MAX_EVENTS, -1);

for (int i = 0; i < num_events; i++) {
    if (events[i].data.fd == server_fd) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd != -1) {
            struct epoll_event client_event = { .data.fd = client_fd, .events = EPOLLIN };
            epoll_ctl(fd_manager, EPOLL_CTL_ADD, client_fd, &client_event);
        }
    } else {
        handle_client(events[i].data.fd);
    }
}
```

[Explore all C implementations](https://github.com/tslime/NetworkProgramming/tree/main/BasicClientServerProgram/C)

---

### 3. C++
- **Simple Implementation**: Socket-based client handling with object-oriented code structure.
- **Fork-like Concurrency**: Uses `fork` to create process-based concurrency.
- **Robust Concurrency**: Optimized server design with `epoll`, tailored for high-performance and scalability.

**Advantages:**
- Combines the raw power of C with object-oriented patterns for scalability.
- Suited for latency-critical applications requiring precise control.

**Code Example:**
```c++
int fd_manager = epoll_create1(0);
if (fd_manager == -1) {
    perror("Failed to create epoll instance");
    exit(EXIT_FAILURE);
}

struct epoll_event events[MAX_EVENTS];
int num_events = epoll_wait(fd_manager, events, MAX_EVENTS, -1);

for (int i = 0; i < num_events; i++) {
    if (events[i].data.fd == server_fd) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd != -1) {
            epoll_event client_event = { .data.fd = client_fd, .events = EPOLLIN };
            epoll_ctl(fd_manager, EPOLL_CTL_ADD, client_fd, &client_event);
        }
    } else {
        process_client(events[i].data.fd);
    }
}
```

[Explore all C++ implementations](https://github.com/tslime/NetworkProgramming/tree/main/BasicClientServerProgram/C++/src)

---

### 4. Java
- **Concurrency with Threads**: Uses `ServerSocket` to spawn new threads for each client.
- **Efficient Concurrency**: Implements non-blocking I/O with `Selector` for scalable client handling.

**Advantages:**
- JVM's portability and memory management simplify networking tasks.
- A balanced choice between performance and developer usability.

**Code Example:**
```java
Selector selector = Selector.open();
serverChannel.register(selector, SelectionKey.OP_ACCEPT);

while (true) {
    int numEvents = selector.select();
    Set<SelectionKey> keys = selector.selectedKeys();
    Iterator<SelectionKey> iterator = keys.iterator();
    
    while (iterator.hasNext()) {
        SelectionKey key = iterator.next();
        iterator.remove();

        if (key.isAcceptable()) {
            ServerSocketChannel server = (ServerSocketChannel) key.channel();
            SocketChannel client = server.accept();
            client.configureBlocking(false);
            client.register(selector, SelectionKey.OP_READ);
        } else if (key.isReadable()) {
            handleClient((SocketChannel) key.channel());
        }
    }
}
```

[Explore all Java implementations](https://github.com/tslime/NetworkProgramming/tree/main/BasicClientServerProgram/Java)

---

### 5. Python
- **Simple Implementation**: Minimal socket server.
- **Threading Concurrency**: Uses Python threading for handling clients.
- **Asyncio-based Concurrency**: Modern event-loop concurrency using `asyncio` for efficient I/O.

**Advantages:**
- Asynchronous programming with `asyncio` is simple, clean, and effective.
- Helpful libraries make development faster.

**Code Example:**
```python
import asyncio

async def handle_client(reader, writer):
    data = await reader.read(100)
    print(f"Received: {data.decode()}")
    writer.write(b"Message received\n")
    await writer.drain()
    writer.close()

async def main():
    server = await asyncio.start_server(handle_client, '127.0.0.1', 8080)
    async with server:
        await server.serve_forever()

asyncio.run(main())
```

[Explore all Python implementations](https://github.com/tslime/NetworkProgramming/tree/main/BasicClientServerProgram/Python)

---


## Comparison Table

The table below highlights Concurrency Level (capacity to handle multiple clients) and Ease of Implementation (developer effort). 

| Metric                  | Node.js      | C            | C++          | Java        | Python     |
|-------------------------|--------------|--------------|--------------|-------------|------------|
| **Concurrency Level**  | **High**     | **Very High** | **Very High**| **High**    | **High**   |
| **Ease of Implementation** | **High**     | *Low*       | *Low*       | **Medium**  | **Medium** |

---

### Table Description:
1. **Concurrency Level**:
   - Reflects scalability and capacity to handle thousands of clients:
     - **Very High**: C and C++ deliver raw performance when implemented correctly.
     - **High**: Node.js, Java, and Python rely on abstractions that maintain solid scalability.
   
2. **Ease of Implementation**:
   - Reflects the effort required to create scalable servers:
     - **Low**: C/C++ require detailed, manual management of resources like `epoll` and memory buffers.
     - **High**: Node.js abstracts all the complexity with its event loop.
     - **Medium**: Java and Python offer a balance of abstraction and control.

---

## Conclusion

This project compares how different programming languages and paradigms tackle network programming. Whether it's C or C++ for low-level fine-tuning or Node.js and Python for rapid prototyping, the repository offers insights into the tradeoffs between performance and developer productivity.
