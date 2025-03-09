# Simple HTTP 1.1 Server - C++

A simple HTTP 1.1 server that runs on localhost:42069

## Why

This project was built so that I could learn the basics of sockets programming and the http protocol.

## Project Status

:white_check_mark: What Works

- The server

:construction: In Progress

- A server class

:bug: Known Issues

- :shrug:

:bulb: Future Plans

- Maintenance

## Building

Requirements

- Windows operating system
- A C++ compiler
- CMake

CMake

```
cmake -B build
```

```
cmake --build build
```

## Usage

Running The Server

```
./build/bin/Server.exe
```

Open up a web browser and navigate to localhost:42069 (127.0.0.1:42069).

## How

The program opens a tcp socket that listens for connections on 127.0.0.1 (localhost) port 42069. Once a connection is accepted by the server the data is recieved from the client and is parsed in order to respond accordingly. The requests are parsed into a `std::unordered_map` from where we can retrieve information quickly for the response to be built. Sending the content to the client is simply reading the path to the content they are requesting, reading the into a buffer and sending that buffer back to client with the relevant http response.

## Feedback

I've only been working with C/C++ for a few years and am still fairly new to CMake, so I'd love to hear your thoughts! If you find any bugs or have any suggestions, feel free to email me at keyboardslayer7@protonmail.com. Any feedback, big or small, is greatly appreciated!
