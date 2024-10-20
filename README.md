# ft_irc

## Internet Relay Chat Server

This project involves creating an IRC (Internet Relay Chat) server in C++98. The goal is to implement a server that can handle multiple clients simultaneously and provide basic IRC functionality.

### Features

- TCP/IP communication (IPv4 or IPv6)
- Multiple client handling without blocking
- Client authentication
- Channels
- Private messages
- Operator commands (KICK, INVITE, TOPIC, MODE)

### Requirements

- C++98 standard
- Must compile with `c++` and flags `-Wall -Wextra -Werror`
- No external libraries or Boost set
- Must use `poll()` (or equivalent like `select()`, `kqueue()`, `epoll()`) for non-blocking I/O operations

### Building the Project

```
make
```

### Running the Server

```
./ircserv <port> <password>
```

- `<port>`: The port number on which your IRC server will listen for incoming connections.
- `<password>`: The connection password required for any IRC client to connect to your server.

### Testing

Use a real IRC client to connect to your server and test its functionality.

### Note

This project is meant to help understand the inner workings of an IRC server and network programming concepts. It's not intended for production use.
