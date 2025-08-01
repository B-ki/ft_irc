---

# ft_irc

A C++ implementation of an IRC (Internet Relay Chat) server, developed as part of the 42 curriculum. This project aims to provide a functioning IRC server, following the RFC standards and the project subject requirements.

## Table of Contents

- [About the Project](#about-the-project)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)
- [Code Organization](#code-organization)
- [Main Developed Functions](#main-developed-functions)
- [Contributing](#contributing)
- [License](#license)

---

## About the Project

`ft_irc` is an IRC server written mainly in C++. The server supports multiple clients, channels, basic IRC commands, and follows the required features specified in the subject PDF. Its goal is to help understand socket programming, networking concepts, and protocol implementation.

## Getting Started

### Prerequisites

- C++ compiler (tested with C++98/C++11)
- Make
- Unix-based OS (Linux/macOS recommended)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/B-ki/ft_irc.git
   cd ft_irc
   ```

2. Build the project:
   ```bash
   make
   ```

### Running the Server

Start the IRC server by specifying the port and password:
```bash
./ircserv <port> <password>
```
- `<port>`: The port number to listen on (1024-49151 recommended).
- `<password>`: The password clients need to connect.

### Connecting a Client

You can connect using any IRC client (e.g., irssi, weechat, HexChat):
```bash
/server <host> <port> <password>
```

---

## Usage

Once the server is running, clients can join, create channels, and use standard IRC commands such as `/join`, `/nick`, `/msg`, etc.

---

## Troubleshooting

- **Port already in use**: Make sure the specified port is free or use a different one.
- **Permission denied**: Use a port above 1024 or run as root (not recommended).
- **Cannot connect**: Check firewall settings and ensure the server is running.
- **Build errors**: Ensure your environment supports C++ and Make.

If you encounter other issues, please open an issue on the GitHub repo.

---

## Code Organization

The codebase is mainly organized as follows:

```
ft_irc/
├── src/                # Main source files
│   ├── server.cpp      # Server setup and event loop
│   ├── client.cpp      # Client connection management
│   ├── channel.cpp     # Channel management
│   └── command.cpp     # IRC commands implementation
├── include/            # Header files
│   ├── server.hpp
│   ├── client.hpp
│   ├── channel.hpp
│   └── command.hpp
├── Makefile
└── subject.pdf         # Project specification
```

- **src/**: All source code for the server, clients, channels, and commands.
- **include/**: All header files.
- **Makefile**: For building the project.
- **subject.pdf**: The detailed project requirements.

---

## Main Developed Functions

Below are some of the main classes and functions you’ll find:

### Server Management

- `Server::start()` — Starts the event loop and listens for new connections.
- `Server::acceptClient()` — Handles new incoming clients.
- `Server::broadcast()` — Sends messages to all or specific clients/channels.

### Client Management

- `Client::parseCommand()` — Parses and validates client commands.
- `Client::sendMessage()` — Sends a message to the client.

### Channel Management

- `Channel::addUser()` — Adds a user to a channel.
- `Channel::removeUser()` — Removes a user from a channel.
- `Channel::broadcast()` — Sends messages to all users in a channel.

### Command Handling

- `/NICK` — Change user nickname.
- `/JOIN` — Join a channel.
- `/PART` — Leave a channel.
- `/PRIVMSG` — Send private messages.
- `/KICK`, `/INVITE`, `/TOPIC`, `/MODE` — Channel management commands.

(See code and comments for more details on each function.)

---

## Contributing

Contributions, issues, and feature requests are welcome! Feel free to check the issues page.

---

## License

This project is for educational purposes as part of the 42 cursus. Please refer to the subject.pdf for more details.

---
