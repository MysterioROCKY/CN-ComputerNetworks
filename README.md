# CN-ComputerNetworks

This repository contains various C programs related to computer networks, including protocols and client-server communication implementations.

## Contents

- `BitDestuffing.c`: Program to perform bit destuffing.
- `BitStuffing.c`: Program to perform bit stuffing.
- `CyclicRedundancyCheck.c`: Program to implement cyclic redundancy check (CRC).
- `DistanceVectarRouting_Protocol.c`: Implementation of the Distance Vector Routing protocol.
- `LinkStateRouting_Protocol.c`: Implementation of the Link State Routing protocol.
- `SlidingWindow_Protocol.c`: Implementation of the Sliding Window protocol.
- `StopWait_Protocol.c`: Implementation of the Stop and Wait protocol.

## Directories

- `ServerClient_Chat_TCP/`: Contains server and client programs for chat communication over TCP.
  - `Server_Chat_TCP.c`: TCP server for chat communication.
  - `Client_Chat_TCP.c`: TCP client for chat communication.

- `ServerClient_Chat_UDP/`: Contains server and client programs for chat communication over UDP.
  - `Server_Chat_UDP.c`: UDP server for chat communication.
  - `Client_Chat_UDP.c`: UDP client for chat communication.

- `ServerClient_File_TCP/`: Contains server and client programs for file transfer over TCP.
  - `Server_File_TCP.c`: TCP server for file transfer.
  - `Client_File_TCP.c`: TCP client for file transfer.

- `ServerClient_File_UDP/`: Contains server and client programs for file transfer over UDP.
  - `Server_File_UDP.c`: UDP server for file transfer.
  - `Client_File_UDP.c`: UDP client for file transfer.

### How to Compile

To compile any of the C programs, use the `gcc` compiler. For example, to compile `BitStuffing.c`, you can use the following command:

```sh
gcc -o BitStuffing BitStuffing.c
