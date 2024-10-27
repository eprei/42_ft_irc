# ft_irc

## Internet Relay Chat Server Implementation

This project implements an IRC (Internet Relay Chat) server in C++98, allowing multiple clients to connect and communicate in real-time. The server supports standard IRC features including user authentication, channels, private messaging, and operator commands.

### Features

- **Client Management**
  - Multiple simultaneous client connections
  - Non-blocking I/O operations using poll() (or equivalent)
  - Client authentication with password
  - Nickname and username registration
  - Ping/Pong for connection monitoring

- **Channel Operations**
  - Channel creation and management
  - Multiple channel modes (+ntikl)
  - Channel operator privileges
  - User limits and channel keys
  - Topic management

- **Commands**
  - User Registration: NICK, USER, PASS
  - Channel Operations: JOIN, PART, LIST, NAMES
  - Messaging: PRIVMSG, NOTICE
  - Channel Control: KICK, INVITE, TOPIC, MODE
  - Server Information: WHOIS, WHOWAS
  - Connection Maintenance: PING, PONG

- **Channel Modes**
  - i: Invite-only channel
  - t: Topic settable by channel operators only
  - k: Channel key (password)
  - l: User limit
  - n: No external messages
  - o: Channel operator status

### Requirements

- C++98 compiler
- Make build system
- Linux/Unix environment
- Working IRC client (for testing)

### Building the Project

```bash
make        # Build the server
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Rebuild the project
```

### Usage

```bash
./ircserv <port> <password>
```

- `<port>`: Port number for the server (valid range: 6665-6669)
- `<password>`: Connection password for client authentication

### Testing

The project includes several testing tools:
- Python-based proxy for debugging client-server communication
- Test scripts for various command scenarios
- Client simulation tests

### Implementation Details

The project is structured into several key components:
- Server class managing connections and client/channel lists
- Client class handling individual client states and commands
- Channel class for room management and operations
- Message parsing and execution system
- Non-blocking I/O handling with poll()

### Project Structure

```
├── commands/       # IRC command implementations
├── srcs/          # Core server components
│   ├── Server.cpp
│   ├── Client.cpp
│   ├── Channel.cpp
│   └── ...
├── test/          # Testing utilities
└── proxy/         # Debugging proxy tools
```

### Technical Highlights

- Pure C++98 implementation without external libraries
- Efficient memory management without memory leaks
- Non-blocking I/O operations
- TCP/IP socket programming
- Real-time client-server communication
- Robust error handling and input validation

### Standards Compliance

- Follows IRC protocol standards
- C++98 compliant code
- Compiled with `-Wall -Wextra -Werror` flags
- No external libraries


---
*Note: This project is part of the 42 school curriculum and implements core IRC server functionality for educational purposes.*
